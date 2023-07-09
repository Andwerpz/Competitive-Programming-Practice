#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

bool func(int x){
    if(x < 100) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int low = 0;
    int high = 1e9;
    int ans = low;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(func(mid)) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    cout << low << "\n";
    cout << ans << "\n";
    
    return 0;
}
