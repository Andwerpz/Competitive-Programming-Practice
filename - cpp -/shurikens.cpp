#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1413D

//you can first parse the events in reverse to generate a possible order in which the placements happened, 
//then check it. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n * 2, 0);
    for(int i = 0; i < 2 * n; i++){
        string s;
        cin >> s;
        if(s == "+"){
            a[i] = -1;
        }
        else {
            cin >> a[i];
        }
    }
    bool isValid = true;
    set<int> s;
    for(int i = 2 * n - 1; i >= 0; i--){
        if(a[i] == -1){
            if(s.size() == 0){
                isValid = false;
                break;
            }
            a[i] = *s.begin();
            s.erase(*s.begin());
        }
        else {
            s.insert(a[i]);
        }
    }
    if(!isValid) {
        cout << "NO\n";
        return 0;
    }
    vector<int> ans(0);
    for(int i = 0; i < 2 * n; i++){
        if(s.find(a[i]) == s.end()) {
            s.insert(a[i]);
            ans.push_back(a[i]);
        }
        else {
            if(a[i] != *s.begin()) {
                isValid = false;
                break;
            }
            s.erase(a[i]);
        }
    }
    if(isValid) {
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    else {
        cout << "NO\n";
    }

    return 0;
}
