#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1746C

//I assume that you can always make the permutation non-descending, which means no inversions. 

//to do so, just greedily assign operations to remove local inversions. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<pair<int, int>> inv(0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(i != 0 && a[i] < a[i - 1]) {
                inv.push_back({a[i - 1] - a[i], i});
            }
        }
        sort(inv.begin(), inv.end());
        int ptr = 0;
        for(int i = 1; i <= n; i++){
            if(ptr < inv.size() && inv[ptr].first <= i){
                cout << inv[ptr].second + 1 << " ";
                ptr ++;
            }
            else {
                cout << 1 << " ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
