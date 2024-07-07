#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1989C

//if someone has a differing opinion between the two movies, always make them vote for the movie they 
//liked more. This works because if they have different opinions, then they can only like, one of the
//movies, and so the other one must be neutral or negative. 

//Now the remaining people have the same opinion for both movies. We can ignore the people who have 
//neutral opinions, and focus on the positive and negative ones. 

//With both the positive and negative opinions, we first want to try to equalize the two movies, 
//before trying to maximize them both. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        int rp = 0, rn = 0;
        int fm = 0, sm = 0;
        for(int i = 0; i < n; i++){
            if(a[i] != b[i]) {
                if(a[i] > b[i]) {
                    fm += a[i];
                }
                else {
                    sm += b[i];
                }
            }
            else {
                if(a[i] == 1){
                    rp ++;
                }
                else if(a[i] == -1){
                    rn ++;
                }
            }
        }
        if(fm > sm){
            swap(fm, sm);
        }
        {
            int diff = sm - fm;
            if(rp < diff) {
                fm += rp;
            }
            else {
                fm += diff;
                rp -= diff;
                fm += rp / 2;
                sm += rp / 2 + (rp % 2);
            }
        }
        {
            int diff = sm - fm;
            if(rn < diff) {
                sm -= rn;
            }
            else {
                sm -= diff;
                rn -= diff;
                fm -= rn / 2;
                sm -= rn / 2 + (rn % 2);
            }
        }
        cout << min(fm, sm) << "\n";
    }
    
    return 0;
}