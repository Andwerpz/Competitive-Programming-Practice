#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES 1676

//standard dsu problem. 

int find(vector<int>& c, int i){
    if(i == c[i]){
        return i;
    }
    return c[i] = find(c, c[i]);
}

bool unify(vector<int>& c, vector<int>& s, int i, int j) {
    int a = find(c, i);
    int b = find(c, j);
    if(a == b){
        return false;
    }
    c[b] = a;
    s[a] += s[b];
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> c(n);   //dsu tree
    vector<int> s(n, 1);
    for(int i = 0; i < n; i++){
        c[i] = i;
    }
    int maxSize = 1;
    int numComponents = n;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        if(unify(c, s, a, b)) {
            int aRoot = find(c, a);
            numComponents --;
            maxSize = max(maxSize, s[aRoot]);
        }
        cout << numComponents << " " << maxSize << "\n";
    }
    
    return 0;
}
