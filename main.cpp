#include <bits/stdc++.h>
using namespace std;

// Problem: Find shortest path from start(2) to home(3) that passes any shop(4)
// Grid n (columns) by m (rows). Movement 4-directional, cannot pass 1. Cells 0/2/3/4 passable.

static const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n columns, m rows
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> a(m, vector<int>(n));
    pair<int,int> s{-1,-1}, t{-1,-1};
    vector<pair<int,int>> shops;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            if (a[i][j] == 2) s = {i,j};
            else if (a[i][j] == 3) t = {i,j};
            else if (a[i][j] == 4) shops.push_back({i,j});
        }
    }

    auto inb = [&](int r, int c){ return r>=0 && r<m && c>=0 && c<n; };
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    // BFS from a set of sources to get distance to all cells
    auto bfs = [&](const vector<pair<int,int>>& srcs){
        vector<vector<int>> dist(m, vector<int>(n, INF));
        deque<pair<int,int>> dq;
        for (auto [r,c]: srcs) {
            dist[r][c] = 0;
            dq.emplace_back(r,c);
        }
        while (!dq.empty()) {
            auto [r,c] = dq.front(); dq.pop_front();
            int d = dist[r][c];
            for (int k=0;k<4;++k){
                int nr=r+dr[k], nc=c+dc[k];
                if (!inb(nr,nc)) continue;
                if (a[nr][nc]==1) continue; // blocked building
                if (dist[nr][nc] > d + 1){
                    dist[nr][nc] = d + 1;
                    dq.emplace_back(nr,nc);
                }
            }
        }
        return dist;
    };

    if (s.first==-1 || t.first==-1 || shops.empty()){
        // If any essential is missing, no valid path
        cout << -1 << '\n';
        return 0;
    }

    // Distances from start and to home (via reverse thinking using BFS from target)
    auto distS = bfs({s});
    auto distT = bfs({t});

    long long ans = LLONG_MAX;
    for (auto [r,c] : shops){
        if (distS[r][c] >= INF || distT[r][c] >= INF) continue;
        ans = min(ans, (long long)distS[r][c] + distT[r][c]);
    }

    if (ans==LLONG_MAX) cout << -1 << '\n';
    else cout << ans << '\n';
    return 0;
}

