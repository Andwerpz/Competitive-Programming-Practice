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

//Codeforces - 2023C

//lets do bfs on each graph and assign each node a color equal to the distance from the start node mod k. Note
//that if you don't consider offsets of the same coloring to be different, there is only 1 valid coloring
//of the graph. 

//for us to print "YES", we want to find some coloring such that we can draw an edge from nodes in A to nodes in B 
//such that the distances remain consistent, that is the offset on the end of the edge has to be +1 in comparison to
//the offset of the start of the edge. 

//we can use KMP or string hashing to find a proper matching, as we just need to take rotations of the frequency
//array of node colors. 

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

// change M and B if you want
const ll M = 1e9 + 9;
const ll B = uniform_int_distribution<ll>(0, M - 1)(rng);

struct hstring {
	// pow[i] contains B^i % M
	vector<long long> pow;

	// p_hash[i] is the hash of the first i characters of the given string
	vector<long long> p_hash;

	hstring(const vi& s) : p_hash(s.size() + 1), pow(1, 1) {
		while (pow.size() <= s.size()) { pow.push_back((pow.back() * B) % M); }

		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

	ll get_hash(int start, int end) {
		long long raw_val = (p_hash[end] - (p_hash[start] * pow[end - start]));
		return (raw_val % M + M) % M;
	}
};
// vector<long long> hstring::pow = {1};

void assign_color(vvi& c, vi& col, int k){
    int n = c.size();
    queue<int> q;
    vi v(n, false);
    q.push(0);
    v[0] = true;
    col[0] = 0;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(v[next]){
                continue;
            }
            v[next] = true;
            col[next] = (col[cur] + 1) % k;
            q.push(next);
        }
    }
}

vl gen_shift_hashes(vi& a){
    hstring s(a);
    // cout << "S HASH : " << s.get_hash(0, 1) << "\n";
    vl res(a.size(), 0);
    for(int i = 0; i < a.size(); i++){
        res[i] = ((s.get_hash(i, a.size()) * s.pow[i]) % M + s.get_hash(0, i)) % M;
    }
    return res;
}

vector<int> kmp(vector<int> s) {
    int n = s.size();
    vector<int> b(n+1,-1);
    int i = 0, j = -1;
    while(i != n) {
        while(j != -1 && s[i] != s[j]) {
            j = b[j];
        }
        i++;
        j++;
        b[i] = j;
    }
    return b;
}

//finds all occurences of m in n with kmp array of m, a. 
vector<int> find_matches(vector<int> &n, vector<int> &m, vector<int> &a) {
    vector<int> matches;
    int i = 0;
    int j = 0;
    while(i < n.size()) {
        while(j == m.size() || (j != -1 && n[i] != m[j])) {
            j = a[j];
        }
        i++;
        j++;
        if(j == m.size()) {
            matches.push_back(i - m.size() + 1);
        }
    }
    return matches;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    bool should_print = false;
    int casi = 0;
    vb ans_arr;
    while(t--){
        casi ++;
        int n, k;
        cin >> n >> k;
        if(casi == 1){
            should_print = t == 10000 && n == 6;
        }
        vi a(n), b(n);
        vvi ca(n), cb(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int m;
        cin >> m;
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            ca[u].push_back(v);
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        cin >> m;
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            cb[u].push_back(v);
        }
        if(casi == 216 && should_print && false) {
            cout << n << " " << k << "\n";
            for(int i = 0; i < n; i++){
                cout << a[i] << " ";
            }
            cout << "\n";
            cout << m << "\n";
            for(int i = 0; i < n; i++){
                for(int j = 0; j < ca[i].size(); j++){
                    cout << i + 1 << " " << ca[i][j] + 1 << "\n";
                }
            }
        }
        //check if incoming and outgoing amounts match up
        int ainc = 0, bout = 0;
        for(int i = 0; i < n; i++){
            ainc += a[i] == 0;
            bout += b[i] == 1;
        }
        if(ainc != bout){
            ans_arr.push_back(false);
            continue;
        }
        if(ainc == 0 || ainc == n){ 
            //final graph will not be a scc, therefore any assignment works. 
            ans_arr.push_back(true);
            continue;
        }
        //color nodes
        vi cola(n, -1), colb(n, -1);
        assign_color(ca, cola, k);
        assign_color(cb, colb, k);
        //ins of a need to be matched with outs of b, and vice versa. 
        //check for cyclic shifts of b colors. 
        vi fainc(k, 0), faout(k, 0), fbinc(k, 0), fbout(k, 0);
        for(int i = 0; i < n; i++){
            if(!a[i]){
                fainc[cola[i]] ++;
            }
            else {  
                faout[cola[i]] ++;
            }
            if(!b[i]){
                fbinc[colb[i]] ++;
            }
            else {
                fbout[colb[i]] ++;
            }
        }
        for(int i = 0; i < k; i++){
            fbinc.push_back(fbinc[i]);
            fbout.push_back(fbout[i]);
        }
        vi kfainc = kmp(fainc), kfaout = kmp(faout);
        vi maincbout = find_matches(fbout, fainc, kfainc);
        vi maoutbinc = find_matches(fbinc, faout, kfaout);
        set<int> smaoutbinc;
        for(int i = 0; i < maoutbinc.size(); i++){
            smaoutbinc.insert(maoutbinc[i] % k);
            smaoutbinc.insert((maoutbinc[i] + k) % k);
        }
        bool ans = false;
        for(int i = 0; i < maincbout.size(); i++){
            int x = maincbout[i];
            ans = ans || smaoutbinc.count((x + 2) % k);
        }
        ans_arr.push_back(ans);

        // // for(int i = 0; i < k; i++){
        // //     cout << fainc[i] << " " << faout[i] << " " << fbinc[i] << " " << fbout[i] << "\n";
        // // }
        // hstring hfainc(fainc), hfaout(faout);
        // vl shfbinc = gen_shift_hashes(fbinc), shfbout = gen_shift_hashes(fbout);
        // // cout << "HASHES : " << hfainc.get_hash(0, k) << " " << hfaout.get_hash(0, k) << "\n";
        // bool ans = false;
        // for(int i = 0; i < k; i++){
        //     // cout << shfbout[(i - 1 + k) % k] << " " << shfbinc[(i + 1) % k] << "\n";
        //     if(hfainc.get_hash(0, k) == shfbout[(i - 1 + k) % k] && hfaout.get_hash(0, k) == shfbinc[(i + 1) % k]) {
        //         ans = true;
        //     }
        // }
        // cout << (ans? "YES" : "NO") << "\n";
    }
    for(int i = 0; i < ans_arr.size(); i++){
        cout << (ans_arr[i]? "YES" : "NO") << "\n";
    }
    
    return 0;
}