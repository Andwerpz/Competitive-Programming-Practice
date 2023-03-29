#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1768C

//sort a in descending order. Each value can only appear a maximum of 2 times, and the first value must be n. 

//if both are true, then creating the two permutations is possible. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<pair<int, int>> b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            b[i].first = a[i];
            b[i].second = i;
        }
        sort(b.begin(), b.end());
        set<int> s1;
        set<int> s2;
        vector<int> a1(n, -1);
        vector<int> a2(n, -1);
        bool isValid = true;
        for(int i = n - 1; i >= 0; i--){
            if(s1.find(b[i].first) == s1.end()) {
                s1.insert(b[i].first);
                a1[b[i].second] = b[i].first;
            }
            else if(s2.find(b[i].first) == s2.end()) {
                s2.insert(b[i].first);
                a2[b[i].second] = b[i].first;
            }
            else {
                isValid = false;
            }
        }
        if(!isValid) {
            cout << "NO\n";
            continue;
        }
        for(int i = 1; i <= n; i++){
            if(s1.find(i) == s1.end()) {
                s1.insert(i);
            }
            else {
                s1.erase(i);
            }
            if(s2.find(i) == s2.end()) {
                s2.insert(i);
            }
            else {
                s2.erase(i);
            }
        }
        for(int i = n - 1; i >= 0; i--){
            if(a1[b[i].second] == -1) {
                a1[b[i].second] = *s1.rbegin();
                s1.erase(*s1.rbegin());
                if(a1[b[i].second] > a2[b[i].second]){
                    isValid = false;
                }
            }
            else {
                a2[b[i].second] = *s2.rbegin();
                s2.erase(*s2.rbegin());
                if(a2[b[i].second] > a1[b[i].second]) {
                    isValid = false;
                }
            }
        }
        if(!isValid) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            cout << a1[i] << " ";
        }
        cout << "\n";
        for(int i = 0; i < n; i++){
            cout << a2[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
