#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string a;
        cin >> a;
        bool decrease = false;
        char min = (char) '0';
        for(int i = 0; i < a.length(); i++){
            if(i != 0 && a[i - 1] > a[i]) {
                decrease = true;
            }
            if(!decrease){
                min = max(a[i], min);
            }
            else {
                min = std::min(a[i], min);
            }
            
            cout << min;
        }
        cout << "\n";
    }
    
    return 0;
}
