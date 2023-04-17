#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 10 D

//just do bfs

//they can run maximum 20 * 50 meters before refilling

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        n += 2;
        vector<pair<int, int>> a(n);
        int start = 0;
        int dest = n - 1;
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                int dist = abs(a[i].first - a[j].first) + abs(a[i].second - a[j].second);
                if(dist <= 20 * 50) {
                    c[i].push_back(j);
                    c[j].push_back(i);
                }
            }
        }
        vector<bool> v(n, false);
        stack<int> s;
        v[start] = true;
        s.push(start);
        while(s.size() != 0){
            int cur = s.top();
            s.pop();
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i];
                if(v[next]) {
                    continue;
                }
                v[next] = true;
                s.push(next);
            }
        }
        cout << (v[dest]? "happy\n" : "sad\n");
    }
    
    return 0;
}
