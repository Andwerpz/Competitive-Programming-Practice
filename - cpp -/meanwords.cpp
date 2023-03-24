#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//University of Alberta Programming Contest 2023 J

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(0);
    vector<int> cnt(0);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = a.size(); j < s.size(); j++){
            a.push_back(0);
            cnt.push_back(0);
        }
        for(int j = 0; j < s.size(); j++){
            a[j] += (int) s[j];
            cnt[j] ++;
        }
    }
    for(int i = 0; i < a.size(); i++){
        cout << (char) (a[i] / cnt[i]);
    }
    cout << "\n";
    
    return 0;
}
