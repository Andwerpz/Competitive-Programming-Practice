#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 11 A

//make 2n nodes, nodes 0 to n are the actual nodes, and n to 2n are parent nodes. 

//when doing operations of type 1, move smaller set to bigger set. 

ll mod = 1e9 + 7;

ll pow(ll a, ll b){
    if(b == 0){
        return 1;
    }
    ll ans = pow(a, b / 2);
    ans *= ans;
    ans %= mod;
    if(b % 2 == 1){
        ans *= a;
        ans %= mod;
    }
    return ans;
}

ll divide(ll a, ll b) {
    ll invA = pow(a, mod - 2);
    return (invA * b) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    while(!cin.eof()) {
        vector<int> a(n + 1, 0);
        vector<set<int>> s(n + 1, set<int>());
        vector<ll> sum(n + 1, 0);
        for(int i = 1; i <= n; i++){
            a[i] = i;
            sum[i] = i;
            s[i].insert(i);
        }
        while(m--){
            int type;
            cin >> type;
            if(type == 1){
                int u, v;
                cin >> u >> v;
                //add smaller set to bigger set
                int uP = a[u];
                int vP = a[v];
                if(s[uP].size() > s[vP].size()) {
                    int tmp = uP;
                    uP = vP;
                    vP = tmp;
                }
                for(auto i = s[uP].begin(); i != s[uP].end(); i++){
                    a[*i] = vP;
                    s[vP].insert(*i);
                }
                s[uP].clear();
                sum[vP] += sum[uP];
                sum[uP] = 0;
                //cout << "TYPE 1 : " << u << " " << v << " " << uP << " " << vP << "\n";
            }
            else if(type == 2){
                int u, v;
                cin >> u >> v;
                int uP = a[u];
                int vP = a[v];
                s[uP].erase(u);
                s[vP].insert(u);
                a[u] = vP;
                sum[vP] += u;
                sum[uP] -= u;
                //cout << "TYPE 2 : " << u << " " << v << " " << uP << " " << vP << "\n";
            }
            else if(type == 3){
                int u;
                cin >> u;
                int uP = a[u];
                cout << s[uP].size() << " " << sum[uP] << "\n";
            }
        }
        cin >> n >> m;
        if(n == 0){
            break;
        }
    }
    
    return 0;
}
