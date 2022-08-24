#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1718C

//i don't exactly understand how this one works, but my intuition said it would. 

//define b(s, k) as the usefulness of 'a' when fed to Burenka with parameters s, k. 

//notice that b(s, k) = b(s, gcd(n, k)). As long as the gcd of two k values with n are the same, then
//they will produce the same output. 

//One more observation: b(s, k) <= b(s, k * a), where n % (k * a) == 0. Essentially, we sample less numbers, 
//but the numbers we sample each add to the usefulness more times. 

//using the two observations, we can see that we only need to sample k equal to n / p, where n % p == 0, and p
//is a prime number. Since n is limited to 2 * 10^5, the maximum amount of unique p is equal to 6. 

//for each k, we only need to sample b(s, k) where 0 <= s <= k - 1. If s == k, then it is identical to s = 0.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, q;
        cin >> n >> q;
        vector<ll> a(n);
        vector<ll> d;
        vector<bool> isComposite(n, false);
        for(int i = 2; i <= n; i++){
            if(isComposite[i]){
               continue; 
            }
            if(n % i == 0){
                d.push_back(n / i);
            }
            for(ll j = (ll)i * (ll)i; j < n; j += i){
                isComposite[(int) j] = true;
            }
        }
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<map<int, ll>> m;
        multiset<ll> multi;
        for(int i = 0; i < d.size(); i++){
            m.push_back(map<int, ll>());
            int div = d[i];
            for(int j = 0; j < div; j++){
                ll sum = 0;
                for(int k = j; k < n; k += div){
                    sum += a[k] * (ll) div;
                }
                m[i].insert({j, sum});
                multi.insert(sum);
            }
        }
        cout << (*multi.rbegin()) << "\n";
        // for(ll j : multi){
        //     cout << j << " ";
        // }
        // cout << endl;
        for(int i = 0; i < q; i++){
            int p, x;
            cin >> p >> x;
            p--;
            ll diff = x - a[p];
            a[p] = x;
            for(int j = 0; j < d.size(); j++){
                int div = d[j];
                int mod = p % div;
                ll remove = m[j].find(mod) -> second;
                ll add = remove + (diff * div);
                m[j].find(mod) -> second = add;
                multi.erase(multi.find(remove));
                multi.insert(add);
            }
            cout << (*multi.rbegin()) << "\n";
            // for(ll j : multi){
            //     cout << j << " ";
            // }
            // cout << endl;
        }
    }
    
    return 0;
}
