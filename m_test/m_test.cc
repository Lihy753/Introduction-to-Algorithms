#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <stdexcept>

struct Node {
    int parent;
    int rank;
    bool flip_flag;
    bool fix;
    int fixed_color;
};

std::vector<Node> uf;

// 初始化并查集
void init_union_find(int n, const std::map<int, int>& fixed_nodes) {
    uf.resize(n);
    for (int i = 0; i < n; ++i) {
        uf[i] = {i, 0, false, false, -1};
    }
    for (const auto& fi : fixed_nodes) {
        uf[std::get<0>(fi)].fix = true;
        uf[std::get<0>(fi)].fixed_color = std::get<1>(fi);
    }
}

// 查找根节点，并进行路径压缩
int find(int x) {
    if (uf[x].parent != x) {
        int root = find(uf[x].parent);
        uf[x].flip_flag ^= uf[uf[x].parent].flip_flag;
        uf[x].parent = root;
    }
    return uf[x].parent;
}

// 合并两个节点的集合
void unite(int x, int y, bool flip) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        // 检查固定颜色冲突
        if (uf[rootX].fix && uf[rootY].fix) {           //如果两团都是固定颜色
            if ((uf[rootX].fixed_color ^ uf[rootX].flip_flag) != 
                (uf[rootY].fixed_color ^ uf[rootY].flip_flag ^ flip)) {
                throw std::logic_error("Fixed color conflict detected!");
            }
        }

        if (uf[rootX].rank < uf[rootY].rank) {
            std::swap(rootX, rootY);
            flip = !flip;
        }

        uf[rootY].parent = rootX;           //总是将小团的根节点，指向大团的根节点！
        uf[rootY].flip_flag = flip ^ uf[x].flip_flag ^ uf[y].flip_flag;    //更新小团的flip状态

        if (uf[rootX].fix) {
            uf[rootY].fix = true;
            uf[rootY].fixed_color = uf[rootX].fixed_color;
        }

        if (uf[rootX].rank == uf[rootY].rank) {
            uf[rootX].rank++;
        }
    }
}

// 计算最终颜色结果
void calculate_final_colors(std::map<int, int>& color_result, const std::vector<int>& initial_colors) {
    for (int i = 0; i < uf.size(); ++i) {
        int root = find(i);
        if (uf[root].fix) {
            color_result[i] = uf[root].fixed_color ^ uf[i].flip_flag;
        } else {
            color_result[i] = initial_colors[i] ^ uf[i].flip_flag;
        }
    }
}

int main() {
    int n = 6; // 节点数
    std::map<int, int> fixed_nodes = {{0, 0}, {3, 1}}; // 固定颜色的节点
    init_union_find(n, fixed_nodes);

    // 初始颜色
    std::vector<int> initial_colors = {0, 0, 0, 1, 1, 0};

    // 边及优先级
    std::vector<std::tuple<int, int, int>> edges = {
        {0, 1, 1},  // 优先级 0
        {0, 3, 2},
        {0, 2, 1},


        {1, 0, 1},
        {1, 2, 2},

        {2, 0, 1},
        {2, 1, 2},
        {2, 3, 1},


        {3, 0, 2},
        {3, 2, 1},
        {3, 4, 4},

        {4, 3, 4},
        {4, 5, 3},

        {5, 4, 3},
    };

    // 按优先级分组
    std::map<int, std::vector<std::tuple<int, int>>> priority_groups;
    for (const auto& fi : edges) {
        priority_groups[std::get<2>(fi)].emplace_back(std::get<0>(fi), std::get<1>(fi));
    }

    // 按优先级逐层处理
    for (const auto& fi : priority_groups) {
        std::cout << "Processing priority " << fi.first << std::endl;
        for (const auto& si : fi.second) {
            bool flip = (fi.first > 0); // 正数优先级翻转，负数优先级保持相同
            unite(std::get<0>(si), std::get<1>(si), flip);
        }
    }

    // 计算最终颜色
    std::map<int, int> color_result;
    calculate_final_colors(color_result, initial_colors);

    // 输出结果
    for (const auto& fi : color_result) {
        std::cout << "Node " << fi.first << ": Color " << fi.second << std::endl;
    }

    return 0;
}
