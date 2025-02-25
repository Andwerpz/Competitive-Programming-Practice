#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Topcoder - 16061

//uhh constructive problem. Just place cells on rows, there's plenty of space. 

class ThreeNeighbors {
public:
    vector<string> construct(int n) {
        int _n = n;
        const int N = 50;
        vector<string> g(N, string(N, '.'));
        for(int i = 0; i < 13; i++){
            g[i * 4][0] = 'X';
            g[i * 4 + 1][1] = 'X';
            for(int j = 2; j < N; j++){
                if(n != 0) {
                    g[i * 4 + (j % 2)][j] = 'X';
                    n --;
                }
            }
        }
        //doublecheck answer
        vi dr = {-1, -1, -1, 0, 0, 1, 1, 1};
        vi dc = {-1, 0, 1, -1, 1, -1, 0, 1};
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(g[i][j] == 'X') continue;
                int cnt = 0;
                for(int k = 0; k < 8; k++){
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
                    cnt += g[nr][nc] == 'X';
                }
                if(cnt == 3) _n --;
            }
        }
        assert(_n == 0);
        return g;
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = ThreeNeighbors();
    vector<string> ret = c.construct(arg0);
    for (auto& item : ret) { cout << item << "\n"; }
}