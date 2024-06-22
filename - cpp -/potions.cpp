#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1526 C1, C2

//consider drinking every potion going from left to right. If you health ever becomes negative, you know you probably
//should've not drunk some negative value potion before you, but which one should you have not drunk?

//the answer is to not drink the most negative potion before you. You can figure out the value using a priority queue. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    priority_queue<ll> q;
    ll sum = 0;
    int ans = 0;
    for(int i = 0; i < n; i++){
        ll a;
        cin >> a;
        sum += a;
        q.push(-a);
        ans ++;
        while(sum < 0){
            ans --;
            sum += q.top();
            q.pop();
        }
    }
    cout << ans << "\n";
    
    return 0;
}