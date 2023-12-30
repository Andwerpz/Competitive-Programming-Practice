#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 12-01-23 Div. 1 G

//intuitively, this is a 2 pointer problem, but it's kinda hard to see why it would work. 

//to solve, for each left bound l, we maintain the largest right bound r, where at most 1 value in the range 
//[l, r) appears more than once. The element that appears more than once we call the dominant element, and we keep
//track of this as well. 

//to update the answer, we just notice that if a segment has a dominant element, then any segment that is created
//between two dominant elements will be valid. So, if when extending our right bound and we see that a[r] == dom, then
//we add to the answer the count of the dominant element in the interval, or cnt[dom]. 

//when moving the left bound, be careful to properly maintain the dominant element. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int dom = -1;
    vector<ll> cnt(n + 1, 0);
    int r = 0;
    ll ans = 0;
    for(int i = 0; i < n; i++){
        while(r != n) {
            if(dom == -1){
                cnt[a[r]] ++;
                if(cnt[a[r]] > 1){
                    ans ++;
                    dom = a[r];
                    //cout << "FOUND NEW DOM : " << a[r] << " " << r << "\n";
                }
            }
            else {
                if(a[r] == dom) {
                    ans += cnt[a[r]];
                    cnt[a[r]] ++;
                    //cout << "FOUND DOM : " << r << "\n";
                }
                else {
                    if(cnt[a[r]] == 1){
                        break;
                    }
                    cnt[a[r]] ++;
                }
            }
            r ++;
        }
        cnt[a[i]] --;
        if(cnt[dom] < 2){
            dom = -1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
