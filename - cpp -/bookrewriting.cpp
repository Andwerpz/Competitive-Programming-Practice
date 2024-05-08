#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC Contest 03-22-24 Div. 1 - E

//first, compress all the words to their indexes. 

//next, observe that the number of lookups is equal to the number of 'leading elements' of sections of contiguous
//elements. When we ask Annie to memorize a word, we are effectively removing all instances of the word
//from the array. 

//when removing a word, we delete one 'leading edge' if the words to the left and to the right are the same. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    map<string, int> ind_mp;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        ind_mp.insert({s, i});
    }
    vector<int> nr_occ(n, 0);
    vector<int> a(0);
    for(int i = 0; i < m; i++){
        string s;
        while(true) {
            bool period = false;
            cin >> s;
            if(s.size() == 0){
                break;
            }
            if(s[s.size() - 1] == '.') {
                period = true;
                s = s.substr(0, (int) s.size() - 1);
            }
            if(ind_mp.find(s) != ind_mp.end()) {
                int ind = ind_mp[s];
                if(a.size() == 0 || a[(int) a.size() - 1] != ind) {
                    nr_occ[ind] ++;
                    a.push_back(ind);
                }
            }
            if(period) {
                break;
            }
        }
    }
    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        ans[i] = (int) a.size() - nr_occ[i];
    }
    for(int i = 1; i < (int) a.size() - 1; i++){
        if(a[i - 1] == a[i + 1]){
            ans[a[i]] --;
        }
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << "\n";
    }
    return 0;
}
