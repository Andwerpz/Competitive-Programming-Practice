#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1867A

//my intuition said to sort the array, and match high elements in the array to low elements in the permutation. 
//this way, we can potentially generate a new element every time. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, int>> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        for(int i = 0; i < n; i++){
            a[i].first = i + 1;
        }
        sort(a.begin(), a.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool{
            return a.second < b.second;
        });
        for(int i = 0; i < n; i++){
            cout << a[i].first << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
