#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//SWERC 2021-2022 N

//note that for any good selection of 4 people, good as in the bars don't cross, there have to be exactly 2
//people out of the 4 that have one person younger and one person older than them horizontally or vertically
//adjacent (not diagonally). Crucially, in any bad arrangement, there are no people who satisfy this condition. 

//then, if we count for each person, the number of rectangles they are a part of where this is true and take
//the sum across all people, the sum will be exactly twice the answer, because for each rectangle, there are 
//exactly 2 people for which this is true. 

//so how do we actually count? for each person, let the number of people that are younger than them on
//their row be R, and the number of younger people on their column be C. Since we want exactly one person
//younger and one older, we can match every younger person on the row, R, to an older person on the column, 
//n - 1 - C, so R * (n - 1 - C). We can likewise do the same with the younger people on the columns, so
//for a given person, they will contribute R * (n - 1 - C) + C * (n - 1 - R) to the sum. 

//to compute R and C for every person, we can do this in n^2 * log(n) time by just sorting everyone by their age
//and considering them in ascending order of age. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> g[i][j];
        }
    }
    vector<pair<int, pair<int, int>>> o(0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            o.push_back({g[i][j], {i, j}});
        }
    }
    vector<int> r(n, 0), c(n, 0);
    ll ans = 0;
    sort(o.begin(), o.end());
    for(int i = 0; i < o.size(); i++){
        int _r = o[i].second.first;
        int _c = o[i].second.second;
        ll u = r[_r];
        ll v = c[_c];
        ans += u * (n - 1 - v) + v * (n - 1 - u);
        r[_r] ++;
        c[_c] ++;
    }
    ans /= 2;
    cout << ans << "\n";
    
    return 0;
}
