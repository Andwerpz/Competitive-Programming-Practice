#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef __int128_t lll;

//2025 ICPC Shenyang Regional - A

lll min(lll x, lll y){
    if(x < y) return x;
    return y;
}

lll max(lll x, lll y) {
    if(x > y) return x;
    return y;
}

lll gcd(lll x, lll y) {
    if (x < y) swap(x, y);
    if (y == 0) return x;
    return gcd(x % y, y);
}

string to_string(lll x) {
    if(x == 0) return string("0");
    string ret = "";
    while(x != 0) {
        int dig = (int) (x % 10);
        ret.push_back('0' + dig);
        x /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}   

ostream& operator<<(ostream& stream, lll x) {
    stream << to_string(x);
    return stream;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, k, a, b;
    cin >> n >> k >> b >> a;

    lll l = 1, r = 1e24;

    while (l < r) {
        lll mid = l + (r - l)/ 2;
        ll count = 0;

        // for (lll y = 2; y <= min(n, (ll)2e6); y++) {
        //     lll x_max = min(mid / (lll) (a * 4 + (lll) b * y * 4), y - 1);
        //     x_max = min(x_max, (lll) n - y);
        //     count += max(x_max, (lll) 0);

        //     x_max = min((mid / ((lll) a * 2 + (lll) b * (lll) (y * 2 - 1)) + 1) / 2, y - 1);
        //     x_max = min(x_max , (lll) n - y + 1);
        //     count += max(x_max, (lll) 0);
        // }

        for (lll x = 1; x <= min(n, (ll)1e6) && count < (ll)1e15; x++) {
            lll tmp = (mid / (x * 2) - a * 2) / (b * 2);
            if (tmp > (lll)1e15) {
                ll added = max(n - x * 2, 0) + max(n - x * 2 + 1, 0);
                if (added == 0) break;
                count += added;
                continue;
            }

            assert(tmp <= (lll)1e15);
            ll y_max = min((ll)tmp, n - x);
            ll added = max(y_max - x, 0);
            
            // if (mid == 13 && y_max - x > 0) {
            //     cout << "Found even with x " << x << " " << y_max << '\n';
            // }

            tmp = ((mid / (x * 2 - 1) - a * 2) / b + 1) / 2;
            y_max = min(tmp, n - x + 1);

            // if (mid == 13 && y_max - x > 0) {
            //     cout << "Found oddd with x " << x << " " << y_max << '\n';
            // }
            added += max(y_max - x, 0);
            if (added == 0) break;
            count += added;
        }

        // cout << "binsearch " << mid << " " << count << '\n';

        if (count >= (lll) k) r = mid;
        else l = mid + 1;
    }

    cout << (l / gcd(l, (lll)b)) << " " << (b / gcd(l, (lll)b)) << '\n';

    return 0;
}