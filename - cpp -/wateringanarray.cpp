#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1917C

//if the array is initially all 0, then it's always optimal to 'farm' the first element. 
//this is because no matter how many operations of type 1 you do, the maximum score you can get is 1. 

//then, the problem boils down to trying to get the most score out of the initial array you are given, 
//then revert to farming the first element for the remaining days. 

//for each element in the initial array, we can compute the range of days in which it it will be good, given 
//we only do operations of type 1. Then, we can just brute force try all days in which at least one element in the
//original array will be good. 

//note that it might also be optimal to do an operation of type 2 on the first day, regardless of the values 
//in the initial array. 

//complexity: O(n^2). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k, d;
        cin >> n >> k >> d;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<ll> v(k);
        for(int i = 0; i < k; i++){
            cin >> v[i];
        }
        ll ans = 0;
        vector<ll> good(n, -1); //for each initial element in a, compute the nr operations until it is good 
        vector<ll> max_good(n, 0);  //after getting good, how many operations until it is not good
        for(int i = 0; i < n; i++){
            //cout << "I : " << i << endl;
            if(a[i] > (i + 1)) {
                continue;
            }
            ll cycle_add = 0;
            for(int j = 0; j < k; j++){
                if(v[j] >= i + 1) {
                    cycle_add ++;
                }
            }
            if(cycle_add == 0){
                if(a[i] == i + 1) {
                    good[i] = 0;
                    max_good[i] = 1e10;
                }
                continue;
            }
            ll diff = (i + 1) - a[i];
            ll nr_cycles = diff / cycle_add;
            nr_cycles = max(0ll, nr_cycles - 1);
            ll nr_ops = nr_cycles * k;
            diff -= cycle_add * nr_cycles;
            int ptr = 0;
            ll good_ops = 0;
            while(diff >= 0) {
                //cout << "PTR : " << ptr << endl;
                if(diff == 0){
                    good_ops ++;
                }
                if(diff != 0){
                    nr_ops ++;
                }
                if(v[ptr % k] >= i + 1) {
                    diff --;
                }
                ptr ++;
            }
            good[i] = nr_ops;
            max_good[i] = good_ops;
        }
        //try every number of initial operations
        for(int i = 0; i < n; i++){
            //cout << "GOOD : " << good[i] << " " << max_good[i] << "\n";
            if(good[i] == -1 || good[i] >= d) {
                continue;
            }
            ll init_ops = good[i];
            ll cur_d = d - init_ops - 1;
            ll c = 0;
            for(int j = 0; j < n; j++){
                if(good[j] == -1){
                    continue;
                }
                if(good[j] <= init_ops && init_ops - good[j] < max_good[j]) {
                    c ++;
                }
            }
            c += cur_d / 2;
            ans = max(ans, c);
        }
        //zero initial operations
        {
            ll c = 0;
            for(int i = 0; i < n; i++){
                if(a[i] == i + 1){
                    c ++;
                }
            }
            c += (d - 1) / 2;
            ans = max(ans, c);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
