#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1691B

//just give each person a shoe of the same size they originally had. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> g(0);
        int prev = -1;
        int ptr = -1;
        for(int i = 0; i < n; i++){
            if(a[i] != prev){
                prev = a[i];
                ptr ++;
                g.push_back(vector<int>(0));
            }
            g[ptr].push_back(i + 1);
        }
        bool isValid = true;
        for(int i = 0; i < g.size(); i++){
            if(g[i].size() == 1){
                isValid = false;
                break;
            }
        }
        if(isValid){
            for(int i = 0; i < g.size(); i++){
                for(int j = 1; j <= g[i].size(); j++){
                    cout << g[i][(j % g[i].size())] << " ";
                }
            }
            cout << "\n";
        }
        else{
            cout << "-1\n";
        }
    }
    
    return 0;
}
