#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2011 E

//since there are only 10^6 total cells, and 20 queries, we might be able to get away with testing every cell
//for each query

//the problem is that the naive method to test a cell involves doing a m^2 search, which is too slow. 

//instead, we can do some precomputation using a prefix sum. Rotate the original array by 45 degrees, so that 
//the diamond shaped area corresponding to some distance around a cell in the original array turns into a
//rectangular area. 

//then, we do prefix sum over this new array to find how many coffee shops are visitable from some cell 
//from some distance. 

pair<int, int> convert(int r, int c, int dx) {
    return {dx + r - c, r + c};
}

void solve(int dx, int dy) {
    dx = max(dx, dy);
    vector<vector<int>> a(dx * 2 + 1, vector<int>(dx * 2 + 1, 0));
    vector<vector<pair<int, int>>> inv_convert(dx * 2 + 1, vector<pair<int, int>>(dx * 2 + 1, {-1, -1}));
    for(int i = 0; i < dx; i++){
        for(int j = 0; j < dx; j++){
            pair<int, int> rc = convert(i, j, dx);
            int r = rc.first;
            int c = rc.second;
            inv_convert[r][c] = {i, j};
        }
    }
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;
        pair<int, int> rc = convert(x, y, dx);
        int r = rc.first;
        int c = rc.second;
        a[r][c] ++;
    }
    // for(int i = 0; i < a.size(); i++){
    //     for(int j = 0; j < a.size(); j++){
    //         cout << a[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < a[0].size(); j++){
            if(i != 0){
                a[i][j] += a[i - 1][j];
            }
            if(j != 0){
                a[i][j] += a[i][j - 1];
            }
            if(i != 0 && j != 0){
                a[i][j] -= a[i - 1][j - 1];
            }
        }
    }
    // cout << "PRESUM : " << "\n";
    // for(int i = 0; i < a.size(); i++){
    //     for(int j = 0; j < a.size(); j++){
    //         cout << a[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    while(q--){
        int m;
        cin >> m;
        int most_coffee = -1;
        pair<int, int> best_loc = {0, 0};
        for(int i = 0; i < a.size(); i++){
            for(int j = 0; j < a[0].size(); j++){
                if(inv_convert[i][j].first == -1){
                    continue;
                }
                int r_min = i - m;
                int r_max = i + m;
                int c_min = j - m;
                int c_max = j + m;
                r_min --;
                c_min --;
                int curans = 0;
                r_max = min(r_max, (int) a.size() - 1);
                c_max = min(c_max, (int) a.size() - 1);
                curans += a[r_max][c_max];
                if(r_min >= 0) {
                    curans -= a[r_min][c_max];
                }
                if(c_min >= 0){
                    curans -= a[r_max][c_min];
                }
                if(r_min >= 0 && c_min >= 0){
                    curans += a[r_min][c_min];
                }
                if(curans > most_coffee) {
                    most_coffee = curans;
                    best_loc = inv_convert[i][j];
                }
                else if(curans == most_coffee) {
                    if(inv_convert[i][j].second < best_loc.second) {
                        best_loc = inv_convert[i][j];
                    }
                    else if(inv_convert[i][j].second == best_loc.second) {
                        if(inv_convert[i][j].first < best_loc.first) {
                            best_loc = inv_convert[i][j];
                        }
                    }
                }
            }
        }
        cout << most_coffee << " " << "(" << best_loc.first + 1 << "," << best_loc.second + 1 << ")" << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    int dx, dy;
    cin >> dx >> dy;
    int casenum = 1;
    while (true) {
        cout << "Case " << casenum << ":" << "\n";
        casenum ++;
        solve(dx, dy);
        cin >> dx >> dy;
        if (!dx) {
            cin >> dx >> dx;
            break;
        }
    }

    return 0;
}
