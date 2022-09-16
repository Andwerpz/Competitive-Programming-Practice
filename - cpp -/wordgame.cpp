#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC 2022 Week 1 C

//just brute force, the inputs are small enough. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        map<string, int> m;
        vector<vector<string>> a(3, vector<string>(n));
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < n; j++){
                cin >> a[i][j];
                if(m.find(a[i][j]) == m.end()){
                    m.insert({a[i][j], 0});
                }
                m.find(a[i][j]) -> second ++;
            }
        }
        for(int i = 0; i < 3; i++){
            int cnt = 0;
            for(int j = 0; j < n; j++){
                int c = m.find(a[i][j]) -> second;
                if(c == 1){
                    cnt += 3;
                }
                else if(c == 2){
                    cnt += 1;
                }
            }
            cout << cnt << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
