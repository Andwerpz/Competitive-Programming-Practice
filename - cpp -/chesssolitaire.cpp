#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef pair<int, int> pii;

//ICPC ECNA 2025 - E

//just a lil bit of implementation

//intuitively, a brute force solution should work. There is an upper bound of 10! states that the pieces
//can have, and alot of those states should just be not reachable. 

vector<pii> locs;
vector<char> p;
int n, m;
vector<ll> pow11;
vector<vvi> poss;
vector<vector<vvi>> ocheck;

//sets ind'th digit to val in base 11
ll enc_set(ll x, int ind, int val) {
    assert(ind < 10);
    assert(val < 11);
    ll cval = (x / pow11[ind]) % 11;
    x -= pow11[ind] * cval;
    x += pow11[ind] * val;
    return x;
}

int enc_get(ll x, int ind) {
    assert(ind < 10);
    return (x / pow11[ind]) % 11;
}

int sign(int x) {
    if(x < 0) return -1;
    else if(x > 0) return 1;
    return 0;
}

string ltos(int ind) {
    assert(ind >= 0 && ind < locs.size());
    string ret(2, ' ');
    ret[0] = (char) ('A' + locs[ind].first);
    ret[1] = (char) ('1' + locs[ind].second);
    return ret;
}

vector<pair<char, pair<int, int>>> ans;

