#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1721C

//notice that a[i] <= b[i]. This is true because d[i] is never negative; you only add to the value in a[i]. 

//calculating the minimum d[i] is pretty simple. For each a[i], find the minimum b[j] where a[i] <= b[j], and b[j] - a[i] is the minimum. 

//calculating the maximum d[i] is slightly harder. Notice that we can't just say that d[i] = b[n - 1] - a[i], since then, a[n - 1] might not have
//any b[j] that is greater than it. So the key here is to look for the maximum j where for all k, i <= k <= j, a[k] <= b[k - 1]. 

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
