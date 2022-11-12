#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Week 6A

//when you put a rook on the board, it makes it so that you can't put another rook in the columns or rows
//adjacent to it. 

//since the board is an n by n square, we just need to check if (n + 1) / 2 >= k to make sure that there is enough
//space for all the rooks. 

//we can just place the rooks along the diagonal if so. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        if((n + 1) / 2 < k) {
            cout << "-1\n";
            continue;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i % 2 == 0 && i == j && k != 0){
                    cout << "R";
                    k--;
                }
                else{
                    cout << ".";
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
