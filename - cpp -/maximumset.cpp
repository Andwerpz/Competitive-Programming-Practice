#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1796C

//notice that if you sort a beautiful set, s, in ascending order, then s[i] is always a multiple of s[i - 1]. 

//to figure out how large the largest set will be, we can start with l. The minimum number that is a multiple of l
//that we can add to the set is l * 2, so we add that to the set, and then try to add another number, l * 4 and so on. 

//if the length of the largest set == 1, then the amount of sets is simply r - l + 1, or just the set of 1 number for each number
//in the interval [l, r]. 

//else, the length is 2 or greater. 

//now, we want to figure out how many unique largest sets we can make. Notice that when generating the set, we should always multiply
//by 2, or 3. If we multiply by 4, then it's just the same as multiplying by 2, 2 times, thus we can make a bigger set. And also, if we multiply
//by 3, 2 times, then it's greater than multiplying by 2, 3 times. So, the largest set consists of either only multiplying by 2, or multiplying 
//by 3 once, and multiplying by 2 the rest of the times. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    ll mod = 998244353;
    while(t-- > 0){
        ll l, r;
        cin >> l >> r;
        ll len = 1;
        ll ptr = l;
        while(ptr * 2 <= r){
            ptr *= 2;
            len ++;
        }
        cout << len << " ";
        if(len == 1){
            cout << r - l + 1 << "\n";
            continue;
        }
        ll ans = 0;
        ptr = r;
        for(int i = 0; i < len - 1; i++){
            ptr /= 2;
        }
        ans += ptr - l + 1;
        ptr = r;
        ptr /= 3;
        for(int i = 0; i < len - 2; i++){
            ptr /= 2;
        }
        ans += max((ptr - l + 1) * (len - 1), (ll) 0);
        cout << ans << "\n";
    }
    
    return 0;
}
