#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1400E

//we can solve for the minimum number of operations over a range of the array. 

//one option is to just use the second type of operation on every number, and remove them one by one. This
//will take r - l operations, or the number of values in the range. 

//or, we can get rid of the minimum amount from each value in the range, and recursively solve for the minimum
//amount of operations on the new subranges. 

ll solve(vector<ll>& a, int l, int r) { //[l, r)   
    //cout << "LR : " << l << " " << r << "\n";
    ll ans = r - l; //laser everything
    ll min = a[l];
    for(int i = l; i < r; i++){
        //cout << a[i] << " ";
        min = std::min(min, a[i]);
    }
    //cout << "\n";
    ll ans2 = min;
    for(int i = l; i < r; i++){
        a[i] -= min;
    }
    for(int i = l; i < r; i++){
        if(a[i] == 0){
            continue;
        }
        int ptr = i + 1;
        while(ptr < r && a[ptr] != 0){
            ptr ++;
        }
        ans2 += solve(a, i, ptr);
        i = ptr;
    }
    return std::min(ans, ans2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    cout << solve(a, 0, n) << "\n";
    
    return 0;
}
