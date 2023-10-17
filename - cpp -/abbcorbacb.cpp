#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1873G

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        bool bb = false;
        bool no_b = true;
        int nr_a = 0;
        int l_a = 0;
        int min_seg = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'B') {
                if(no_b) {
                    min_seg = l_a;
                }
                min_seg = min(min_seg, l_a);
                l_a = 0;
                no_b = false;
            }
            if(i != s.size() - 1 && s[i] == 'B' && s[i + 1] == 'B'){
                bb = true;
            }
            if(s[i] == 'A') {
                l_a ++;
                nr_a ++;
            }
        }
        min_seg = min(min_seg, l_a);
        if(no_b) {
            cout << "0\n";
            continue;
        }
        if(bb) {
            cout << nr_a << "\n";
            continue;
        }
        cout << nr_a - min_seg << "\n";
    }
    
    return 0;
}
