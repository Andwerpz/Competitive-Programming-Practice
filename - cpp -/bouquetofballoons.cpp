#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;

// ICPC PACNW 2025 - A

//the first sample test case should give you the insight that rather than solving the problems greedily in ascending order
//of time to solve, we should instead solve them in descending order. This makes it so that problems with longer time to solve
//don't 'time out' previous problems as much. 

//so we sort the problems in descending order. 
//next, observe that if we start at some suffix and take problems from that suffix in order and it works, then
//starting from any suffix that contains that suffix will also work. 

//therefore, we can just binary search for the answer. 

bool is_valid(vl& a, ll n, ll d, ll m, int val) {
    // cout << "TEST : " << val << "\n";
    m *= d;
    ll sum = 0;
    ll t = 0;
    ll cnt = 0;
    queue<ll> q;
    for(int i = val - 1; i >= 0; i--){
        ll nt = t + a[i];
        while(q.size() != 0 && q.front() <= nt) {
            cnt --;
            sum -= q.front() - t;
            q.pop();
        }
        sum -= (nt - t) * cnt;
        t = nt;
        cnt ++;
        sum += d;
        q.push(t + d);
        // cout << "SUM : " << t << " " << sum << "\n";
        if(sum >= m) {
            return true;
        }
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n, d, m;
    cin >> n >> d >> m;
    vl a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int ans = -1;
    int low = 1, high = n;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(is_valid(a, n, d, m, mid)) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";

    return 0;
}