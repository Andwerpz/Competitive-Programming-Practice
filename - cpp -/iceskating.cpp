#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 5C

//to connect two connected components of snow piles requires one snow pile. It is impossible to connect three
//connected components of snow piles at once with one snow pile, because that implies that two of the connected 
//components are already connected, making it so that you're just connecting two components. 

//thus, the answer is simply the total number of connected components - 1. To figure out connections, you just
//need to keep track for each row and column, what snow piles are on them. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> r(1000, vector<int>(0));
    vector<vector<int>> c(1000, vector<int>(0));
    vector<pair<int, int>> a(0);
    for(int i = 0; i < n; i++){
        pair<int, int> next;
        cin >> next.first >> next.second;
        next.first --;
        next.second --;
        a.push_back(next);
        r[next.first].push_back(i);
        c[next.second].push_back(i);
    }
    int ans = 0;
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        v[i] = true;
        stack<int> s;
        s.push(i);
        ans ++;
        while(s.size() != 0) {
            int next = s.top();
            s.pop();
            int row = a[next].first;
            int col = a[next].second;
            for(int j : r[row]) {
                if(v[j]) {
                    continue;
                }
                v[j] = true;
                s.push(j);
            }
            for(int j : c[col]) {
                if(v[j]) {
                    continue;
                }
                v[j] = true;
                s.push(j);
            }
        }
    }
    cout << (ans - 1) << "\n";
    
    return 0;
}
