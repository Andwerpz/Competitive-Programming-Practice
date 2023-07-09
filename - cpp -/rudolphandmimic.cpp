#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1846F

//wait until the mimic changes for the first time. Then, remove all items that are not the same
//as the mimic. Then when the mimic changes again, you can identify the mimic. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(10);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            a[next] ++;
        }
        int found = -1;
        vector<int> type(n);
        while(found == -1) {
            cout << "- 0" << endl;
            vector<int> b(10);
            for(int i = 0; i < n; i++){
                cin >> type[i];
                b[type[i]] ++;
            }
            for(int i = 0; i < 10; i++){
                if(b[i] > a[i]){
                    found = i;
                }
            }
        }
        vector<int> r(0);
        for(int i = 0; i < n; i++){
            if(type[i] != found) {
                r.push_back(i + 1);
            }
        }
        cout << "- " << r.size() << " ";
        for(int i = 0; i < r.size(); i++){
            cout << r[i] << " ";
        }
        cout << endl;
        int ans = -1;
        while(true){
            vector<int> b(n - r.size());
            for(int i = 0; i < b.size(); i++){
                cin >> b[i];
                if(b[i] != found) {
                    ans = i + 1;
                }
            }
            if(ans != -1){
                break;
            }
            cout << "- 0" << endl;
        }
        cout << "! " << ans << endl;
    }
    
    return 0;
}
