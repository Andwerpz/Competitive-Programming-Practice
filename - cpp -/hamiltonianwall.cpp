#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1766C

//if you can paint the wall, then you can start the brush at the left edge, where col = 0 to paint it. 

//assume that you can only paint a given wall if you start the brush at the center. If that is true, then 
//there must be a loop formed between all of the black cells that you can travel through, since it is necessary
//that you both travel left and right to paint all of the black cells. In this case, you can start from any cell to paint it, 
//so the original assumption is incorrect. 

//another observation is that you should always try to move in one direction + up and down, because if you ever move in the other direction, 
//you're stuck moving in that direction until you get stuck, or you've painted all the cells. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<string> a(2);
        cin >> a[0] >> a[1];
        bool isValid = false;
        int r = 0;
        int lastBlack = 0;
        for(int i = 0; i < n; i++){
            if(a[0][i] == 'B' || a[1][i] == 'B') {
                lastBlack = i;
            }
        }
        //cout << "LB " << lastBlack << endl;
        isValid = true;
        r = 0;
        for(int i = 0; i <= lastBlack; i++){
            if(a[r][i] == 'W'){
                isValid = false;
                break;
            }
            if(a[0][i] == 'B' && a[1][i] == 'B'){
                r = r == 0? 1 : 0;
            }
        }
        if(isValid) {
            cout << "YES\n";
            continue;
        }
        isValid = true;
        r = 1;
        for(int i = 0; i <= lastBlack; i++){
            if(a[r][i] == 'W'){
                isValid = false;
                break;
            }
            if(a[0][i] == 'B' && a[1][i] == 'B'){
                r = r == 0? 1 : 0;
            }
        }
        if(isValid){
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
    
    return 0;
}
