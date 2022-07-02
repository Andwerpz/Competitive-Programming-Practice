#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
    
//Codeforces - 1696D

//lets say that for a given array 'a', we know the location of the maximum and minimum values in
//the array, 'i', and 'j', i < j. Given another set of indicies, u, and v, i < u < j, and v < i || v > j,
//we know that we can't form a connection between u and v. 

//thus, we can split the array into 3 parts, and solve them seperately. Actually, the middle section, [i, j], 
//is solved already, we can make a direct connection between i and j. We just need to solve
//the two outer sections, and that can be done with recursion. 

void min_modify(vector<int> &t, int n, int i, int val){
    i += n;
    t[i] = val;
    for(i /= 2; i > 0; i /= 2){
        t[i] = min(t[i * 2], t[i * 2 + 1]);
    }
}

void max_modify(vector<int> &t, int n, int i, int val){
    i += n;
    t[i] = val;
    for(i /= 2; i > 0; i /= 2){
        t[i] = max(t[i * 2], t[i * 2 + 1]);
    }
}

int min_query(vector<int> &t, int n, int l, int r){ //[l, r)
    l += n;
    r += n;
    int ans = t[l];
    for(; l < r; l /= 2, r /= 2) {
        if(l % 2 == 1){
            ans = min(ans, t[l]);
            l++;
        }
        if(r % 2 == 1){
            r--;
            ans = min(ans, t[r]);
        }
    }
    return ans;
}

int max_query(vector<int> &t, int n, int l, int r){ //[l, r)
    l += n;
    r += n;
    int ans = t[l];
    for(; l < r; l /= 2, r /= 2) {
        if(l % 2 == 1){
            ans = max(ans, t[l]);
            l++;
        }
        if(r % 2 == 1){
            r--;
            ans = max(ans, t[r]);
        }
    }
    return ans;
}

int solve(vector<int> &a, vector<int> &loc, vector<int> &tmin, vector<int> &tmax, int n, int l, int r) {    //[l, r]
    //cout << "SOLVING: " << l << " " << r << "\n";
    int ans = 0;
    if(l == r){
        ans = 0;
    }
    else if(r - l == 1){
        ans = 1;
    }
    else{
        int minLoc = loc[min_query(tmin, n, l, r + 1)];
        int maxLoc = loc[max_query(tmax, n, l, r + 1)];
        ans = 1;
        int lLoc = min(minLoc, maxLoc);
        int rLoc = max(minLoc, maxLoc);
        if(lLoc != l){
            //cout << "LEFT\n";
            ans += solve(a, loc, tmin, tmax, n, l, lLoc);
        }
        if(rLoc != r){
            //cout << "RIGHT\n";
            ans += solve(a, loc, tmin, tmax, n, rLoc, r);
        }
    }
    //cout << "OUT: " << ans << "\n";
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> loc(n); //for each a_i, what is it's i?
        vector<int> tmin(n * 2);
        vector<int> tmax(n * 2);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
            loc[a[i]] = i;
            min_modify(tmin, n, i, a[i]);
            max_modify(tmax, n, i, a[i]);
        }
        cout << solve(a, loc, tmin, tmax, n, 0, n - 1) << "\n";
    }
    
    return 0;
}
