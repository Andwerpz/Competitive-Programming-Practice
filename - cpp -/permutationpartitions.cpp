
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1326C

//notice that you want to make the partitions around the k greatest numbers in the permutation. All the other numbers do not matter.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    bool seen = false;
    int threshold = n - k;
    int counter = 0;
    ll ans = 1;
    ll mod = 998244353;
    ll max = 0;
    for(int i = 0; i < n; i++){
        int next = nums[i];
        if(!seen){
            if(next > threshold){
                seen = true;
                counter = 1;
                max += next;
            }
        }
        else{
            if(next > threshold){
                max += next;
                ans *= (ll) (counter);
                ans %= mod;
                counter = 1;
            }
            else{
                counter ++;
            }
        }
    }
    cout << max << " " << ans << endl;

    return 0;
}



