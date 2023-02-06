#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
using pi = pair<int, int>;

//ICPC North America Qualifier 2022 L

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t, s;
    cin >> t >> s;

    ll tT = 0, tS = 0;
    for (ll i = 0; i <= s; ++i)
    {
        ll max_D = min(i, (s - i) * 2);
        ll taxi = max(ll(0), t - i);
        ll spider = max_D + s - (max_D * 3 + 1) / 2 - (i - max_D);

        if (taxi > spider)
        {
            tT += spider;
            tS += spider;
        }
        else
        {
            tT += taxi;
            tS += spider;
        }
        // ll taxi = max(t - i, (ll)0);
        // ll spider = i + (s - (i * 3 + 1) / 2);
        // ll max_d = min((2 * s) / 3, i);
        // ll cost = (max_d * 3 + 1) / 2;
        // ll left = i - max_d;
        // if (s - cost - left < 0) spider = 0;
        // else {
        //     spider = s - cost - left + max_d;
        // }

        // cout << "x: " << i << " spider: " << spider << " cost: " << (i * 3 + 1) / 2 << "\n";
        // cerr << "max_d : " << max_d << " cost : " << cost << " left : " << left << endl;
        // if(taxi > spider) {
        //     tT += spider;
        //     tS += spider;
        // } else {
        //     tT += taxi;
        //     tS += spider;
        //}
    }
    tT = tT * 4 + 1;
    tS = tS * 4 + 1;
    // cerr << "tT : " << tT << " tS : " << tS << endl;
    // if (t == 0) tT = 1;
    ll den = gcd(tT, tS);
    tT /= den;
    tS /= den;
    if (tT == 1 && tS == 1)
        cout << 1 << endl;
    else
        cout << tT << "/" << tS << endl;
    return 0;
}