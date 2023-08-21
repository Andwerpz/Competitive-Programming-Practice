#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1858B

//note that by removing exactly one cookie seller, we can make the amount of eaten cookies go down by at most 1. 

//so, we just try to remove each cookie seller. If for every cookie seller, removing them doesn't decrease the amount of cookies, 
//then the amount of cookie sellers returned should be m, not 0. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, d;
        cin >> n >> m >> d;
        map<int, int> loc_map;
        for(int i = 0; i < m; i++){
            int s;
            cin >> s;
            if(loc_map.find(s) == loc_map.end()) {
                loc_map.insert({s, 0});
            }
            loc_map[s] ++;
        }
        loc_map.insert({1, 2});
        int nr_reduce = 0;
        int nr_cookies = 0;
        for(auto i = loc_map.begin(); i != loc_map.end(); i++){
            nr_cookies ++;
            if(i -> first == 1){
                continue;
            }
            int cur = i -> first;
            auto ptr = i;
            ptr --;
            int prev = ptr -> first;
            ptr ++;
            ptr ++;
            int next = -1;
            if(ptr == loc_map.end()) {
                next = n + 1;
            }
            else {
                next = ptr -> first;
            }
            int dold = (cur - prev - 1) / d + (next - cur - 1) / d;
            int dnew = (next - prev - 1) / d;
            //cout << prev << " " << cur << " " << next << " " << dold << " " << dnew << "\n";
            if(i -> second == 1 && dold == dnew){
                nr_reduce ++;
            }
            nr_cookies += (cur - prev - 1) / d;
            if(ptr == loc_map.end()) {
                nr_cookies += (next - cur - 1) / d;
            }
        }
        if(loc_map.rbegin() -> first == 1){
            nr_cookies += (n - 1) / d;
        }
        if(nr_reduce == 0){
            nr_reduce = m;
        }
        else {
            nr_cookies --;
        }
        cout << nr_cookies << " " << nr_reduce << "\n";
    }
    
    return 0;
}
