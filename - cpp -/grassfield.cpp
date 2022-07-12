#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1701A

//notice that in one move, you can remove grass from any 3 tiles of your choosing. So if all tiles have
//grass, then the minimum amount of moves is 2. 

//if no tiles have grass, then 0 moves are required, else, one move is required. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int cnt = 0;
        for(int i = 0; i < 4; i++){
            int next;
            cin >> next;
            cnt += next;
        }
        cout << (cnt == 0? 0 : (cnt == 4? 2 : 1)) << "\n";
    }
    
    return 0;
}
