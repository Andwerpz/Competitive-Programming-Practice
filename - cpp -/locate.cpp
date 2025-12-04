#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 2168B

//first, lets try to solve the problem without the first phase.  
//we can binary search for the first r such that the segment [0, r) has range n - 1
//similarly, we can binary search for the last l such that the segment [l, n) has range n - 1
//however, we will never be able to know which end of the range has value 1 and which has value n

//this is where the first phase comes in, we can send '0' if n comes before 1 and '1' otherwise. 

int n;
int interact(int l, int r) {
    assert(l < r && l >= 0 && r <= n);
    cout << "? " << (l + 1) << " " << r << endl;
    int ret;
    cin >> ret;
    return ret;
}

void report_ans(int ans) {
    assert(ans >= 0 && ans < n);
    cout << "! " << (ans + 1) << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string run;
    cin >> run;
    if(run == "first") {
        int t;
        cin >> t;
        while(t--) {
            cin >> n;
            vi p(n);
            for(int i = 0; i < n; i++) cin >> p[i];
            bool ff = false;
            for(int i = 0; i < n; i++) {
                if(p[i] == n) {
                    cout << ff << "\n";
                    break;
                }
                if(p[i] == 1) ff = true;
            }
        }
    }
    else {
        int t;
        cin >> t;
        while(t--) {
            cin >> n;
            int x;
            cin >> x;
            if(n == 1) {
                report_ans(0);
                continue;
            }
            int low = 1, high = n;
            int sind = n;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                int val = interact(0, mid);
                if(val == n - 1) {
                    sind = min(sind, mid - 1);
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            assert(sind != n);
            if(x) {
                report_ans(sind);
            }
            else {
                low = 0, high = n - 1;
                int find = 0;
                while(low <= high) {
                    int mid = low + (high - low) / 2;
                    int val = interact(mid, n);
                    if(val == n - 1) {
                        find = max(find, mid);
                        low = mid + 1;
                    }
                    else {
                        high = mid - 1;
                    }
                }
                report_ans(find);
            }
        }
    }
    
    return 0;
}