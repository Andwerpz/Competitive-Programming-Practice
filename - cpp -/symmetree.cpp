#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1800G

//this problem uses a standard rooted tree hashing technique. If we know how to do that, then it becomes trivial. 
//To hash rooted trees, we can use the cantor pairing function. 

//to check if a subtree is symmetrical, we just have to figure out if the hashes of the children of the root can make
//a palindrome. If the number of children is odd, then the center child must also be symmetrical in order for the 
//root to be symmetrical. 

vector<vector<int>> c;
vector<int> sub_size;
vector<ll> sub_hash;

void calc_size(int cur) {
    sub_size[cur] = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        calc_size(next);
        sub_size[cur] += sub_size[next];
    }
}

ll cantor(ll a, ll b, ll mod) {
    return ((a + b) * (a + b + 1) / 2 + b) % mod;
}

ll calc_hash(int cur, ll mod) {
    ll cur_hash = c[cur].size() + 1;
    vector<ll> chash(c[cur].size());
    for(int i = 0; i < c[cur].size(); i++){
        chash[i] = calc_hash(c[cur][i], mod);
    }
    sort(chash.begin(), chash.end());
    for(int i = 0; i < c[cur].size(); i++){
        cur_hash = cantor(cur_hash, chash[i], mod);
    }
    sub_hash[cur] = cur_hash;
    return cur_hash;
}

bool is_symmetrical(int cur) {
    //first, go through subtree sizes
    map<int, vector<int>> size_map;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        int nsize = sub_size[next];
        if(size_map.find(nsize) == size_map.end()) {
            size_map.insert({nsize, vector<int>(0)});
        }
        size_map[nsize].push_back(next);
    }
    int mid_tree = -1;
    for(auto i = size_map.begin(); i != size_map.end(); i++){
        vector<int> arr = i -> second;
        map<ll, int> hash_set;
        for(int j = 0; j < arr.size(); j++){
            int next = arr[j];
            ll hash = sub_hash[next];
            if(hash_set.find(hash) == hash_set.end()) {
                hash_set.insert({hash, next});
            }
            else {
                hash_set.erase(hash);
            }
        }
        if(hash_set.size() != 0){
            if(hash_set.size() > 1){
                return false;
            }
            if(mid_tree != -1){
                return false;
            }
            mid_tree = hash_set.begin() -> second;
        }
    }
    if(mid_tree != -1){
        return is_symmetrical(mid_tree);
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> edges(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
        //better tree representation
        c = vector<vector<int>>(n, vector<int>(0));
        vector<bool> v(n, false);
        v[0] = true;
        stack<int> s;
        s.push(0);
        while(s.size() != 0){
            int cur = s.top();
            s.pop();
            for(int i = 0; i < edges[cur].size(); i++){
                int next = edges[cur][i];
                if(v[next]){
                    continue;
                }
                v[next] = true;
                c[cur].push_back(next);
                s.push(next);
            }
        }
        sub_size = vector<int>(n, 0); //size of subtree
        calc_size(0);
        sub_hash = vector<ll>(n, 0);
        calc_hash(0, 1e9 + 7);
        cout << (is_symmetrical(0)? "YES\n" : "NO\n");
    }
    
    return 0;
}
