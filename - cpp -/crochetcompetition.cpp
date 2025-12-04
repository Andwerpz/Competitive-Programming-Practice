#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

//NCPC 2025 - C

//implementation. 

ll to_min(string d, string t) {
    ll ans = 60 * 24;
    if(d == "Mon") ans *= 0;
    else if(d == "Tue") ans *= 1;
    else if(d == "Wed") ans *= 2;
    else if(d == "Thu") ans *= 3;
    else if(d == "Fri") ans *= 4;
    else if(d == "Sat") ans *= 5;
    else if(d == "Sun") ans *= 6;
    ll h = stoi(t.substr(0, 2));
    ll m = stoi(t.substr(3, 2));
    ans += h * 60 + m;
    return ans;
}

void print_str(ll amt, string s) {
    assert(amt >= 1);
    cout << amt << " " << s;
    if(amt > 1) cout << "s";
}

void print_min(ll min) {
    ll d = 0, h = 0, m = 0;
    while(min >= 60 * 24) {
        min -= 60 * 24;
        d ++;
    }
    while(min >= 60) {
        min -= 60;
        h ++;
    }
    m = min;
    if((d != 0) + (h != 0) + (m != 0) == 3) {
        print_str(d, "day");
        cout << ", ";
        print_str(h, "hour");
        cout << ", ";
        print_str(m, "minute");
    }
    else if(d != 0 && h != 0) {
        print_str(d, "day");
        cout << " and ";
        print_str(h, "hour");
    }
    else if(h != 0 && m != 0) {
        print_str(h, "hour");
        cout << " and ";
        print_str(m, "minute");
    }
    else if(d != 0 && m != 0) {
        print_str(d, "day");
        cout << " and ";
        print_str(m, "minute");
    }
    else if(d != 0) {
        print_str(d, "day");
    }
    else if(h != 0) {
        print_str(h, "hour");
    }   
    else if(m != 0) {
        print_str(m, "minute");
    }
    else assert(false);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string d1, d2;
    string t1, t2;
    cin >> d1 >> t1;
    cin >> d2 >> t2;
    ll mins = 0;
    ll m1 = to_min(d1, t1);
    ll m2 = to_min(d2, t2);
    mins = m2 - m1;
    if(mins <= 0) mins += 60 * 24 * 7;
    print_min(mins);

    return 0;
}