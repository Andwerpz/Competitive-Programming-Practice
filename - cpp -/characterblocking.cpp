#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1840E

//just keep a running count of how many pairs of characters are not the same. 

//operations of type 1 will decrease the count by one if the blocked pair of characters are different.

//operations of type 2 will change the count by at most 2, depending on the characters swapped. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        vector<string> a(2, "");
        cin >> a[0] >> a[1];
        int tblock, q;
        cin >> tblock >> q;
        priority_queue<pair<int, int>> qu;
        int time = 0;
        int nrDiff = 0;
        for(int i = 0; i < a[0].size(); i++){
            nrDiff += (a[0][i] != a[1][i]);
        }
        //cout << "INIT : " << nrDiff << "\n";
        while(q--) {
            int type;
            cin >> type;
            //deal with unblockings
            while(qu.size() != 0 && -qu.top().first == time) {
                //cout << "UNBLOCK : " << -qu.top().first << " " << qu.top().second << "\n";
                int ind = qu.top().second;
                qu.pop();
                if(a[0][ind] != a[1][ind]) {
                    nrDiff ++;
                }
            }
            if(type == 1){
                //block
                int ind;
                cin >> ind;
                ind--;
                if(a[0][ind] != a[1][ind]){
                    nrDiff --;
                }
                qu.push({-(time + tblock), ind});
            }
            else if(type == 2){
                //swap
                int s1, s2, i1, i2;
                cin >> s1 >> i1 >> s2 >> i2;
                s1--;
                s2--;
                i1--;
                i2--;
                if(i1 == i2) {
                    swap(a[s1][i1], a[s2][i2]);
                }
                else {
                    int before = (a[0][i1] != a[1][i1]) + (a[0][i2] != a[1][i2]);
                    swap(a[s1][i1], a[s2][i2]);
                    int after = (a[0][i1] != a[1][i1]) + (a[0][i2] != a[1][i2]);
                    int diff = after - before;
                    nrDiff += diff;
                }
            }
            else if(type == 3){
                //equality check
                cout << (nrDiff == 0? "YES" : "NO") << "\n";
            }
            time ++;
        }
    }
    
    return 0;
}
