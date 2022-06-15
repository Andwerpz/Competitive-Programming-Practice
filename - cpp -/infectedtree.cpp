#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1689C

//simple recursive solution due to binary tree structure. 

int getAns(vector<vector<int>> &c, int parent, int t, bool isRoot) {
    if(c[t].size() == 1 - isRoot) {
        return 1;
    }
    else if(c[t].size() == 2 - isRoot){
        return 2;
    }
    else{
        int a = c[t][0];
        int b = c[t][1];
        if(a == parent){
            a = c[t][2];
        }
        else if(b == parent){
            b = c[t][2];
        }
        return 2 + min(getAns(c, t, a, false), getAns(c, t, b, false));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n;
        cin >> n;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c[a].push_back(b);
            c[b].push_back(a);
        }
        //cout << getAns(c, 0, true) << "\n";
        cout << (n - getAns(c, -1, 0, true)) << "\n";
    }
    
    return 0;
}
