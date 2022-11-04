#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 5D

//the upper bound on the number of operations is just the number of unique elements.

//two indices, i, j, in a are 'opposite' to each other if j = n - i - 1. 
//notice that elements at opposite indices must be equal in order for a to be a palindrome. 

//say that elements a[i] and a[j] are connected if they are opposite to each other. If we find a connected 
//component of elements, then it requires num elements in component - 1 moves to make them all equal. 

//thus, the answer is number unique elements - num connected components. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> unique;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
        unique.insert(a[i]);
    }
    int ans = unique.size();
    vector<set<int>> c(2e5, set<int>());
    for(int i = 0; i < (n + 1) / 2; i++){
        int cur = a[i];
        int opp = a[n - 1 - i];
        c[cur].insert(opp);
        c[opp].insert(cur);
    }
    vector<bool> v(2e5, false);
    for(int i : unique) {
        if(v[i]){
            continue;
        }
        ans --;
        v[i] = true;
        stack<int> s;
        s.push(i);
        while(s.size() != 0){
            int next = s.top();
            s.pop();
            for(int j : c[next]) {
                if(v[j]){
                    continue;
                }
                v[j] = true;
                s.push(j);
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
