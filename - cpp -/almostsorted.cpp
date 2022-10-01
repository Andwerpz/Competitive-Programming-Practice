#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//MAPS 2022 C

//notice that it only takes at most n swaps to completely sort the array. 

//so you just have to simulate the sorting somehow. The hard part is figuring out which
//number to sort the given number with in constant time.

//since all the numbers are distinct, you can normalize the numbers to the range [0, n). 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> sorted(n);
    map<int, int> m;
    map<int, int> rm;
    map<int, int> indexMap;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sorted[i] = a[i];
    }
    int q;
    cin >> q;
    sort(sorted.begin(), sorted.end());
    for(int i = 0; i < n; i++){
        m.insert({sorted[i], i});
        rm.insert({i, sorted[i]});
    }
    for(int i = 0; i < n; i++){
        a[i] = m.find(a[i]) -> second;
        indexMap.insert({a[i], i});
    }
    int l = 0;
    while(a[m.find(q) -> second] != m.find(q) -> second){
        while(a[l] == l){
            l ++;
        }
        int cur = a[l];
        a[l] = a[cur];
        a[cur] = cur;
    }
    for(int i = 0; i < n; i++){
        cout << (rm.find(a[i]) -> second) << " ";
    }
    cout << "\n";
    
    return 0;
}
