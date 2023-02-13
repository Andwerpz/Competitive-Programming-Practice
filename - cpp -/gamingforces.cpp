#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1792A

//notice that you only can save moves if you can kill two monsters in one move. 

//thus, the number of saved moves is equal to floor(cnt of monsters on one health / 2). 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int cnt = 0;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            cnt += next == 1? 1 : 0;
        }
        cout << n - (cnt / 2) << "\n";
    }
    
    return 0;
}
