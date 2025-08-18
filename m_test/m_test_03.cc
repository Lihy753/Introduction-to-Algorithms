// pde_uv.cpp
// C++ (Eigen) rewrite of the provided MATLAB code for coupled u,v system.
// Author: ChatGPT (GPT-5 Thinking)
// Build: g++ -O3 -DNDEBUG -I /path/to/eigen -std=c++17 pde_uv.cpp -o pde_uv

#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using SpMat = Eigen::SparseMatrix<double>;
using Triplet = Eigen::Triplet<double>;
using Vec = Eigen::VectorXd;

// -------- utilities: sparse identity and shifted diagonal (ones on given offset) ----------
static SpMat speye(int n) {
    SpMat I(n, n);
    I.setIdentity();
    return I;
}

// diag_ones(n, offset): returns an n x n sparse matrix with ones on the diagonal shifted by 'offset'
// offset = 0 -> identity; -1 -> sub-diagonal; +1 -> super-diagonal
static SpMat diag_ones(int n, int offset) {
    SpMat D(n, n);
    std::vector<Triplet> trips;
    trips.reserve(n);
    if (offset >= 0) {
        for (int i = 0; i < n - offset; ++i) {
            trips.emplace_back(i, i + offset, 1.0);
        }
    } else {
        int k = -offset;
        for (int i = 0; i < n - k; ++i) {
            trips.emplace_back(i + k, i, 1.0);
        }
    }
    D.setFromTriplets(trips.begin(), trips.end());
    return D;
}

// scale a sparse matrix
static SpMat scale(const SpMat& A, double s) {
    SpMat B = A;
    B *= s;
    return B;
}

// sparse tridiagonal matrix of size n with [sub, diag, super]
static SpMat sp_tridiag(int n, double sub, double diag, double super) {
    std::vector<Triplet> trips;
    trips.reserve(3 * n);
    for (int i = 0; i < n; ++i) {
        trips.emplace_back(i, i, diag);
        if (i + 1 < n) {
            trips.emplace_back(i + 1, i, sub);
            trips.emplace_back(i, i + 1, super);
        }
    }
    SpMat A(n, n);
    A.setFromTriplets(trips.begin(), trips.end());
    return A;
}

// Kronecker product for sparse matrices: kron(A,B)
static SpMat kronSparse(const SpMat& A, const SpMat& B) {
    // If A is (m x n) and B is (p x q), result is (m*p x n*q)
    const int m = A.rows(), n = A.cols();
    const int p = B.rows(), q = B.cols();
    std::vector<Triplet> trips;
    trips.reserve(A.nonZeros() * B.nonZeros());

    for (int kA = 0; kA < A.outerSize(); ++kA) {
        for (SpMat::InnerIterator itA(A, kA); itA; ++itA) {
            int i = itA.row();
            int j = itA.col();
            double a = itA.value();
            if (a == 0.0) continue;

            for (int kB = 0; kB < B.outerSize(); ++kB) {
                for (SpMat::InnerIterator itB(B, kB); itB; ++itB) {
                    int r = itB.row();
                    int s = itB.col();
                    double b = itB.value();
                    if (b == 0.0) continue;

                    // position in big matrix
                    int I = i * p + r;
                    int J = j * q + s;
                    trips.emplace_back(I, J, a * b);
                }
            }
        }
    }

    SpMat K(m * p, n * q);
    K.setFromTriplets(trips.begin(), trips.end());
    return K;
}

// Build the big system matrix AB for given (M1, M3, h1,h2,h3, tau, Ds, Db, mu)
// Layout follows the MATLAB code exactly:
//   First block rows/cols correspond to u (size Nu = (M1-1)^2*(M3-1)),
//   then v (size Nv = (M1-1)^2).
struct SystemMatrices {
    SpMat AB;
    int Nu;
    int Nv;
};

