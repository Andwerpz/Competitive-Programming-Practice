#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 11 F

//brute force. Sample size is maximum 12

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll ans = 0;
        int caseNo;
        cin >> caseNo;
        vector<int> a(12, 0);
        for(int i = 0; i < 12; i++){
            cin >> a[i];
        }
        for(int i = 1; i < 11; i++){
            for(int j = i + 1; j < 12; j++){
                int min = 1e9;
                for(int k = i; k < j; k++){
                    min = std::min(min, a[k]);
                }
                if(min > a[i - 1] && min > a[j]){
                    ans ++;
                }
            }
        }
        cout << caseNo << " " << ans << "\n";
    }
    
    return 0;
}
