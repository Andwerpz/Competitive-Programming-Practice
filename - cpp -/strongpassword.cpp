#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1845C

//we just need to make sure that all possible passwords are contained within the password database. 

//to do this, we can use a greedy method: 
//maintain a pointer, r, that starts at -1. 
//for each position, find the first appearance of all valid digits for that position, that is to the right of r. 
//set r to the position of the last digit. 

//if r ever goes out of bounds, that means that you couldn't find a digit, which means that all possible passwords
//are not contained within the database. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int m;
        cin >> m;
        string l, r;
        cin >> l >> r;
        int rptr = 0;
        bool valid = false;
        for(int i = 0; i < m; i++){
            int lb = l[i] - '0';
            int rb = r[i] - '0';
            set<int> v;
            for(; rptr < s.size(); rptr++){
                int dig = s[rptr] - '0';
                if(lb <= dig && dig <= rb) {
                    v.insert(dig);
                }
                if(v.size() == rb - lb + 1) {
                    break;
                }
            }
            rptr ++;
            //cout << "VSIZE : " << v.size() << "\n";
            //cout << "R : " << rptr << "\n";
            if(v.size() != rb - lb + 1){
                valid = true;
                break;
            }
        }
        cout << (valid? "YES\n" : "NO\n");
    }
    
    return 0;
}
