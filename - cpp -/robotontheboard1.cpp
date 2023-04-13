#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces 1607E

//instead of thinking of the robot as moving around, think of the possible valid starting positions shrinking as the robot
//moves around. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        int minR = 0;
        int minC = 0;
        int maxR = 0;
        int maxC = 0;
        int r = 0;
        int c = 0;
        int ar = 1;
        int ac = 1;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'L') {
                c --;
            }
            else if(s[i] == 'R'){
                c ++;
            }
            else if(s[i] == 'U'){
                r --;
            }
            else if(s[i] == 'D'){
                r ++;
            }
            minR = min(minR, r);
            maxR = max(maxR, r);
            minC = min(minC, c);
            maxC = max(maxC, c);
            if(maxR - minR + 1 > n || maxC - minC + 1 > m){
                break;
            }
            ar = 1 - minR;
            ac = 1 - minC;
        }
        cout << ar << " " << ac << "\n";
    }
    
    return 0;
}
