#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1860C

//lets say an index i is a 'dead end' if when the chip is moved there, there are no more valid moves. 
//in order for i to be a dead end, it must be less than the minimum in the range [0, i). 

//lets say that index i is 'dead end adjacent' if the only valid moves from index i are dead ends. 

//if the chip starts at a dead end cell, then bob automatically wins. If the chip starts at a cell that is not
//a dead end, and is not dead end adjacent, then bob can just move the chip to a dead end adjacent cell, and bob wins. 

//thus, the only way that alice wins is if she starts the chip on a dead end adjacent cell. Thus, we just need to count the number of
//dead end adjacent cells. 

//we can do this in linear time. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        int min_nr = n + 1;
        int min_dead_adj = n + 1;
        int ans = 0;
        for(int i = 0; i < n; i++){
            int next = a[i];
            if(next < min_nr) {
                //dead end
                min_nr = min(min_nr, next);
            }
            else if(next < min_dead_adj) {
                //can only move to dead end cells
                min_dead_adj = min(min_dead_adj, next);
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
