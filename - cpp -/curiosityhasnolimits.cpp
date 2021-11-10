
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1031B

//since the numbers are so small in the sequence, you can represent this problem with a graph.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n - 1);
    vector<int> b(n - 1);
    for(int i = 0; i < n - 1; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n - 1; i++){
        cin >> b[i];
    }
    vector<vector<int>> c(n);
    for(int i = 0; i < n; i++){
        c[i] = vector<int>(4, -1);
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                if((j | k) == a[i] && (j & k) == b[i]){
                    if(i == 0){
                        c[i + 1][k] = j;
                    }
                    else{
                        if(c[i][j] != -1){
                            c[i + 1][k] = j;
                        }
                    }
                }
            }
        }
    }
    vector<int> ans(n);
    int pointer = -1;
    for(int i = 0; i < 4; i++){
        if(c[n - 1][i] != -1){
            pointer = i;
            break;
        }
    }
    //cout << "POINTER: " << pointer << endl;
    if(pointer == -1){
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
        ans[n - 1] = pointer;
        for(int i = n - 1; i > 0; i--){
            pointer = c[i][pointer];
            ans[i - 1] = pointer;
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}



