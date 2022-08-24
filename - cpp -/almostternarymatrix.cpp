#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1699B

//there exists a tileable 2x2 pattern that satisfies the condition in the problem:

//1 0
//0 1

//we can tile it like so to fit a 4x6 rectangle:

//1 0 0 1 1 0
//0 1 1 0 0 1
//0 1 1 0 0 1
//1 0 0 1 1 0

//notice that all we do is flip the parity of a few columns first:

//1 0 0 1 1 0
//1 0 0 1 1 0
//1 0 0 1 1 0
//1 0 0 1 1 0

//and then we flip the parity of a few rows:

//1 0 0 1 1 0
//0 1 1 0 0 1
//0 1 1 0 0 1
//1 0 0 1 1 0

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int next = 0;
                if(i % 4 == 1 || i % 4 == 2){
                    next = (next + 1) % 2;
                }
                if(j % 4 == 1 || j % 4 == 2){
                    next = (next + 1) % 2;
                }
                cout << next << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
