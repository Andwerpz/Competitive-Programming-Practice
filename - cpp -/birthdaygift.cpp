#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1946D

//note that for a bit to not appear in the final OR sum, it needs to occur in every XOR segment an even amount of times. 
//if we give a restriction in the form of choosing some bits to exclude from the final XOR sum, all other bits we don't care,
//we can solve for the maximum k under this restriction in linear time using a greedy algorithm. 

//from here, we can notice that only a few restrictions are actually relevant. Namely, we can choose a bit that is on in x,
//and force set it to off. Then, any bit that is lower in significance to that bit can be turned on or off without exceeding x.
//any bit above needs to stay off if it's originally off, otherwise we don't care. 

//we just do a trial for every bit in x. 

//no restrictions are on the ith bit if (1 << i) is present in allow
//returns -1 if is not possible
int solve(vector<int>& a, int allow) {
    int ans = 0;
    vector<int> b_cnt(30, 0);
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < 30; j++){
            b_cnt[j] += (a[i] & (1 << j)) != 0;
        }
        bool incr = true;
        for(int j = 0; j < 30; j++){
            if((allow & (1 << j)) == 0 && b_cnt[j] % 2) {
                incr = false;
            }
        }
        ans += incr;
    }
    for(int i = 0; i < 30; i++){
        if((allow & (1 << i)) == 0 && b_cnt[i] % 2) {
            return -1;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = -1;
        ans = max(ans, solve(a, x));
        for(int i = 0; i < 30; i++){
            int allow = x;
            for(int j = 0; j <= i; j++){
                allow |= (1 << j);
            }
            for(int j = i + 1; j < 30; j++){
                if(allow & (1 << j)) {
                    allow ^= (1 << j);
                    ans = max(ans, solve(a, allow));
                    break;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
