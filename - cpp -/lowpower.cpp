#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2013 - F

//binary search across the maximum minimum difference, d. 

bool isValid(vector<int>& a, int val, int k, int n) {
    //cout << "TESTING : " << val << "\n";
    vector<int> s(a.size(), 0); //1: begin, 2: end
    int cnt = 0;
    for(int i = 0; i < a.size() - 1; i++){
        if(a[i + 1] - a[i] <= val) {
            //cout << a[i + 1] << " " << a[i] << "\n";
            s[i] = 1;
            s[i + 1] = 1;
            cnt ++;
            i ++;
            if(cnt == n){
                break;
            }
        }
    }
    if(cnt < n) {
        return false;
    }
    cnt = 0;
    for(int i = a.size() - 1; i >= 0; i--){
        cnt ++;
        if(s[i] == 1){
            cnt -= k;
            if(cnt < 0){
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    int nk2 = 2 * n * k;
    vector<int> a(nk2, 0);
    for(int i = 0; i < nk2; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int low = 0;
    int high = 1e9 + 1;
    int ans = high;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(isValid(a, mid, k, n)) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