set<ll> v;
bool solve(ll state, int left, vi& cloc, vb& occ) {
    if(left == 1) {
        return true;
    }
    if(v.count(state)) {
        // cout << "ALREADY VISITED\n";
        return 0;
    }
    v.insert(state);
    // cout << "STATE : ";
    // for(int i = 0; i < n; i++) cout << cloc[i] << " ";
    // cout << "\n";
    //enumerate all moves possible at this state
    vector<array<int, 4>> mvs;
    for(int i = 0; i < n; i++) {
        if(cloc[i] == n) continue;
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            if(cloc[j] == n) continue;
            if(poss[i][cloc[i]][cloc[j]]) {
                bool cposs = true;
                for(int k : ocheck[i][cloc[i]][cloc[j]]) {
                    if(occ[k]) {
                        cposs = false;
                        // cout << "BLOCKED : " << p[i] << " " << ltos(cloc[i]) << " " << ltos(cloc[j]) << "\n";
                        break;
                    }
                }
                if(cposs) {
                    // cout << "MOVE : " << p[i] << " " << ltos(cloc[i]) << " " << ltos(cloc[j]) << "\n";
                    mvs.push_back({cloc[i], cloc[j], i, j});
                }
            }
        }
    }
    //consider all moves in lexicographic order
    sort(mvs.begin(), mvs.end());
    for(int i = 0; i < mvs.size(); i++) {
        int loci = mvs[i][0];
        int locj = mvs[i][1];
        int ii = mvs[i][2];
        int jj = mvs[i][3];
        // cout << "MOVE : " << p[ii] << " " << ltos(loci) << " " << ltos(locj) << "\n";
        cloc[ii] = locj;
        cloc[jj] = n;
        occ[loci] = false;
        ll nstate = enc_set(state, ii, locj);
        nstate = enc_set(nstate, jj, n);
        if(solve(nstate, left - 1, cloc, occ)) {
            ans.push_back({p[ii], {loci, locj}});
            return 1;
        }
        cloc[ii] = loci;
        cloc[jj] = locj;
        occ[loci] = true;
    }
    // cout << "BACKTRACK\n";
    return 0;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    pow11 = vl(12);
    pow11[0] = 1;
    for(int i = 1; i <= 11; i++) pow11[i] = pow11[i - 1] * (ll) 11;
    cin >> m >> n;
    p = vector<char>(n);
    locs = vector<pii>(n);
    for(int i = 0; i < n; i++) {
        string t;
        cin >> t;
        p[i] = t[0];
        cin >> t;
        locs[i] = {t[0] - 'A', t[1] - '1'};
    }  
    //reorder according to lex locs
    {
        vector<pair<pii, int>> ord;
        for(int i = 0; i < n; i++) ord.push_back({locs[i], i});
        sort(ord.begin(), ord.end());
        vector<char> np(n);
        vector<pii> nlocs(n);
        for(int i = 0; i < n; i++) {
            np[i] = p[ord[i].second];
            nlocs[i] = locs[ord[i].second];
        }
        p = np;
        locs = nlocs;
    }
    //compute for each piece, moves between which locs are possible
    poss = vector<vvi>(n, vvi(n, vi(n, 0)));
    ocheck = vector<vector<vvi>>(n, vector(n, vvi(n, vi(0))));
    for(int i = 0; i < n; i++) {
        if(p[i] == 'N') {
            for(int ii = 0; ii < n; ii++) {
                for(int jj = 0; jj < n; jj++) {
                    if(ii == jj) continue;
                    int dr = abs(locs[ii].first - locs[jj].first);
                    int dc = abs(locs[ii].second - locs[jj].second);
                    if(min(dr, dc) == 1 && max(dr, dc) == 2) poss[i][ii][jj] = 1;
                }
            }
        }
        else if(p[i] == 'B') {
            for(int ii = 0; ii < n; ii++) {
                for(int jj = 0; jj < n; jj++) {
                    if(ii == jj) continue;
                    int dr = locs[ii].first - locs[jj].first;
                    int dc = locs[ii].second - locs[jj].second;
                    if(abs(dr) == abs(dc)) {
                        poss[i][ii][jj] = 1;
                        for(int kk = 0; kk < n; kk++) {
                            if(kk == ii || kk == jj) continue;
                            int kdr = locs[ii].first - locs[kk].first;
                            int kdc = locs[ii].second - locs[kk].second;
                            if(abs(kdr) != abs(kdc)) continue;
                            if(sign(kdr) != sign(dr) || sign(kdc) != sign(dc)) continue;
                            if(abs(kdr) > abs(dr)) continue;
                            assert(abs(kdr) != abs(dr));
                            ocheck[i][ii][jj].push_back(kk);
                        }
                    }
                }   
            }
        }
        else if(p[i] == 'R') {
            for(int ii = 0; ii < n; ii++) {
                for(int jj = 0; jj < n; jj++) {
                    if(ii == jj) continue;
                    int dr = locs[ii].first - locs[jj].first;
                    int dc = locs[ii].second - locs[jj].second;
                    if(dr == 0 || dc == 0) {
                        poss[i][ii][jj] = 1;
                        for(int kk = 0; kk < n; kk++) {
                            if(kk == ii || kk == jj) continue;
                            int kdr = locs[ii].first - locs[kk].first;
                            int kdc = locs[ii].second - locs[kk].second;
                            if(kdr && kdc) continue;
                            if(kdr == 0 && dr != 0) continue;
                            if(sign(kdr) != sign(dr) || sign(kdc) != sign(dc)) continue;
                            if(max(abs(kdr), abs(kdc)) > max(abs(dr), abs(dc))) continue;
                            assert(max(abs(kdr), abs(kdc)) < max(abs(dr), abs(dc)));
                            ocheck[i][ii][jj].push_back(kk);
                        }
                    }
                }
            }
        }
        else if(p[i] == 'Q') {
            for(int ii = 0; ii < n; ii++) {
                for(int jj = 0; jj < n; jj++) {
                    if(ii == jj) continue;
                    int dr = locs[ii].first - locs[jj].first;
                    int dc = locs[ii].second - locs[jj].second;
                    if(abs(dr) == abs(dc)) {
                        poss[i][ii][jj] = 1;
                        for(int kk = 0; kk < n; kk++) {
                            if(kk == ii || kk == jj) continue;
                            int kdr = locs[ii].first - locs[kk].first;
                            int kdc = locs[ii].second - locs[kk].second;
                            if(abs(kdr) != abs(kdc)) continue;
                            if(sign(kdr) != sign(dr) || sign(kdc) != sign(dc)) continue;
                            if(abs(kdr) > abs(dr)) continue;
                            assert(abs(kdr) <= abs(dr));
                            ocheck[i][ii][jj].push_back(kk);
                        }
                    }
                    else if(min(abs(dr), abs(dc)) == 0) {
                        poss[i][ii][jj] = 1;
                        for(int kk = 0; kk < n; kk++) {
                            if(kk == ii || kk == jj) continue;
                            int kdr = locs[ii].first - locs[kk].first;
                            int kdc = locs[ii].second - locs[kk].second;
                            if(kdr && kdc) continue;
                            if(kdr == 0 && dr != 0) continue;
                            if(sign(kdr) != sign(dr) || sign(kdc) != sign(dc)) continue;
                            if(max(abs(kdr), abs(kdc)) > max(abs(dr), abs(dc))) continue;
                            assert(max(abs(kdr), abs(kdc)) < max(abs(dr), abs(dc)));
                            ocheck[i][ii][jj].push_back(kk);
                        }
                    }
                }
            }
        }
        else if(p[i] == 'K') {
            for(int ii = 0; ii < n; ii++) {
                for(int jj = 0; jj < n; jj++) {
                    if(ii == jj) continue;
                    int dr = abs(locs[ii].first - locs[jj].first);
                    int dc = abs(locs[ii].second - locs[jj].second);
                    if(max(dr, dc) == 1) poss[i][ii][jj] = 1;
                }
            }
        }
    }
    //solve
    ll state = 0;
    for(int i = 0; i < n; i++) state = enc_set(state, i, i);
    vi cloc(n);
    for(int i = 0; i < n; i++) cloc[i] = i;
    vb occ(n, 1);
    bool solved = solve(state, n, cloc, occ);
    if(!solved) cout << "No solution\n";
    else {
        assert(ans.size() == n - 1);
        reverse(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); i++) {
            int ind = ans[i].first;
            int loci = ans[i].second.first;
            int locj = ans[i].second.second;
            // cout << "IND : " << ind << "\n";
            cout << (char) (ind) << ": ";
            int ri = locs[loci].first, ci = locs[loci].second;
            int rj = locs[locj].first, cj = locs[locj].second;
            cout << (char) (ri + 'A') << (char) (ci + '1') << " -> " << (char) (rj + 'A') << (char) (cj + '1') << "\n";
        }   
    }

    return 0;
}