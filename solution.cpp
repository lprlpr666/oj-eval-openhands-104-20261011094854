#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

vector<vector<int>> bfs(int start_x, int start_y, const vector<vector<int>>& grid, int m, int n) {
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    queue<Point> q;
    
    dist[start_x][start_y] = 0;
    q.push(Point(start_x, start_y));
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = curr.x + dx[dir];
            int ny = curr.y + dy[dir];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] != 1 && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
    
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    Point start(-1, -1), home(-1, -1);
    vector<Point> shops;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start = Point(i, j);
            } else if (grid[i][j] == 3) {
                home = Point(i, j);
            } else if (grid[i][j] == 4) {
                shops.push_back(Point(i, j));
            }
        }
    }
    
    if (start.x == -1 || home.x == -1) {
        cout << -1 << endl;
        return 0;
    }
    
    // If there are no umbrella shops, no solution
    if (shops.empty()) {
        cout << -1 << endl;
        return 0;
    }
    
    // BFS from start
    vector<vector<int>> dist_from_start = bfs(start.x, start.y, grid, m, n);
    
    // BFS from home
    vector<vector<int>> dist_from_home = bfs(home.x, home.y, grid, m, n);
    
    int min_distance = INT_MAX;
    
    // For each umbrella shop, calculate total distance
    for (const Point& shop : shops) {
        int dist_to_shop = dist_from_start[shop.x][shop.y];
        int dist_to_home = dist_from_home[shop.x][shop.y];
        
        if (dist_to_shop != INT_MAX && dist_to_home != INT_MAX) {
            int total_dist = dist_to_shop + dist_to_home;
            min_distance = min(min_distance, total_dist);
        }
    }
    
    if (min_distance == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << min_distance << endl;
    }
    
    return 0;
}