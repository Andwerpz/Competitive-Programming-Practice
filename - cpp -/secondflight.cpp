#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Meta Hacker Cup 2022 D

//this solution too slow :(

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin("second_flight_input.txt");
    ofstream fout("second_flight_output.txt");
    
    int t;
    fin >> t;
    int caseNum = 0;
    while(t-- > 0){
        caseNum ++;
        int n, m, q;
        fin >> n >> m >> q;
        vector<vector<vector<int>>> c(n, vector<vector<int>>(0, vector<int>(0)));
        for(int i = 0; i < m; i++){
            int a, b, cnt;
            fin >> a >> b >> cnt;
            a--;
            b--;
            c[a].push_back({b, cnt});
            c[b].push_back({a, cnt});
        }
        fout << "Case #" << caseNum << ": ";
        for(int i = 0; i < q; i++){
            int x, y;
            fin >> x >> y;
            x--;
            y--;
            map<int, ll> inter;
            for(int j = 0; j < c[x].size(); j++){
                inter.insert({c[x][j][0], (ll) c[x][j][1]});
            }
            ll ans = 0;
            if(inter.find(y) != inter.end()){
                ans += inter.find(y) -> second * 2;
            }
            for(int j = 0; j < c[y].size(); j++) {
                int next = c[y][j][0];
                ll cnt = (ll) c[y][j][1];
                if(inter.find(next) != inter.end()){
                    ans += min(inter.find(next) -> second, cnt);
                }
            }
            fout << ans << " ";
        }
        cout << "done with tc " << caseNum << endl;
        fout << endl;
    }
    
    return 0;
}
