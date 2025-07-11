#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// 每个矩形边缘事件
struct Event {
    int x;
    int y1, y2;
    int type; // +1: entering, -1: leaving

    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

// 坐标离散化后的线段树节点数量最大值（所有 y 坐标数 * 2）
const int MAXN = 10010;

struct SegmentTree {
    int cover[4 * MAXN] = {0}; // 覆盖次数
    int length[4 * MAXN] = {0}; // 当前区间合并后的总长度
    vector<int> ys;

    void build(const vector<int>& y_coords) {
        ys = y_coords;
    }

    void update(int node, int l, int r, int ql, int qr, int val) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            cover[node] += val;
        } else {
            int mid = (l + r) / 2;
            update(node * 2, l, mid, ql, qr, val);
            update(node * 2 + 1, mid, r, ql, qr, val);
        }

        if (cover[node] > 0) {
            length[node] = ys[r] - ys[l];
        } else {
            if (r - l == 1) length[node] = 0;
            else length[node] = length[node * 2] + length[node * 2 + 1];
        }
    }

    int query() const {
        return length[1]; // 根节点
    }

    int find_index(int y) {
        return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
    }
};

int main() {
    int n;
    cin >> n;

    vector<Event> events;
    vector<int> y_coords;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        events.push_back({x1, y1, y2, +1});
        events.push_back({x2, y1, y2, -1});

        y_coords.push_back(y1);
        y_coords.push_back(y2);
    }

    // 对 y 坐标离散化
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());

    // 排序事件
    sort(events.begin(), events.end());

    SegmentTree st;
    st.build(y_coords);

    long long total_area = 0;
    int prev_x = events[0].x;

    for (const auto& e : events) {
        int cur_x = e.x;
        int dx = cur_x - prev_x;
        int height = st.query();
        total_area += static_cast<long long>(dx) * height;

        int y1 = st.find_index(e.y1);
        int y2 = st.find_index(e.y2);
        st.update(1, 0, y_coords.size() - 1, y1, y2, e.type);

        prev_x = cur_x;
    }

    cout << "Total union area: " << total_area << endl;
    return 0;
}
