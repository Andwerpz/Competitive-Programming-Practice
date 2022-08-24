#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1715D

//since the question asks us to make the lexographically least array possible, we can optimize
//a[i] without regard to anything to the right, but we need to still keep in mind what is to the left. 

//The idea is to first precompute for each a[i], what is the maximum value it can be; 'm', given the constraints. 
//Then, we iterate through the array, starting from the left. For each a[i], we determine the slack it needs to pick
//up from the left by looking at 'a', and the slack from the right, 'm'. 

//note that self edges are possible, so if you see one, then the weight on the edge is the value of a[i].  

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> m(n);
    vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>(0));   //i, x;
    for(int i = 0; i < q; i++){
        int u, v, x;
        cin >> u >> v >> x;
        u--;
        v--;
        c[u].push_back({v, x});
        c[v].push_back({u, x});
    }
    for(int i = 0; i < n; i++){
        if(c[i].size() == 0){
            continue;
        }
        m[i] = c[i][0].second;
        for(int j = 1; j < c[i].size(); j++){
            m[i] &= c[i][j].second;
        }
    }
    for(int i = 0; i < n; i++){
        int lReq = 0;
        int rReq = 0;
        int selfReq = 0;
        for(int j = 0; j < c[i].size(); j++){
            if(c[i][j].first < i){  //lReq
                lReq |= ~a[c[i][j].first] & c[i][j].second;
            }
            else if(c[i][j].first > i) {    //rReq
                rReq |= ~m[c[i][j].first] & c[i][j].second;
            }
            else{   //selfReq
                selfReq = c[i][j].second;
                break;
            }
        }
        a[i] = lReq | rReq | selfReq;
    }
    for(int i : a){
        cout << i << " ";
    }
    cout << "\n";
    
    return 0;
}
