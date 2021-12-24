
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> c = vector<vector<int>>(n);
        for(int i = 0; i < n; i++){
            c.push_back(vector<int>());
        }
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            c[a - 1].push_back(b - 1);
            c[b - 1].push_back(a - 1);
        }
        vector<vector<int>> groups = vector<vector<int>>();
        vector<bool> v = vector<bool>(n);
        for(int i = 0; i < n; i++){
            if(!v[i]){
                groups.push_back(vector<int>());
                stack<int> s = stack<int>();
                s.push(i);
                v[i] = true;
                while(s.size() != 0){
                    int cur = s.top();
                    s.pop();
                    groups[groups.size() - 1].push_back(cur);
                    for(int a : c[cur]){
                        if(!v[a]){
                            v[a] = true;
                            s.push(a);
                        }
                    }
                }
            }
        }
        int hasStart, hasEnd;
        for(int i = 0; i < groups.size(); i++){
            for(int j : groups[i]){
                if(j == 0){
                    hasStart = i;
                }
                if(j == n - 1){
                    hasEnd = i;
                }
            }
        }
        if(hasStart == hasEnd){
            cout << "0\n";
            continue;
        }
        for(int i = 0; i < groups.size(); i++){
            sort(groups[i].begin(), groups[i].end());
        }
        vector<ll> fromStart = vector<ll>(groups.size());
        vector<ll> toEnd = vector<ll>(groups.size());
        for(int i = 0; i < groups.size(); i++){
            int a = 0;
            int b = 0;
            ll minDiff = 1000000;
            while(true){
                int aVal = groups[hasStart][a];
                int bVal = groups[i][b];
                minDiff = min(minDiff, (ll)abs(aVal - bVal));
                if(minDiff == 0){
                    break;
                }
                if(aVal < bVal){
                    if(a + 1 < groups[hasStart].size()){
                        a ++;
                    }
                    else {
                        break;
                    }
                }
                if(bVal < aVal){
                    if(b + 1 < groups[i].size()){
                        b ++;
                    }
                    else {
                        break;
                    }
                }
            }
            fromStart[i] = (ll) minDiff * (ll) minDiff;
        }
        for(int i = 0; i < groups.size(); i++){
            int a = 0;
            int b = 0;
            ll minDiff = 1000000;
            while(true){
                int aVal = groups[hasEnd][a];
                int bVal = groups[i][b];
                minDiff = min(minDiff, (ll)abs(aVal - bVal));
                if(minDiff == 0){
                    break;
                }
                if(aVal < bVal){
                    if(a + 1 < groups[hasEnd].size()){
                        a ++;
                    }
                    else {
                        break;
                    }
                }
                if(bVal < aVal){
                    if(b + 1 < groups[i].size()){
                        b ++;
                    }
                    else {
                        break;
                    }
                }
            }
            toEnd[i] = (ll) minDiff * (ll) minDiff;
        }
        ll ans = fromStart[0] + toEnd[0];
        for(int i = 1; i < groups.size(); i++){
            ans = min(ans, fromStart[i] + toEnd[i]);
        }
        cout << ans << endl;
    }    
    
    return 0;
}
