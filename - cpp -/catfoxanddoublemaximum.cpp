#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1973C

//initially thought this was guessforces, but the editorial has a nice way to think of the solution. 

//first, note that the maximum amount of local maxima that we can ever have is n / 2 - 1. This is due to space
//constraints in the array; a local maxima can never neighbor another local maxima. 

//next, imagine that p[0] = n. If we make all the even indexed elements into local maxima, and odd indexed into local
//minima, then it might work. So, we assign to all the even indexed elements all numbers n / 2 + 1 or higher, and all
//the odd elements, n / 2 or lower. 

//Note that since p[0] = n, all the even elements will be at least n + 1 or higher, and all the odd elements will be n 
//or lower. If n is not on an even index, then we can reverse the array, solve it, and then reverse the answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        bool rev = false;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(i % 2 == 0 && a[i] == n){
                rev = true;
            }
        }
        if(rev) {
            reverse(a.begin(), a.end());
        }
        vector<int> ans(n, -1);
        priority_queue<pair<int, int>> q;
        for(int i = 0; i < n; i++){
            q.push({-a[i] + (i % 2 == 0? 0 : n), i});
        }
        for(int i = n; i >= 1; i--){
            int next = q.top().second;
            q.pop();
            ans[next] = i;
        }
        if(rev){
            reverse(ans.begin(), ans.end());
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
