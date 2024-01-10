#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1909E

//a lamp will be toggled by any button that is it's divisor. Since only perfect squares have
//an odd amount of divisors, if you press every button, only perfect squares will be left on. 

//the ratio of perfect squares to non squares is sqrt(n) / n, and at n >= 20, we can get away with 
//pressing every button. 

//for n <= 19, we can have up to at most 3 lamps remaining, depending on the actual value of n. 
//It is sufficient just to test all subsets of at most 3 lamps to see if one works. 

//given a subset of lamps to turn on, you can test it by going from 1 to n, and toggling the lamp if it 
//is not in the correct state. Afterwards, you must check if the constraints given by the edges are satisfied. 

//it is possible to further optimize this solution by precomputing the answers to the smaller subsets,
//(size 1 and 2), but it runs fast enough without it (~2600 ms).

bool is_possible(int n, vector<int> end, vector<vector<int>>& c) {
    vector<bool> on(n, false);
    vector<bool> toggled(n, false);
    for(int i = 0; i < end.size(); i++){
        on[end[i] - 1] = true;
    }
    for(int i = 0; i < n; i++){
        if(on[i]) {
            toggled[i] = true;
            for(int j = i; j < n; j += i + 1) {
                on[j] = !on[j];
            }
        }
    }
    int nr_toggled = 0;
    for(int i = 0; i < n; i++){
        if(!toggled[i]){
            continue;
        }
        nr_toggled ++;
        for(int j = 0; j < c[i].size(); j++){
            int next = c[i][j];
            if(!toggled[next]) {
                return false;
            }
        }
    }
    cout << nr_toggled << "\n";
    for(int i = 0; i < n; i++){
        if(toggled[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
        }
        if(n >= 20){
            //just press all of them. 
            cout << n << "\n";
            for(int i = 1; i <= n; i++){
                cout << i << "\n";
            }
            continue;
        }
        //1 <= n < 20
        //at most 3 lamps can be on. Iterate through all possible subsets of at most 3 lamps
        bool is_valid = false;
        if(n >= 5) {
            for(int i = 1; i <= n && !is_valid; i++){
                //lamp i is on
                if(is_possible(n, {i}, c)) {
                    is_valid = true;
                }
                if(n >= 10) {
                    for(int j = i + 1; j <= n && !is_valid; j++){
                        //lamps i, j are on
                        if(is_possible(n, {i, j}, c)) {
                            is_valid = true;
                        }
                        if(n >= 15) {
                            for(int k = j + 1; k <= n && !is_valid; k++){
                                //lamps i, j, k are on. 
                                if(is_possible(n, {i, j, k}, c)) {
                                    is_valid = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(!is_valid) {
            cout << "-1\n";
        }
    }
    
    return 0;
}
