#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NWERC 2020 - I

//fix the position of the first person, then binary search the closest the second person can start to the
//first one and not be caught up to. Then, binary search for the position of the third person. 
//then, if the third person doesn't catch up to the first one, this is a valid starting position. 

//then, we just try all 6 permutations of the 3 people. 

//complexity : O(n^2 * log(n) * 6)

bool is_valid(vector<ll>& d, vector<vector<ll>>& t, int s_a, int s_b, int i_a, int i_b) {
    if(s_a == s_b){
        return false;
    }
    priority_queue<pair<ll, pair<pair<int, int>, int>>> q; //{-time, {{1:-1 leaving or entering, which}, id}};
    vector<int> s(2, 0);
    s[0] = s_a;
    s[1] = s_b;
    vector<int> c(2, 0);
    c[0] = s_a;
    c[1] = s_b;
    vector<int> i(2, 0);
    i[0] = i_a;
    i[1] = i_b;
    q.push({0, {{-1, s_a}, 0}});
    q.push({0, {{-1, s_b}, 1}});
    while(q.size() != 0){
        ll time = -q.top().first;
        bool is_entering = q.top().second.first.first == -1;
        int cur = q.top().second.first.second;
        int id = q.top().second.second;
        q.pop();
        if(is_entering) {
            c[id] = cur;
            if(c[0] == c[1]) {
                return false;
            }
            time += t[i[id]][cur];
            q.push({-time, {{1, cur}, id}});
        }
        else {
            c[id] = -1;
            time += d[cur];
            cur = (cur + 1) % d.size();
            if(s[id] == cur) {
                break;
            }
            q.push({-time, {{-1, cur}, id}});
        }
    }
    return true;
}

int search(vector<ll>& d, vector<vector<ll>>& t, int s_a, int i_a, int i_b) {
    int low = 1;
    int high = d.size() - 1;
    int ans = 1e9;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        int s_b = (s_a + mid) % d.size();
        if(is_valid(d, t, s_a, s_b, i_a, i_b)) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    if(ans == 1e9){
        return -1;
    }
    ans = (s_a + ans) % d.size();
    return ans;
}

void solve(vector<ll>& d, vector<vector<ll>>& t, vector<int> order, vector<int>& ans) {
    for(int i = 0; i < d.size(); i++){
        //look for position of j
        int j = search(d, t, i, order[0], order[1]);
        if(j == -1){
            continue;
        }
        int k = search(d, t, j, order[1], order[2]);
        if(k == -1){
            continue;
        }
        if(is_valid(d, t, k, i, order[2], order[0])) {
            ans = vector<int>(3);
            ans[order[0]] = i;
            ans[order[1]] = j;
            ans[order[2]] = k;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> d(n);
    for(int i = 0; i < n; i++){
        cin >> d[i];
    }
    vector<vector<ll>> t(3, vector<ll>(n));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < n; j++){
            cin >> t[i][j];
        }
    }
    vector<int> ans(0);
    solve(d, t, {0, 1, 2}, ans);
    solve(d, t, {0, 2, 1}, ans);
    solve(d, t, {1, 0, 2}, ans);
    solve(d, t, {1, 2, 0}, ans);
    solve(d, t, {2, 1, 0}, ans);
    solve(d, t, {2, 0, 1}, ans);
    if(ans.size() == 0){
        cout << "impossible\n";
    }
    else {
        for(int i = 0; i < 3; i++){
            cout << ans[i] + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}
