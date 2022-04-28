#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 339D

//we can just simulate the problem statement using a seg tree. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> t(n + 1);
    int tSize = pow(2, n);
    for(int i = 0; i < n + 1; i++){
        t[i] = vector<int>(tSize);
        tSize /= 2;
    }
    tSize = pow(2, n);
    for(int i = 0; i < tSize; i++){
        cin >> t[0][i];
    }
    for(int i = 1; i < t.size(); i++){
        for(int j = 0; j < t[i].size(); j++){
            if(i % 2 == 1) {t[i][j] = t[i - 1][j * 2] | t[i - 1][j * 2 + 1];}
            else {t[i][j] = t[i - 1][j * 2] ^ t[i - 1][j * 2 + 1];}
        }
    }
    for(int i = 0; i < m; i++){
        int p, b;
        cin >> p >> b;
        p--;
        t[0][p] = b;
        for(int j = 1; j < t.size(); j++){
            p /= 2;
            if(j % 2 == 1){t[j][p] = t[j - 1][p * 2] | t[j - 1][p * 2 + 1];}
            else{t[j][p] = t[j - 1][p * 2] ^ t[j - 1][p * 2 + 1];}
        }
        cout << t[t.size() - 1][0] << endl;
    }

    return 0;
}
