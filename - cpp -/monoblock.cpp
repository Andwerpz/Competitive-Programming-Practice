#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1715C

//to reiterate the problem, you must find the sum of the awesomeness of all subarrays of 'a'
//after every modification step. 

//define the sum of the awesomeness of all subarrays of 'a' as f(a). We can compute f(a) in linear time, 
//the idea is to compute f(a) for each prefix of 'a' in order. 

//you'll notice that f(a) is made up of two parts: the sum of the sequence 1, 2, 3, ... n; and 
//the additional part, 'add' where add[i] = i * (n - i). add[i] is only factored in if a[i] != a[i - 1]. 

//To modify the answer for the queries, we can activate or deactivate add[i] and add[i + 1] depending 
//on what x is equal to. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    vector<ll> add(n);
    ll ans = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        add[i] = (ll) i * (ll) (n - i);
        ans += i + 1;
        if(i != 0){
            ans += a[i] != a[i - 1]? add[i] : 0;
        }
    }
    for(int i = 0; i < m; i++){
        int id, x;
        cin >> id >> x;
        id --;
        if(id != 0){
            if(a[id] != a[id - 1] && x == a[id - 1]){
                ans -= add[id];
            }
            else if(a[id] == a[id - 1] && x != a[id - 1]) {
                ans += add[id];
            }
        }
        if(id != n - 1){
            if(a[id] != a[id + 1] && x == a[id + 1]){
                ans -= add[id + 1];
            }
            else if(a[id] == a[id + 1] && x != a[id + 1]) {
                ans += add[id + 1];
            }
        }
        a[id] = x;
        cout << ans << "\n";
    }
    
    return 0;
}
