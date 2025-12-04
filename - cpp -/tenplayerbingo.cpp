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

//2025 NAQ - J

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vector<int> a(100);
    for(int &x : a) cin >> x;
    int val = a[99];

    cout << (val - 1) % 10 + 1 << endl;
    
    return 0;
}

/*
12 91 49 4 52 95 45 51 50 40 11 5 88 87 39 38 42 89 76 85 30 69 35 81 23 67 32 3 62 8 79 58 1 75 37 27 24 46 18 16 97 61 41 59 13 74 78 54 98 66 14 33 86 55 83 93 63 72 6 19 92 17 56 64 100 53 28 71 7 96 36 57 84 43 73 60 15 77 80 31 20 99 21 90 70 22 26 10 25 2 94 9 82 34 65 68 48 29 44 50

*/