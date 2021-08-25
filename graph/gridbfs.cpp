// グリッドBFS
// verified
// ATC 001 A - 深さ優先探索
// https://atcoder.jp/contests/atc001/submissions/17517887
// 蟻本 p38~39

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1001001001;

vector<vector<int>> gridbfs(vector<string> &grid, int H, int W, int SX, int SY) {
    vector<vector<int>> res(H, vector<int>(W,INF));
    vector<pair<int,int>> dxdy = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    queue<pair<int,int>> que;
    res[SX][SY] = 0;
    que.push({SX,SY});

    while (que.size()) {
        pair<int,int> p = que.front(); que.pop();
        int cx = p.first, cy = p.second;
        for (int i = 0; i < 4; i++) {
            int nx = cx+dxdy[i].first, ny = cy+dxdy[i].second;
            if (0 <= nx && nx < H && 0 <= ny && ny < W && grid[nx][ny] != '#' && res[nx][ny] == INF) {
                res[nx][ny] = res[cx][cy]+1;
                que.push({nx,ny});
            }
        }
    }
    return res;
}

int main() {
    int h,w,sx,sy,gx,gy; cin >> h >> w;
    vector<string> grid(h);
    for (int i = 0; i < h; i++) cin >> grid[i];

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 's') {sx = i; sy = j;}
            if (grid[i][j] == 'g') {gx = i; gy = j;}
        }
    }

    vector<vector<int>> res = gridbfs(grid, h, w, sx, sy);

    printf("%s\n", res[gx][gy] != INF ? "Yes" : "No");

    return 0;
}
