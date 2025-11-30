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

//Codeforces - 2134E

//make sure to read that a[i] = 1 or 2. 

//we can easily figure out the values of the last 2 elements using 3 operations. 
//then, we can go backwards and incrementally figure out the elements one by one. We can simply remember
//the amount of jumps that each element had, and compare the number of jumps by the current element 
//to the next two to see which one lines up. 

//the one issue is that the number of jumps might be the same regardless of the power of the box. 
//In this case, we can directly compute the amount of jumps, but just skip processing it for now. 

//after we did one back to front pass, we need to then process the ambiguous elements. 
//to process one ambiguous element, we can simply swap it with the element in front, then throw a ball at it.
//Now, it's guaranteed to be unambiguous (proof left to the reader). 

//the observation that makes this solution work is that you can't have two ambiguous elements in a row. 
//So in the forwards pass, worst case half of the elements are ambiguous, and half are unambiguous. So a
//total of n/2 + (n/2) * 2 = 3n / 2 operations. 

int calc_steps(vi& a, int s) {
    int ans = 0;
    while(s < a.size()) {
        ans ++;
        assert(a[s] != -1);
        s += a[s];
    }
    return ans;
}

int n;
bool debug_mode = true;
vi ja, jca;
int qcnt;
int interact(string s, int x) {
    qcnt ++;
    int ans = 0;
    if(debug_mode) {
        if(s == "swap"){
            assert(x + 1 < n);
            swap(jca[x], jca[x + 1]);
        }
        else if(s == "throw"){
            ans = calc_steps(jca, x);
        }
        else assert(false);
    }
    else {
        cout << s << " " << (x + 1) << endl;
        if(s == "throw") cin >> ans;
    }
    return ans;
}

vi a, oind;
void do_swap(int x) {
    interact("swap", x);
    swap(a[x], a[x + 1]);
    swap(oind[x], oind[x + 1]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        qcnt = 0;

        if(debug_mode) {
            ja = vi(n);
            for(int i = 0; i < n; i++) cin >> ja[i];
            jca = ja;
        }

        a = vi(n, -1);
        oind = vi(n);
        vi nj(n + 2, -1);
        nj[n] = 0, nj[n + 1] = 0;
        for(int i = 0; i < n; i++) oind[i] = i;
        //figure out last 2
        {
            if(interact("throw", n - 2) == 1) a[n - 2] = 2;
            else a[n - 2] = 1;
            do_swap(n - 2);
            if(interact("throw", n - 2) == 1) a[n - 2] = 2;
            else a[n - 2] = 1;
            nj[n - 1] = 1;
            nj[n - 2] = a[n - 2] == 1? 2 : 1;
        }
        //figure out figure outable
        for(int i = n - 3; i >= 0; i--){
            if(nj[i + 1] == nj[i + 2]) {
                nj[i] = nj[i + 1] + 1;
                continue;
            }
            int j = interact("throw", i);
            nj[i] = j;
            if(j == nj[i + 1] + 1) a[i] = 1;
            else if(j == nj[i + 2] + 1) a[i] = 2;
            else assert(false);
        }
        cout << "A : ";
        for(int i = 0; i < n; i++) cout << a[i] << " ";
        cout << "\n";
        //figure out -1s
        for(int i = 0; i < n; i++){
            if(a[i] != -1) continue;
            assert(a[i + 1] != -1);
            do_swap(i);
            int j = interact("throw", i + 1);
            if(j == nj[i + 2] + 1) a[i + 1] = 1;
            else if(j == nj[i + 3] + 1) a[i + 1] = 2;
            else assert(false);
        }
        vi ans(n);
        for(int i = 0; i < n; i++) ans[oind[i]] = a[i];
        cout << "! ";
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << endl;

        if(debug_mode) cout << "QCNT : " << qcnt << "\n";
    }
    
    return 0;
}