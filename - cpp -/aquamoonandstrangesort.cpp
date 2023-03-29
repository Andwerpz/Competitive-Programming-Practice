#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1545A

//for each unique value, count the number of even and odd indices of numbers sharing the same value. 
//then, sort the array and do another count. 

//since each number must move an even distance to still be facing right, the number of even indices and odd indices must
//be the same before and after the sort. 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int test;
    cin >> test;
    while(test-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        map<int, pair<int, int>> mb;
        map<int, pair<int, int>> ma;
        for(int i = 0; i < n; i++){
            if(mb.find(a[i]) == mb.end()) {
                mb.insert({a[i], {0, 0}});
            }
            if(i % 2 == 0){
                mb.find(a[i]) -> second.first ++;
            }
            else {
                mb.find(a[i]) -> second.second ++;
            }
        }
        sort(a.begin(), a.end());
        bool isValid = true;
        for(int i = 0; i < n; i++){
            if(ma.find(a[i]) == ma.end()) {
                ma.insert({a[i], {0, 0}});
            }
            if(i % 2 == 0){
                ma.find(a[i]) -> second.first ++;
            }
            else {
                ma.find(a[i]) -> second.second ++;
            }
        }
        for(int i = 0; i < n; i++){
            if(ma.find(a[i]) -> second.first != mb.find(a[i]) -> second.first || ma.find(a[i]) -> second.second != mb.find(a[i]) -> second.second) {
                isValid = false;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}