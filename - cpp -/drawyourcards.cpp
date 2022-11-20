#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Week 6F

//you can just simulate it using a map with upper_bound() and lower_bound(). 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
    }
    vector<int> c(n, -1);   //for each card, which card did this one replace
    vector<int> t(n, -1);
    map<int, int> m;
    for(int i = 0; i < n; i++){
        int nextCard = a[i];
        auto p = m.upper_bound(nextCard);
        if(p == m.end()){
            m.insert({nextCard, 1});
        }
        else {
            int amt = p -> second + 1;
            int prev = p -> first;
            m.erase(prev);
            m.insert({nextCard, amt});
            c[nextCard] = prev;
        }
        if(m.find(nextCard) -> second == k) {
            //cout << "EATEN : " << nextCard << "\n";
            m.erase(nextCard);
            t[nextCard] = i + 1;
        }
    }
    vector<int> ans(n, -1);
    for(int i = 0; i < n; i++){
        if(t[i] != -1){
            int p = i;
            ans[i] = t[i];
            while(c[p] != -1) {
                p = c[p];
                ans[p] = t[i];
            }
        }
    }
    for(int i : ans) {
        cout << i << " ";
    }
    cout << "\n";
    
    return 0;
}
