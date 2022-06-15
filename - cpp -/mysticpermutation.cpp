#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1689B

//you can construct a mystic permutation just by iterating through the array, and picking the number from
//the set that isn't currently a_i. All you have to worry about is the last two numbers. 

//to construct the lexographically minimum permutation, all you have to do is make sure the number you pick
//every time is the minimum out of the numbers that you have left. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        set<int> s;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            s.insert(a[i]);
        }
        if(n == 1){
            cout << "-1\n";
            continue;
        }
        vector<int> ans(n);
        for(int i = 0; i < n - 2; i++){
            auto ptr = s.begin();
            if(a[i] == *ptr) {
                ptr ++;
            }
            cout << *ptr << " ";
            s.erase(*ptr);
        }
        auto ptr = s.begin();
        int sl = *ptr;
        ptr ++;
        int last = *ptr;
        if(last == a[n - 1] || sl == a[n - 2]) {
            cout << last << " " << sl;
        }
        else if(last == a[n - 2] || sl == a[n - 1]){
            cout << sl << " " << last;
        }
        else{
            cout << min(last, sl) << " " << max(last, sl);
        }
        cout << endl;
    }
    
    return 0;
}
