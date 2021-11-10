
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codechef - CHECHOC

//tile the grid in a checkerboard pattern, with the black tile in one of the corners. On the black tile, put the higher value item, and on the white tiles, put the remainder.

//special case: 1x1. This case is different since if x > y, then you can just put x in the only tile.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, m, x, y;
        cin >> n >> m >> x >> y;
        int ans = 0;
        if(n * m == 1){
            ans = x;
        }
        else if(x * 2 <= y){
            ans = n * m * x;
        }
        else {
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    int next = 0;
                    if(x < y){
                        next = (i + j) % 2 == 0? x : y - x;
                    }
                    else{
                        next = (i + j) % 2 == 0? y : 0;
                    }
                    ans += next;
                    //cout << next << " ";
                }
                //cout << "\n";
            }
        }
        cout << ans << endl;
    }

    return 0;
}



