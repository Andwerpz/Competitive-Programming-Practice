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

//Codeforces - 2115B

//nice problem.

//if you try working backwards (creating all the constraints that each element of b should follow) to get to a, 
//then you're going to quickly realize it's way too hard. Since this is only div2D, there should be an easier to 
//implement solution. 

//this is when you try working forwards. First, we can express every element of b simply as the minimum of some
//subset of elements in a. So we want to select the elements in a such that all of these n equations are satisfied
//simultaneously. 

//consider some a[i]. This a[i] must appear in the equations for some subset of b[i]. For the equations that this
//a[i] appears in, it can't be smaller than any of those b[i], so it must be >= the maximum b[i] that it appears in. 
//But if some a[i] is bigger than the maximum b[i], then it becomes useless, as all the b[i] that it appears in 
//must take on the value of some smaller a[i]. Therefore, we should set each a[i] equal to the maximum b[i] that it
//appears in. 

//How can we figure out the maximum b[i] that some a[i] appears in? We can do this for all a[i] in linear time. 
//first, process the operations in forwards order. Initially, each a[i] is a node, and for every operation we create
//a new node and connect it to the two nodes it takes the min of. Once we've processed all the operations, assign
//to the nodes that represent the b values their respective values. Then, propogate the values back up the DAG. 

//It can be proven (i think) that if this configuration of a[i] doesn't work, then it's impossible, so just test it. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        vi b(n), cn(n);
        for(int i = 0; i < n; i++) cin >> b[i];
        for(int i = 0; i < n; i++) cn[i] = i;
        vvi c(n + q);
        vvi qs(q);
        for(int i = 0; i < q; i++){
            int x, y, z;
            cin >> x >> y >> z;
            x --, y --, z --;
            qs[i] = {x, y, z};
            c[n + i].push_back(cn[x]);
            c[n + i].push_back(cn[y]);
            cn[z] = n + i;
        }
        vi val(n + q, 0);
        for(int i = 0; i < n; i++) val[cn[i]] = b[i];
        for(int i = n + q - 1; i >= 0; i--){
            for(int x : c[i]) val[x] = max(val[x], val[i]);
        }
        vi a(n);
        for(int i = 0; i < n; i++) a[i] = val[i];
        for(int i = 0; i < q; i++){
            int x = qs[i][0], y = qs[i][1], z = qs[i][2];
            a[z] = min(a[x], a[y]);
        }
        if(a != b) cout << "-1\n";
        else {
            for(int i = 0; i < n; i++) cout << val[i] << " ";
            cout << "\n";
        }
    }
    
    return 0;
}