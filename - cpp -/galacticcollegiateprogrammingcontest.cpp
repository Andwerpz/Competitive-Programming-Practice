#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 08 G

//ordered set cheese. 

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<vector<int>,null_type,less<vector<int>>,rb_tree_tag,tree_order_statistics_node_update>

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    ordered_set s;
    vector<vector<int>> teams(n, vector<int>(3));
    for(int i = 0; i < n; i++){
        teams[i][0] = 0;
        teams[i][1] = 0;
        teams[i][2] = n - i;
        s.insert({0, 0, n - i});
    }
    //cout << "YEN" << endl;
    for(int i = 0; i < m; i++){
        int t, p;
        cin >> t >> p;
        t--;
        s.erase(teams[t]);
        teams[t][0] ++;
        teams[t][1] -= p;
        s.insert(teams[t]);
        cout << n - s.order_of_key(teams[0]) << "\n";
    }
    
    return 0;
}
