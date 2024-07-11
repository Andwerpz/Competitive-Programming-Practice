#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1986E

//the problem asks you to make the array into a palindrome only by adding k, and by rearranging the elements. 

//notice that two numbers can only become equal if their remainders mod k are equal. So, first for every remainder
//mod k, record the number of elements in the array. 

//then, if n is even, all categories must be even, if n is odd, exactly 1 category must be odd. 

//when matching up elements within the same category, it's optimal to sort them, and then greedily take pairs
//in sorted order. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        map<int, vector<int>> m;
        for(int i = 0; i < n; i++){
            m[a[i] % k].push_back(a[i] / k);
        }
        bool too_many_odd = false;
        int odd_rem = -1;
        for(auto i = m.begin(); i != m.end(); i++){
            if(i -> second.size() % 2 == 0){
                continue;
            }
            if(odd_rem == -1){
                odd_rem = i -> first;
                continue;
            }
            too_many_odd = true;
        }
        if(too_many_odd || (odd_rem != -1 && n % 2 == 0)) {
            cout << "-1\n";
            continue;
        }
        int ans = 0;
        for(auto i = m.begin(); i != m.end(); i++){
            vector<int> v = i -> second;
            sort(v.begin(), v.end());
            if(v.size() % 2 == 0){
                for(int j = 0; j < v.size(); j += 2){
                    ans += v[j + 1] - v[j];
                }
            }
            else {
                vector<int> pfx(1, 0);
                for(int j = 0; j < v.size(); j += 2){
                    pfx.push_back(v[j + 1] - v[j]);
                    pfx[pfx.size() - 1] += pfx[pfx.size() - 2];
                }
                int cans = pfx[v.size() / 2];
                int sfx_sum = 0;
                for(int j = v.size() - 2; j >= 0; j -= 2){
                    sfx_sum += v[j + 1] - v[j];
                    cans = min(cans, sfx_sum + pfx[j / 2]);
                }
                ans += cans;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}