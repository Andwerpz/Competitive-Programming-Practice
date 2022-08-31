#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        vector<int> max(n, 1 << 30);
        vector<int> min(n);
        max[n - 1] = b[n - 1];
        int pb = 0;
        for(int i = 0; i < n; i++){
            while(b[pb] < a[i]){
                pb ++;
            }
            if(i == pb && i != 0){
                max[i - 1] = b[i - 1];
            }   
            min[i] = b[pb] - a[i];
            cout << min[i] << " ";
        }
        cout << "\n";
        for(int i = n - 2; i >= 0; i--){
            max[i] = std::min(max[i], max[i + 1]);
        }
        for(int i = 0; i < n; i++){
            cout << (max[i] - a[i]) << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