static SystemMatrices build_AB(int M1, int M3, double h1, double h2, double h3,
                               double tau, double Ds, double Db, double mu)
{
    const int nx = M1 - 1;             // interior in x
    const int ny = M1 - 1;             // interior in y (same as x)
    const int nz = M3 - 1;             // interior in z
    const int Nxy = nx * ny;
    const int Nu  = Nxy * nz;
    const int Nv  = Nxy;
    const int Ntot = Nu + Nv;

    // ----- coefficients (match MATLAB) -----
    // For u (3D diffusion):
    double a1 = -tau * Db / (h1 * h1);
    double a2 =  1.0 + 2.0 * tau * Db * (1.0/(h1*h1) + 1.0/(h2*h2) + 1.0/(h3*h3));
    double a3 = -tau * Db / (h2 * h2);
    double a4 = -tau * Db / (h3 * h3);

    // For v (2D diffusion + coupling term):
    double b1 = -tau * Ds / (h1 * h1);
    double b2 =  1.0 + tau * mu * Db / h3 + 2.0 * tau * Ds * (1.0/(h1*h1) + 1.0/(h2*h2));
    double b3 = -tau * Ds / (h2 * h2);
    double c  = -tau * Db / h3;

    // ----- Build pieces for u -----
    // A1 = a3*I_(nx)
    SpMat A1 = scale(speye(nx), a3);
    // A2 = tridiag in x: size nx with a1 on off-diagonals and a2 on diag
    SpMat A2 = sp_tridiag(nx, a1, a2, a1);
    // A3 = a4*I_(nx)
    SpMat A3 = scale(speye(nx), a4);

    // A2_1 = sparse(A2) (already)
    // AA1 = kron(I_y, A3)
    SpMat Iy = speye(ny);
    SpMat AA1 = kronSparse(Iy, A3);

    // AA2 = kron(diag(ones(ny-1),-1),A1) + kron(I_y,A2) + kron(diag(ones(ny-1),+1),A1)
    SpMat Dy_lower = diag_ones(ny, -1);
    SpMat Dy_upper = diag_ones(ny, +1);
    SpMat AA2 = kronSparse(Dy_lower, A1) + kronSparse(Iy, A2) + kronSparse(Dy_upper, A1);

    // AAA = kron(diag(ones(nz-1),-1),AA1) + kron(I_z,AA2) + kron(diag(ones(nz-1),+1),AA1)
    SpMat Iz = speye(nz);
    SpMat Dz_lower = diag_ones(nz, -1);
    SpMat Dz_upper = diag_ones(nz, +1);
    SpMat AAA = kronSparse(Dz_lower, AA1) + kronSparse(Iz, AA2) + kronSparse(Dz_upper, AA1);

    // ----- Build pieces for v -----
    // B1 = b3*I_(nx)
    SpMat B1 = scale(speye(nx), b3);
    // B2 = tridiag in x: size nx with b1 off-diag and b2 diag
    SpMat B2 = sp_tridiag(nx, b1, b2, b1);
    // C = c*I_(nx)
    SpMat C  = scale(speye(nx), c);

    // BB = kron(diag(ones(ny-1),-1),B1) + kron(I_y, B2) + kron(diag(ones(ny-1),+1),B1)
    SpMat BB = kronSparse(Dy_lower, B1) + kronSparse(Iy, B2) + kronSparse(Dy_upper, B1);

    // CC = kron(I_y, C)
    SpMat CC = kronSparse(Iy, C);

    // DD = mu * AA1   (boundary coupling block)
    SpMat DD = scale(AA1, mu);

    // ----- Assemble AB -----
    SpMat AB(Ntot, Ntot);
    std::vector<Triplet> trips;
    trips.reserve( AAA.nonZeros() + BB.nonZeros() + CC.nonZeros() + DD.nonZeros() );

    // Top-left: AAA (u-u)
    for (int k = 0; k < AAA.outerSize(); ++k)
        for (SpMat::InnerIterator it(AAA, k); it; ++it)
            trips.emplace_back(it.row(), it.col(), it.value());

    // Bottom-right: BB (v-v)
    for (int k = 0; k < BB.outerSize(); ++k)
        for (SpMat::InnerIterator it(BB, k); it; ++it)
            trips.emplace_back(Nu + it.row(), Nu + it.col(), it.value());

    // Bottom-left: CC (v <- u( z=0 ) coupling term)
    for (int k = 0; k < CC.outerSize(); ++k)
        for (SpMat::InnerIterator it(CC, k); it; ++it)
            trips.emplace_back(Nu + it.row(), it.col(), it.value());

    // Top-right: DD (u( z=0 ) <- v coupling)
    for (int k = 0; k < DD.outerSize(); ++k)
        for (SpMat::InnerIterator it(DD, k); it; ++it)
            trips.emplace_back(it.row(), Nu + it.col(), it.value());

    AB.setFromTriplets(trips.begin(), trips.end());

    return {AB, Nu, Nv};
}

