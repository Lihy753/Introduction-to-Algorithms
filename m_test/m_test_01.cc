// #include <iostream>
// #include <vector>
// #include <map>
// #include <algorithm>

// struct Polygon {
//     int id;
//     double x, y;    // 左下角坐标
//     double area;
//     int row_id, col_id; // 网格位置
// };

// // 网格粒度大小（单位与坐标单位一致，如 micron、nm）
// const int TILE_SIZE = 500;

// void assignGridID(std::vector<Polygon>& polygons) {
//     for (auto& poly : polygons) {
//         // 这里是确定该每个 polygon 是在第几个 grid 中！
//         poly.row_id = static_cast<int>(poly.y / TILE_SIZE);  // row = y方向
//         poly.col_id = static_cast<int>(poly.x / TILE_SIZE);  // col = x方向
//     }
// }

// void gridSortedBalancedColoring(std::vector<Polygon>& polygons, std::map<int, int>& colors) {
//     assignGridID(polygons);

//     // Step 1: 排序（按 row_id，再按 col_id）
//     std::sort(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
//         if (a.row_id != b.row_id)
//             return a.row_id < b.row_id;
//         return a.col_id < b.col_id;
//     });

//     // Step 2: 顺序染色，保持两色面积均衡
//     double area0 = 0, area1 = 0;

//     for (const auto& poly : polygons) {
//         int chosen_color = (area0 <= area1) ? 0 : 1;
//         colors[poly.id] = chosen_color;

//         if (chosen_color == 0)
//             area0 += poly.area;
//         else
//             area1 += poly.area;
//     }

//     std::cout << "Total Area Color 0: " << area0 << ", Color 1: " << area1 << "\n";
// }


// int main() {
//     std::vector<Polygon> polygons = {
//         {0, 100, 200, 50}, {1, 300, 400, 80}, {2, 1200, 400, 60}, {3, 900, 100, 70},
//         {4, 250, 180, 55}, {5, 1100, 500, 90}
//     };

//     std::map<int, int> colors;
//     gridSortedBalancedColoring(polygons, colors);

//     for (const auto& fi : colors) {
//         std::cout << "Polygon " << fi.first << " -> Color: " << fi.second << "\n";
//     }

//     return 0;
// }


#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <cmath>

// Polygon 定义
struct Polygon {
    int id;
    double area;
    int color = -1; // -1 表示未染色
};


// 每个 Cell 包含若干 polygon
struct GridCell {
    std::vector<Polygon*> polygons;
    bool visited = false;
};

// 主逻辑
void bfs_polygon_coloring(std::vector<std::vector<GridCell>>& grid, int color_count = 2) {
    int rows = grid.size();
    int cols = grid[0].size();

    std::queue<std::pair<int, int>> q;
    q.push({0, 0});  // 从左下角开始（如有必要可改成 rows-1, 0）
    grid[0][0].visited = true;

    // 全局颜色面积统计
    std::vector<double> total_area_per_color(color_count, 0.0);

    const std::vector<std::pair<int, int>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        GridCell& cell = grid[r][c];

        // 对每个 polygon 单独决定颜色

        std::sort(cell.polygons.begin(), cell.polygons.end(), [](Polygon* a, Polygon* b) {
                return a->area > b->area;
            });
        for (auto poly : cell.polygons) {
            if (poly->color != -1) continue;  // 已染色

            // 选择使颜色面积最均衡的颜色
            int best_color = 0;
            double min_total_area = 1e18;

            for (int color = 0; color < color_count; ++color) {
                double simulated_area = total_area_per_color[color] + poly->area;
                if (simulated_area < min_total_area) {
                    min_total_area = simulated_area;
                    best_color = color;
                }
            }

            // 上色
            poly->color = best_color;
            total_area_per_color[best_color] += poly->area;
        }

        // 扩展邻居
        for (auto [dr, dc] : dirs) {
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !grid[nr][nc].visited) {
                grid[nr][nc].visited = true;
                q.push({nr, nc});
            }
        }
    }

    // 打印统计
    for (int i = 0; i < color_count; ++i) {
        std::cout << "Color " << i << " total area = " << total_area_per_color[i] << "\n";
    }
}

