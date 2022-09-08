#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1728A

//The biggest group of balls is guaranteed to be able to be the last group. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int maxIndex = 0;
        int max = a[0];
        for(int i = 0; i < n; i++){
            if(a[i] > max){
                maxIndex = i;
                max = a[i];
            }
        }
        cout << (maxIndex + 1) << "\n";
    }
    
    return 0;
}