// Build initial vector u0 = [zeros(Nu); vec(v0)]
// v0(i,j) = 10/(2*pi*sigma^2) * exp(-x(i)^2/(2*sigma^2)) * exp(-y(j)^2/(2*sigma^2))
// with x,y = -0.5+h : h : 0.5-h  (i=0..nx-1)
static Vec build_u0_vGaussian(int nx, int ny, int nz,
                              double sigma, int Nu, int Nv,
                              double x_left, double x_right)
{
    assert(Nv == nx * ny);
    Vec u0 = Vec::Zero(Nu + Nv);

    const double h = (x_right - x_left) / (nx + 1); // since nx = M1-1 interior
    const double coef = 10.0 / (2.0 * M_PI * sigma * sigma);

    // v0 laid out as vec (column-major like MATLAB: i runs over x-fast? In MATLAB, v0(i,j) with i=1..nx, j=1..ny,
    // and v0(:) stacks column-major: first column j=1 (i=1..nx), then j=2, etc.)
    // We'll emulate MATLAB: index (i,j) -> idx = i + j*nx   with i,j zero-based.
    for (int j = 0; j < ny; ++j) {
        double y = -0.5 + (j + 1) * h; // -0.5+h ... 0.5-h
        for (int i = 0; i < nx; ++i) {
            double x = -0.5 + (i + 1) * h;
            double val = coef * std::exp(-(x*x) / (2.0 * sigma * sigma))
                               * std::exp(-(y*y) / (2.0 * sigma * sigma));
            int idx = i + j * nx;
            u0(Nu + idx) = val;
        }
    }
    return u0;
}

// Time stepping: since AB is constant, we factor once and repeatedly solve AB * u^{n} = u^{n-1}
static Vec march_in_time(const SpMat& AB, const Vec& u0, int Nsteps) {
    Eigen::SparseLU<SpMat> solver;
    solver.analyzePattern(AB);
    solver.factorize(AB);
    if (solver.info() != Eigen::Success) {
        std::cerr << "Factorization failed." << std::endl;
        std::exit(1);
    }
    Vec u = u0;
    for (int n = 0; n < Nsteps; ++n) {
        u = solver.solve(u);
        if (solver.info() != Eigen::Success) {
            std::cerr << "Solve failed at step " << (n+1) << std::endl;
            std::exit(1);
        }
    }
    return u; // final time layer
}

// Extract u-part and v-part from state vector
static void split_uv(const Vec& u_all, int Nu, int Nv, Vec& u_u, Vec& u_v) {
    u_u = u_all.head(Nu);
    u_v = u_all.tail(Nv);
}

// Project fine-grid u (with nz_fine = 2*nz_coarse) onto coarse z-layers by keeping even z-slices:
// MATLAB: u_u_out = u_u(:,:, 2:2:end-1)
// Here u_u represents [layer1; layer2; ... layer_{nz_fine}] blocks, each block size = Nxy.
// We keep z = 2,4,...,(nz_fine-1)  (since end-1 is even when nz_fine=2*nz_coarse)
static Vec project_fine_to_coarse_z(const Vec& u_fine, int nx, int ny, int nz_fine) {
    const int Nxy = nx * ny;
    std::vector<int> keep_layers;
    keep_layers.reserve(nz_fine / 2 - 1);
    for (int kz = 2; kz <= nz_fine - 1; kz += 2) { // 2,4,...,nz_fine-2  (1-based in MATLAB)
        keep_layers.push_back(kz); // store 1-based for clarity
    }
    Vec u_coarse(Nxy * static_cast<int>(keep_layers.size()));
    int pos = 0;
    for (int L1based : keep_layers) {
        int k = L1based - 1; // 0-based
        int offset = k * Nxy;
        u_coarse.segment(pos, Nxy) = u_fine.segment(offset, Nxy);
        pos += Nxy;
    }
    return u_coarse;
}

