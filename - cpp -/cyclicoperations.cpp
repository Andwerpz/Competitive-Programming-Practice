#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1867D

//if we interpret the array A as a graph, where the index is the node id, and the element at A[i] is the outgoing edge
//we can interpret the operation done by the array L as forcibly adding a cycle into A. 

//thus, if we find all the cycles in A, they all have to be length K. As long as this is true, then the array A
//is constructible using the operations. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        bool isValid = true;
        if(k == 1){
            for(int i = 0; i < n; i++){
                if(a[i] != i){
                    isValid = false;
                }
            } 
        }  
        else {
            vector<bool> v(n, false);
            //each thing needs a cycle of length exactly k. 
            for(int i = 0; i < n; i++){
                if(v[i]){
                    continue;
                }
                bool foundCycle = false;
                int cycleSize = 0;
                stack<int> path;
                path.push(i);
                while(!v[a[path.top()]]) {
                    v[a[path.top()]] = true;
                    path.push(a[path.top()]);
                }
                int end = a[path.top()];
                while(path.size() != 0){
                    cycleSize ++;
                    if(path.top() == end) {
                        foundCycle = true;
                        break;
                    }
                    path.pop();
                }
                if(foundCycle) {
                    if(cycleSize != k){
                        isValid = false;
                        break;
                    }
                }
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
