#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdint>

/*
坐标(m_x, m_y)
     ↓
归一化 → 映射为整数格点 (gx, gy)
     ↓
Hilbert 曲线映射 → 得到 h 值（1D）
     ↓
对所有 polygon 的 h 值排序
     ↓
排序后 ID 相近 → 空间上位置也尽量相近
*/
using namespace std;

// 你的结构体
struct Non_conflict_polygons {
    Non_conflict_polygons(int id, double area, int x, int y)
    {
        m_id = id;
        m_area = area;
        m_color = -1;
        m_x = x;
        m_y = y;
    }
    int m_id;
    double m_area;
    int m_color;
    double m_x;
    double m_y;
};

// Hilbert 辅助函数
void rot(int n, int& x, int& y, int rx, int ry) {
    if (ry == 0) {
        if (rx == 1) {
            x = n - 1 - x;
            y = n - 1 - y;
        }
        std::swap(x, y);
    }
}

uint32_t hilbert_index(int bits, int x, int y) {
    uint32_t index = 0;
    int n = 1 << bits; // 这里的 n 也就是 gridsize；
    cout << "n = " << n << endl;
    int rx, ry;
    for (int s = bits - 1; s >= 0; --s) {
        rx = (x >> s) & 1;          // 这个操作是为了提取出 x 的二进制编码中的第 s 位元素！！！
        ry = (y >> s) & 1;
        index += (uint32_t)(1 << (2 * s)) * ((3 * rx) ^ ry);    // rx, ry 都是 0 或者 1。 (3 * rx) ^ ry 是确定第几象限，其值范围位 [0,1,2,3]. "^" 是按位异或（XOR）的意思
        rot(n, x, y, rx, ry);
    }
    return index;
}

int normalize(double val, double min_val, double max_val, int grid_size) {
    if (max_val - min_val < 1e-12)
        return 0;
    double ratio = (val - min_val) / (max_val - min_val);
    if (ratio < 0.0) ratio = 0.0;
    if (ratio > 1.0) ratio = 1.0;
    cout << "val " << val << ", min_val = " << min_val << ", max_val = " << max_val << ", ratio = " << ratio << endl;
    return static_cast<int>(ratio * (grid_size - 1));   // 确定其在第几个 grid 上；
}

// 复合排序函数：面积降序，面积相同按 Hilbert 升序
void sort_polygons_by_area_then_hilbert(std::vector<Non_conflict_polygons*>& polys,
                                        double min_x, double min_y,
                                        double max_x, double max_y,
                                        int bits = 10) {
    const int grid_size = 1 << bits;

    std::sort(polys.begin(), polys.end(),
        [&](const Non_conflict_polygons* a, const Non_conflict_polygons* b) {
            // 面积降序
            if (fabs(a->m_area - b->m_area) > 1e-9)
                return a->m_area > b->m_area;

            std::cout << "polygons [ " << a->m_id << ", " << b->m_id << " ]" << std::endl;
            // 面积相等时，Hilbert 曲线升序
            int ax = normalize(a->m_x, min_x, max_x, grid_size);
            int ay = normalize(a->m_y, min_y, max_y, grid_size);
            int bx = normalize(b->m_x, min_x, max_x, grid_size);
            int by = normalize(b->m_y, min_y, max_y, grid_size);

            std::cout << "ax " << ax << ", " << "ay " << ay << std::endl;
            std::cout << "bx " << bx << ", " << "by " << by << std::endl;
            uint32_t h1 = hilbert_index(bits, ax, ay);
            uint32_t h2 = hilbert_index(bits, bx, by);
            std::cout << "h1 = " << h1 << ", h2 = " << h2 << "; and h1 < h2 : " << bool(h1 < h2) << std::endl;

            return h1 < h2;
        });
}

int main() {
    std::vector<Non_conflict_polygons*> polys;
    Non_conflict_polygons* poly1 = new Non_conflict_polygons(0, 10, 1, 1);
    Non_conflict_polygons* poly2 = new Non_conflict_polygons(1, 10, 1, 2);
    Non_conflict_polygons* poly3 = new Non_conflict_polygons(2, 10, 1, 3);
    Non_conflict_polygons* poly4 = new Non_conflict_polygons(3, 10, 1, 4);

    Non_conflict_polygons* poly5 = new Non_conflict_polygons(4, 10, 2, 1);
    Non_conflict_polygons* poly6 = new Non_conflict_polygons(5, 10, 2, 2);
    Non_conflict_polygons* poly7 = new Non_conflict_polygons(6, 10, 2, 3);
    Non_conflict_polygons* poly8 = new Non_conflict_polygons(7, 10, 2, 4);

    Non_conflict_polygons* poly9 = new Non_conflict_polygons(8, 10, 3, 1);
    Non_conflict_polygons* poly10 = new Non_conflict_polygons(9, 10, 3, 2);
    Non_conflict_polygons* poly11 = new Non_conflict_polygons(10, 10, 3, 3);
    Non_conflict_polygons* poly12 = new Non_conflict_polygons(11, 10, 3, 4);

    // Non_conflict_polygons* poly13 = new Non_conflict_polygons(12, 10, 3, 1);

    polys.push_back(poly1);
    polys.push_back(poly2);
    polys.push_back(poly3);
    polys.push_back(poly4);

    polys.push_back(poly5);
    polys.push_back(poly6);
    polys.push_back(poly7);
    polys.push_back(poly8);

    polys.push_back(poly9);
    polys.push_back(poly10);
    polys.push_back(poly11);
    polys.push_back(poly12);

    // polys.push_back(poly13);
    // 假设 polys 填充完成，且已知边界：
    double min_x = 1.0, min_y = 1.0;
    double max_x = 3.0, max_y = 4.0;

    for (size_t i = 0; i < polys.size(); ++i) {
        std::cout << "before sort, polygon " << polys[i]->m_id << std::endl;
    }
    sort_polygons_by_area_then_hilbert(polys, min_x, min_y, max_x, max_y);

    // 给排序后的多边形赋 ID 或颜色
    for (size_t i = 0; i < polys.size(); ++i) {        
        // polys[i]->m_id = static_cast<int>(i);
        polys[i]->m_color = i % 2; // 简单交替染色
    }
    for (size_t i = 0; i < polys.size(); ++i) {
        std::cout << "after sort polygon " << polys[i]->m_id << " : " << polys[i]->m_color << std::endl;
    }
}

