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

//2024 ICPC World Finals - C

//First, we can turn all dates into the number of days elapsed since 0000-01-01
//the maximum date we need to consider is around 6000-12-31, which would translate to around 2 million
//so we can actually just make a big array and mark each date as to if we're in the country or not. 
//then just make a prefix sum array so that we can query for each year, the number of days that we're in the country.

//observe that we can actually put the year ranges into one of 365 buckets (kind of like day % 365). 
//Then, for each bucket, we compute the last year for that remainder for which we've been out of the country
//too much. Then, we can go through each remainder and find the minimum. 

//One implementation consideration is to take into account negative years. 

vi month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//just stores elapsed stuff
//so y, m, d, are 0 indexed
struct date {
    int y, m, d;
};

int date_to_int(date d) {
    int ans = d.y * 365;
    for(int i = 0; i < d.m; i++){
        ans += month[i];
    }
    ans += d.d;
    return ans;
}

date int_to_date(int x) {
    int y = x / 365;
    x %= 365;
    int m = 0;
    for(int i = 0; i < month.size(); i++){
        if(x < month[i]) break;
        assert(i != month.size() - 1);
        m ++;
        x -= month[i];
    }
    int d = x;
    return {y, m, d};
}

//YYYY-MM-DD
date parse_date(string s) {
    int y = stoi(s.substr(0, 4));
    int m = stoi(s.substr(5, 2));
    int d = stoi(s.substr(8, 2));
    m --, d --;
    return {y, m, d};
}

string format_date(date dt) {
    string y = to_string(dt.y);
    string m = to_string(dt.m + 1);
    string d = to_string(dt.d + 1);
    while(y.size() != 4) y = "0" + y;
    while(m.size() != 2) m = "0" + m;
    while(d.size() != 2) d = "0" + d;
    return y + "-" + m + "-" + d;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, y, d;
    cin >> n >> y >> d;
    vvi a(n, vi(2));
    vi arr(2e6 + 1100 * 365, 1);
    int lastd = 0;
    for(int i = 0; i < n; i++){
        string d1, d2;
        cin >> d1 >> d2;
        a[i][0] = date_to_int(parse_date(d1));
        a[i][1] = date_to_int(parse_date(d2));
        a[i][0] += 1100 * 365;
        a[i][1] += 1100 * 365;
        // assert(format_date(int_to_date(a[i][0])) == d1);
        // assert(format_date(int_to_date(a[i][1])) == d2);
        assert(a[i][0] >= 0 && a[i][1] < arr.size());
        for(int j = a[i][0]; j <= a[i][1]; j++){
            arr[j] = 0;
        }
        lastd = a[i][1];
    }
    vi pfx(arr.size() + 1, 0);
    for(int i = 1; i <= arr.size(); i++){
        pfx[i] = pfx[i - 1] + arr[i - 1];
    }
    vi b(365, -1);  //what's the last starting day on which that year is invalid?
    for(int i = 0; i < arr.size() - 365; i++){
        int amt = pfx[i + 365] - pfx[i];
        if(amt < d) {
            b[i % 365] = i;
        }
    }
    // cout << "BUCKETS : " << "\n";
    // for(int i = 0; i < 365; i++){
    //     cout << format_date(int_to_date(b[i])) << "\n";
    // }
    int ans = 1e9;
    for(int i = 0; i < 365; i++){
        int cd = lastd + i + 1;
        int bv = b[cd % 365];
        if(bv == -1) {
            ans = min(ans, cd);
            continue;
        }
        assert((cd - bv) % 365 == 0);
        int yamt = (cd - bv) / 365;
        yamt = max(yamt, y);
        ans = min(ans, (bv + 365) + yamt * 365);
    }
    ans -= 1100 * 365;
    cout << format_date(int_to_date(ans)) << "\n";
    // for(int i = 0; i < y; i++){
    //     ans -= 365;
    //     int amt = pfx[ans + 365] - pfx[ans];
    //     if(amt == 240) {
    //         cout << (pfx[ans + 365] - pfx[ans]) << "\n";
    //         int cnt = 0;
    //         for(int j = 0; j < 365; j++){
    //             if(arr[ans + j]) {
    //                 cout << format_date(int_to_date(ans + j)) << "\n";
    //                 cnt ++;
    //             }
    //         }
    //         cout << "CNT : " << cnt << "\n";
    //     }
        
    // }
    
    return 0;
}