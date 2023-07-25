#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1852B

//we can first assign each index to be either positive or negative. 
//notice that indices with a higher value must be assigned positive and as you go lower, they'll be assigned negative. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, int>> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a.begin(), a.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
            if(a.first != b.first){
                return a.first > b.first;
            }
            return a.second < b.second;
        });
        //assign pos / neg
        vector<int> pos(0);
        vector<int> neg(0);
        for(int i = 0; i < n; i++){
            //can it be negative?
            if(i >= a[i].first) {
                //cout << "IS NEGATIVE : " << a[i].first << " " << a[i].second << "\n";
                neg.push_back(i);
            }
            else {
                //cout << "IS POSITIVE : " << a[i].first << " " << a[i].second << "\n";
                pos.push_back(i);
            }
        }
        reverse(neg.begin(), neg.end());
        vector<pair<int, int>> val(n);
        for(int i = 0; i < n; i++){
            val[i] = {0, a[i].second};
        }
        bool isValid = true;
        int pptr = 0;
        int nptr = 0;
        int ptr = n;
        while(pptr < pos.size() || nptr < neg.size()){
            if(nptr != neg.size() && a[neg[nptr]].first == pptr) {
                //place negative number
                val[neg[nptr]].first = -ptr;
                ptr --;
                nptr ++;
                continue;
            }
            if(pptr != pos.size() && a[pos[pptr]].first == n - nptr) {
                //place positive number
                val[pos[pptr]].first = ptr;
                ptr --;
                pptr ++;
                continue;
            }
            isValid = false;
            break;
        }
        if(!isValid){
            cout << "NO\n";
            continue;
        }
        // for(int i = 0; i < n; i++){
        //     cout << val[i].first << " " << val[i].second << "\n";
        // }
        cout << "YES\n";
        sort(val.begin(), val.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
            return a.second < b.second;
        });
        for(int i = 0; i < n; i++){
            cout << val[i].first << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
