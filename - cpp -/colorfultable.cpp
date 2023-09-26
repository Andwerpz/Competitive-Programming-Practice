#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1870C

//note that the table is symmetrical across the diagonal. This means that if we find the first row-wise
//occurrence of a value, the first column-wise occurrence is at the same index, and any rectangle built to
//contain all occurrences of a value must be a square. 

//in order to find the first row-wise occurrence of a value, note that it will simply replace the first value
//that is greater than or equal to it. Thus, we can just create a prefix maximum array, and do a binary search.
//to find the last row-wise occurrence, we can do the same thing, just over the suffix. 

//finally, the side length is just the difference between the first and last row-wise occurrence indexes. 

int find_f(vector<int>& pfx, int val) {
    int low = 0;
    int high = pfx.size() - 1;
    int ans = high;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(pfx[mid] >= val) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return ans;
}

int find_l(vector<int>& sfx, int val) {
    int low = 0;
    int high = sfx.size() - 1;
    int ans = low;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(sfx[mid] >= val) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        set<int> exist;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            exist.insert(a[i]);
        }
        vector<int> pfx(n);
        vector<int> sfx(n);
        pfx[0] = a[0];
        sfx[n - 1] = a[n - 1];
        for(int i = 1; i < n; i++){
            pfx[i] = max(pfx[i - 1], a[i]);
            sfx[n - 1 - i] = max(sfx[n - i], a[n - i - 1]);
        }
        for(int i = 1; i <= k; i++){
            if(exist.find(i) == exist.end()) {
                cout << "0 ";
                continue;
            }
            int l = find_f(pfx, i);
            int r = find_l(sfx, i);
            int ans = (r - l + 1) * 2;
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
