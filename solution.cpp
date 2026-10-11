#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 1005;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int grid[MAXN][MAXN];
int dist_start[MAXN][MAXN];
int dist_home[MAXN][MAXN];
int n, m;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

void bfs(int start_x, int start_y, int dist[MAXN][MAXN]) {
    queue<Point> q;
    q.push(Point(start_x, start_y));
    dist[start_x][start_y] = 0;
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = curr.x + dx[dir];
            int ny = curr.y + dy[dir];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] != 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    memset(dist_start, -1, sizeof(dist_start));
    memset(dist_home, -1, sizeof(dist_home));
    
    int start_x = -1, start_y = -1, home_x = -1, home_y = -1;
    vector<Point> shops;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start_x = i; start_y = j;
            } else if (grid[i][j] == 3) {
                home_x = i; home_y = j;
            } else if (grid[i][j] == 4) {
                shops.push_back(Point(i, j));
            }
        }
    }
    
    if (start_x == -1 || home_x == -1 || shops.empty()) {
        cout << -1 << endl;
        return 0;
    }
    
    bfs(start_x, start_y, dist_start);
    bfs(home_x, home_y, dist_home);
    
    int answer = -1;
    
    for (const Point& shop : shops) {
        int dist_to_shop = dist_start[shop.x][shop.y];
        int dist_to_home = dist_home[shop.x][shop.y];
        
        if (dist_to_shop != -1 && dist_to_home != -1) {
            int total = dist_to_shop + dist_to_home;
            if (answer == -1 || total < answer) {
                answer = total;
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}