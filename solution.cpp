#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct State {
    int x, y, has_umbrella;
    State(int _x, int _y, int _has) : x(_x), y(_y), has_umbrella(_has) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    int start_x = -1, start_y = -1, home_x = -1, home_y = -1;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start_x = i; start_y = j;
            } else if (grid[i][j] == 3) {
                home_x = i; home_y = j;
            }
        }
    }
    
    if (start_x == -1 || home_x == -1) {
        cout << -1 << endl;
        return 0;
    }
    
    // BFS with state: (x, y, has_umbrella)
    vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(2, -1)));
    queue<State> q;
    
    // Start without umbrella
    dist[start_x][start_y][0] = 0;
    q.push(State(start_x, start_y, 0));
    
    int answer = -1;
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        // If we reach home with umbrella, we found a solution
        if (curr.x == home_x && curr.y == home_y && curr.has_umbrella) {
            answer = dist[curr.x][curr.y][curr.has_umbrella];
            break;
        }
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = curr.x + dx[dir];
            int ny = curr.y + dy[dir];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != 1) {
                int next_has_umbrella = curr.has_umbrella;
                if (grid[nx][ny] == 4) {
                    next_has_umbrella = 1; // Pick up umbrella
                }
                
                if (dist[nx][ny][next_has_umbrella] == -1) {
                    dist[nx][ny][next_has_umbrella] = dist[curr.x][curr.y][curr.has_umbrella] + 1;
                    q.push(State(nx, ny, next_has_umbrella));
                }
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}