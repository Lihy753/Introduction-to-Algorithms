#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_set>

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

// 欧几里得距离平方
double distance2(const Non_conflict_polygons* a, const Non_conflict_polygons* b) {
    double dx = a->m_x - b->m_x;
    double dy = a->m_y - b->m_y;
    return dx * dx + dy * dy;
}

// 构建 KNN 邻接图（邻接表）
std::vector<std::vector<int>> build_knn_graph(const std::vector<Non_conflict_polygons*>& polys, int k = 4) {
    int n = polys.size();
    std::vector<std::vector<int>> adj(n);

    for (int i = 0; i < n; ++i) {
        std::vector<std::pair<double, int>> neighbors;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            double d2 = distance2(polys[i], polys[j]);
            neighbors.emplace_back(d2, j);
        }
        std::partial_sort(neighbors.begin(), neighbors.begin() + std::min(k, (int)neighbors.size()), neighbors.end());
        for (int t = 0; t < k && t < (int)neighbors.size(); ++t) {
            adj[i].push_back(neighbors[t].second);
        }
    }

    return adj;
}

// DFS 遍历邻接图
void dfs(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<int>& order) {
    visited[u] = true;
    order.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited, order);
        }
    }
}

// 主函数：返回排序后的 polygon 指针数组
std::vector<Non_conflict_polygons*> spatially_sorted_polygons(const std::vector<Non_conflict_polygons*>& polys, int k = 4) {
    int n = polys.size();
    std::vector<std::vector<int>> adj = build_knn_graph(polys, k);

    std::vector<bool> visited(n, false);
    std::vector<int> dfs_order;

    // 可选：从最左下角 polygon 开始
    int start = 0;
    for (int i = 1; i < n; ++i) {
        if (polys[i]->m_x < polys[start]->m_x || 
           (polys[i]->m_x == polys[start]->m_x && polys[i]->m_y < polys[start]->m_y)) {
            start = i;
        }
    }

    dfs(start, adj, visited, dfs_order);

    // 如果有未连通点（极少数孤立 polygon）
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, dfs_order);
        }
    }

    std::vector<Non_conflict_polygons*> result;
    for (int idx : dfs_order) {
        result.push_back(polys[idx]);
    }

    return result;
}


int main() {
    std::vector<Non_conflict_polygons*> polygons;
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

    polygons.push_back(poly1);
    polygons.push_back(poly2);
    polygons.push_back(poly3);
    polygons.push_back(poly4);

    polygons.push_back(poly5);
    polygons.push_back(poly6);
    polygons.push_back(poly7);
    polygons.push_back(poly8);

    polygons.push_back(poly9);
    polygons.push_back(poly10);
    polygons.push_back(poly11);
    polygons.push_back(poly12);

    auto sorted = spatially_sorted_polygons(polygons, 6); // 可调整 k

    // 赋值颜色/ID
    for (size_t i = 0; i < sorted.size(); ++i) {
        // sorted[i]->m_id = static_cast<int>(i);
        sorted[i]->m_color = i % 2; // 交替染色
        std::cout << "polygon : " << sorted[i]->m_id << ", color : " << sorted[i]->m_color << std::endl;
    }

    return 0;
}
