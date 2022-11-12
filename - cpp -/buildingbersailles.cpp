#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    set<string> s;
    for(int i = 0; i < n; i++){
        string next;
        cin >> next;
        s.insert(next);
    }
    vector<vector<string>> sequences(0);
    for(int i = 0; i < m; i++){
        int a;
        cin >> a;
        vector<string> next(a);
        for(int j = 0; j < a; j++){
            cin >> next[j];
            cout << next[j] << " ";
            s.erase(next[j]);
        }
    }
    for(string next : s){
        cout << next << " ";
    }
    cout << "\n";
    
    return 0;
}
