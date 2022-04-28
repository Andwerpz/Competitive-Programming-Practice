#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 380C

//We can make a segment tree that saves 3 attributes on each node; max subsequence size, 
//number of open brackets not in max subsequence, number of close brackets not in subsequence. 

//To combine 2 segments, $l$ and $r$, we can define a new number, $d$, which is equal to 
//\code{min(left segment open brackets, right segment close brackets)}. New segment max subsequence 
//will be equal to the sum of max subsequences of left and right segments plus $d$. 
//Number of open brackets will be the sum of open brackets from left and right segments minus $d$; 
//same thing for close brackets, except you sum the close brackets. 

//Retrieving the range query is just a matter of combining all segments within the range. 

vector<vector<int>> tree(1e6 * 2 + 100, vector<int>(3));  //largest seg, num '(', num ')'

vector<int> combine(vector<int>& l, vector<int>& r) {
    vector<int> dest(3);
    int d = min(l[1], r[2]);
    dest[0] = l[0] + r[0] + d;
    dest[1] = l[1] + r[1] - d;
    dest[2] = l[2] + r[2] - d;
    return dest;
}   

int query(int l, int r, int n) {
    l += n;
    r += n;
    vector<int> lSeg(3);
    vector<int> rSeg(3);
    for(; l < r; l /= 2, r /= 2){
        if(l % 2 == 1) {lSeg = combine(lSeg, tree[l++]);}
        if(r % 2 == 1) {rSeg = combine(tree[--r], rSeg);}
    }
    return combine(lSeg, rSeg)[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int n, m;
    n = s.size();
    cin >> m;
    //set up seg tree
    for(int i = 0; i < n; i++){
        s[i] == '('? tree[i + n][1] ++ : tree[i + n][2] ++;
    }
    for(int i = n - 1; i > 0; i--){
        tree[i] = combine(tree[i * 2], tree[i * 2 + 1]);
    }
    for(int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        cout << query(--l, r, n) * 2 << endl;
    }
    
    return 0;
}
