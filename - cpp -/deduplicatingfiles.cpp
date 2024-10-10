#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - deduplicatingfiles

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        set<string> s;
        vector<string> a;
        for(int i = 0; i < n; i++){
            string line;
            if(i == 0){
                getline(cin, line);
            }
            getline(cin, line);
            s.insert(line);
            a.push_back(line);
        }
        int ans2 = 0;
        map<char, map<string, int>> m;
        for(int i = 0; i < n; i++){
            string line = a[i];
            char hash = 0;
            for(int j = 0; j < line.size(); j++){
                hash ^= line[j];
            }
            m[hash][line] ++;
        }
        for(auto i = m.begin(); i != m.end(); i++){
            int tot = 0;
            for(auto j = i -> second.begin(); j != i -> second.end(); j++){
                tot += j -> second;
                ans2 -= j -> second * (j -> second - 1) / 2;
            }
            ans2 += tot * (tot - 1) / 2;
        }
        cout << s.size() << " " << ans2 << "\n";
        cin >> n;
    }
    
    return 0;
}