int main() {
    // ----- Parameters (from MATLAB script) -----
    const double x_left = -0.5, x_right = 0.5;
    const double y_left = -0.5, y_right = 0.5;
    const double z_below = 0.0, z_above = 1.0;

    const double T = 1.0;
    const double Ds = 1.0, Db = 1.0;
    const double mu = 0.3, sigma = 0.01;

    const int M  = 58;     // x,y partitions
    const int m3 = 28;     // z partitions (first run)
    const int n  = 1 << 10; // time steps

    // ------------- First run: M1=M, M3=m3 -------------
    {
        int M1 = M;
        int M3 = m3;
        int nx = M1 - 1, ny = M1 - 1, nz = M3 - 1;

        double h1 = (x_right - x_left) / M1;
        double h2 = h1;
        double h3 = (z_above - z_below) / M3;
        double tau = T / n;

        auto sys = build_AB(M1, M3, h1, h2, h3, tau, Ds, Db, mu);

        Vec u0 = build_u0_vGaussian(nx, ny, nz, sigma, sys.Nu, sys.Nv, x_left, x_right);
        Vec u_final = march_in_time(sys.AB, u0, n);

        // Keep final layer split
        Vec u1_u_sol, u1_v_sol;
        split_uv(u_final, sys.Nu, sys.Nv, u1_u_sol, u1_v_sol);

        // Store to compare later:
        // We'll keep them in static to reuse outside block
        static Vec s_u1_u_sol, s_u1_v_sol;
        s_u1_u_sol = u1_u_sol;
        s_u1_v_sol = u1_v_sol;

        // Move to second run scope with captured copies:
        // ------------- Second run: M1=M, M3=2*m3 -------------
        {
            int M1b = M;
            int M3b = 2 * m3;
            int nxb = M1b - 1, nyb = M1b - 1, nzb = M3b - 1;

            double h1b = (x_right - x_left) / M1b;
            double h2b = h1b;
            double h3b = (z_above - z_below) / M3b;
            double taub = T / n;

            auto sysb = build_AB(M1b, M3b, h1b, h2b, h3b, taub, Ds, Db, mu);
            Vec u0b = build_u0_vGaussian(nxb, nyb, nzb, sigma, sysb.Nu, sysb.Nv, x_left, x_right);
            Vec u_final_b = march_in_time(sysb.AB, u0b, n);

            Vec u2_u_all, u2_v_all;
            split_uv(u_final_b, sysb.Nu, sysb.Nv, u2_u_all, u2_v_all);

            // ---- Project fine u(z) onto coarse z-grid ----
            Vec u2_u_proj = project_fine_to_coarse_z(u2_u_all, nxb, nyb, nzb);

            // v is already same size between runs (x,y unchanged), so no projection
            Vec u2_v_proj = u2_v_all;

            // ---- Compute errors (end time layer) ----
            // Note: sizes must match
            assert(u2_u_proj.size() == s_u1_u_sol.size());
            assert(u2_v_proj.size() == s_u1_v_sol.size());

            // L2-like (with mesh measure factors, matching your code)
            double err_u_l2_sq = 0.0;
            for (int i = 0; i < u2_u_proj.size(); ++i) {
                double d = s_u1_u_sol[i] - u2_u_proj[i];
                err_u_l2_sq += d * d;
            }
            double err_v_l2_sq = 0.0;
            for (int i = 0; i < u2_v_proj.size(); ++i) {
                double d = s_u1_v_sol[i] - u2_v_proj[i];
                err_v_l2_sq += d * d;
            }

            double err_u_l1_sum = 0.0;
            for (int i = 0; i < u2_u_proj.size(); ++i)
                err_u_l1_sum += std::abs(s_u1_u_sol[i] - u2_u_proj[i]);

            double err_v_l1_sum = 0.0;
            for (int i = 0; i < u2_v_proj.size(); ++i)
                err_v_l1_sum += std::abs(s_u1_v_sol[i] - u2_v_proj[i]);

            double err_u_l2 = std::sqrt(h1b * h2b * h3b * err_u_l2_sq);
            double err_v_l2 = std::sqrt(h1b * h2b *        err_v_l2_sq);
            double err_u_l1 = (h1b * h2b * h3b) * err_u_l1_sum;
            double err_v_l1 = (h1b * h2b)        * err_v_l1_sum;

            std::cout.setf(std::ios::scientific);
            std::cout << "err_u_l2 = " << err_u_l2 << "\n";
            std::cout << "err_v_l2 = " << err_v_l2 << "\n";
            std::cout << "err_u_l1 = " << err_u_l1 << "\n";
            std::cout << "err_v_l1 = " << err_v_l1 << "\n";
        }
    }

    return 0;
}
