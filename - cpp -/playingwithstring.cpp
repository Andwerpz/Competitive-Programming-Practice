#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 305E

//the naive approach is to compute the grundy number for each substring. The problem is that there
//are n^2 substrings, and each substring's grundy number depends on around n other numbers, so the
//total complexity is around n^3. 

//instead, first we can mark all the characters that are palindrome centers. Then, we notice that if
//two continuous groups of palindrome centers are seperated from each other, then they are independent, 
//which means we can compute a grundy number that only depends on the length of contiguous palindrome
//centers. 

//for a given substring of palindrome centers, we can simply test all possible choices of moves to
//get the grundy number. 

int n;
string s;
vector<int> g_map;

int mex(vector<int>& a){
    sort(a.begin(), a.end());
    int ans = 0;
    for(int i = 0; i < a.size(); i++){
        ans += ans == a[i];
    }
    return ans;
}

int calc_grundy(int len) {
    if(len <= 0){
        return 0;
    }
    if(g_map[len] != -1){
        return g_map[len];
    }
    vector<int> c;
    for(int i = 1; i <= len; i++){
        int l = max(0, i - 2);
        int r = max(0, len - 1 - i);
        c.push_back(calc_grundy(l) ^ calc_grundy(r));
    }
    g_map[len] = mex(c);
    return g_map[len];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> s;
    n = s.size();
    g_map = vector<int>(n, -1);
    int x_sum = 0;
    vector<bool> v(n, false);
    for(int i = 1; i < n - 1; i++){
        v[i] = s[i - 1] == s[i + 1];
    }
    vector<int> seg_begin;
    vector<int> seg;
    for(int i = 0; i < n;){
        if(!v[i]) {
            i ++;
            continue;
        }
        int r = i;
        while(r != n && v[r]) {
            r ++;
        }
        seg.push_back(r - i);
        seg_begin.push_back(i);
        i = r;
    }
    for(int i = 0; i < seg.size(); i++){
        x_sum ^= calc_grundy(seg[i]);
    }
    if(x_sum == 0){
        cout << "Second\n";
        return 0;
    }
    cout << "First\n";
    for(int i = 0; i < seg.size(); i++){
        int begin = seg_begin[i];
        int len = seg[i];
        for(int j = 0; j < len; j++){
            int l = max(0, j - 1);
            int r = max(0, len - 2 - j);
            if((calc_grundy(len) ^ calc_grundy(l) ^ calc_grundy(r)) == x_sum) {
                cout << begin + j + 1 << "\n";
                return 0;
            }
        }
    }
    
    return 0;
}
