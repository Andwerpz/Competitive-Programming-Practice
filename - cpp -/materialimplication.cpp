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

//Topcoder - 14380

// x -> x is always true, it's impossible to make an expression that is always false, as if you set everything to true, 
// then the result is always going to be true. 
// x -> True = True
// x -> False = !x
// True -> x = x
// False -> x = True

// actually, I don't think you can get under 2^{n - 1}. Consider the last variable, if that is set to true, then the whole 
// expression will always be true. 

// n = 3, k = 4, A
// n = 3, k = 5, ((A -> B) -> C)
// n = 3, k = 6, (A -> B)
// n = 3, k = 7, (C -> (A -> B))
// n = 3, k = 8, (A -> A)

// n = 4, k = 8, A
// n = 4, k = 9, ((C -> (A -> B)) -> D)
// n = 4, k = 10, (A -> B) -> C
// n = 4, k = 11, (((A -> B) -> C) -> D)
// n = 4, k = 12, (A -> B)
// n = 4, k = 13, (D -> ((A -> B) -> C))
// n = 4, k = 14, C -> (A -> B)
// n = 4, k = 15, (D -> (C -> (A -> B)))
// n = 4, k = 16, (A -> A)

// You can always multiply k by 2 just by incrementing n. Then, to do odd k, we need to create something new. 
// Lets say that Z is our new variable. We have two options: (E -> Z) and (Z -> E)
//  - (E -> Z), if we fix Z = True, the expression is always True, and if we fix Z = False, then the expression is equivalent to !E
//  - (Z -> E), if we fix Z = True, the expression is equivalent to E, and if we fix Z = False, the expression is always True
// By choosing E and (E -> Z) or (Z -> E) carefully, we can build any k >= 2^{n - 1}. 

string solve(int n, int k){
    if(k < (1 << (n - 1))) return "Impossible";
    if(k == (1 << n)) return "(A->A)";
    if(k == (1 << (n - 1))) return "A";
    if(n == 2 && k == 3) return "(A->B)";
    if(k % 2 == 0) return solve(n - 1, k / 2);
    if(k > (1 << (n - 1)) + (1 << (n - 2))) return "(" + string(1, 'A' + n - 1) + "->" + solve(n - 1, k - (1 << (n - 1))) + ")";
    if(k < (1 << (n - 1)) + (1 << (n - 2))) return "(" + solve(n - 1, (1 << n) - k) + "->" + string(1, 'A' + n - 1) + ")";
    assert(false);
    return "D:";
}

bool getval(int val, char c) {
    return val & (1 << (c - 'A'));
}

bool eval(string& s, int val, int l, int r) {
    if(l == r - 1) return getval(val, s[l]);
    bool lval, rval;
    if(s[l + 1] != '(') {
        lval = getval(val, s[l + 1]);
        rval = eval(s, val, l + 4, r - 1);
    }
    else {
        lval = eval(s, val, l + 1, r - 4);
        rval = getval(val, s[r - 2]);
    }
    return (lval != true) || (rval != false);
}

class MaterialImplication {
public:
    string construct(int n, int k) {
        string ans = solve(n, k);
        if(ans == "Impossible") return ans;
        //check if answer is correct
        int cnt = 0;
        for(int i = 0; i < (1 << n); i++){
            cnt += eval(ans, i, 0, ans.size());
        }
        assert(cnt == k);
        return ans;
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg1;
    cin >> arg1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = MaterialImplication();
    string ret = c.construct(arg0, arg1);
    cout << ret;
}