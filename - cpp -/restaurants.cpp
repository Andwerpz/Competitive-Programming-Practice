#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define z(s) (int) (x).size()
typedef vector<vi> vvi;

//SWERC 2020 - L

//the first two constraints on the solution are relatively easy to understand. 
//the third constraint is much more tricky. It essentially means that the solution is
//bad if there exists some (c, r) pair where c would much rather be with r than 
//its current restaurant, and r would much rather have c compared to its worst customer.

//The idea is that we can simply go to all customers and assign them a table at 
//their most preferred restaurant. 
//if when we try to get a table, but the restaurant is full, we can see if the current
//customer can kick out the worst customer currently assigned to the restaurant. 
//if the current customer can't get a table at their most preferred restaurant, then
//they should simply give up and move on to their next most preferred. 

//observe that the 'barrier to entry' of a restaurant only monotonically increases
//as we kick out people, the worst person in a restaurant will only become more and
//more preferred by the restaurant as this process continues. 

//so if a person gets kicked out of a restaurant, then they will never be able to get back
//in, as the minimum preference is always going to increase. 

//therefore, if we simulate this process using a queue, we will only have to consider each
//reservation at most once. When we can't make any more actions, then we will have 
//satisfied all three constraints. 

vector<string> split(string s, char delim) {
    vector<string> ret;
    for(int i = 0; i < s.size();) {
        if(s[i] == delim) {
            i ++;
            continue;
        }
        int r = i;
        while(r != s.size() && s[r] != delim) r ++;
        ret.push_back(s.substr(i, r - i));
        i = r;
    }
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    vi c(m);
    string line;
    getline(cin, line);
    for(int i = 0; i < m; i++) {
        getline(cin, line);
        c[i] = stoi(line);
    }
    vvi res(n);
    for(int i = 0; i < n; i++) {
        getline(cin, line);
        vector<string> tok = split(line, ' ');
        for(int j = 0; j < tok.size(); j++) {
            res[i].push_back(stoi(tok[j]));
        }
        for(int j = 0; j < tok.size(); j++) {
            res[i][j] --;
        }
    }
    vvi pref(m);
    for(int i = 0; i < m; i++) {
        getline(cin, line);
        vector<string> tok = split(line, ' ');
        for(int j = 0; j < tok.size(); j++) {
            pref[i].push_back(stoi(tok[j]));
        }
        for(int j = 0; j < tok.size(); j++) {
            pref[i][j] --;
        }
    }
    vector<map<int, int>> pmap(m);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < pref[i].size(); j++) {
            pmap[i][pref[i][j]] = j;
        }
    }
    vi rptr(n, 0);
    queue<int> q;
    for(int i = 0; i < n; ++i) {
        q.push(i);
    }
    vector<set<pii>> s(m); //{pref rank, cind}, lower pref rank is better
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        while(rptr[cur] != res[cur].size()) {
            int rest = res[cur][rptr[cur]];
            int cprank = pmap[rest][cur];
            //see if there's extra capacity
            if(s[rest].size() < c[rest]) {
                s[rest].insert({cprank, cur});
                break;
            }
            //see if we can kick someone out
            if(s[rest].rbegin()->first > cprank) {
                int kick = s[rest].rbegin()->second;
                s[rest].erase({s[rest].rbegin()->first, s[rest].rbegin()->second});
                s[rest].insert({cprank, cur});
                q.push(kick);
                break;
            }
            //never gonna get in here D:
            rptr[cur] ++;
        }
    }
    vi ans;
    for(int i = 0; i < s.size(); i++) {
        for(pii x : s[i]) {
            ans.push_back(x.second);
        }
    }
    sort(ans.begin(), ans.end());
    for(int x : ans) cout << (x + 1) << "\n";

    return 0;
}
