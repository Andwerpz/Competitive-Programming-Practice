#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1794C

//the subsequence of largest value is always the suffix of a sorted array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n, 0);
        int l = 0;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            while(a[l] < i - l + 1){
                l ++;
            }
            cout << i - l + 1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
