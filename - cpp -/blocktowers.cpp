#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1767B

//notice that moving blocks between towers that don't include the first tower only shortens the other towers, 
//and moving blocks from the first tower to another tower shortens the first tower, so we should only move blocks
//from other towers towards the first tower. 

//go from the lowest tower to the highest tower excluding the first tower, and transfer as many blocks from 
//not the first tower to the first tower. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, first;
        cin >> n >> first;
        vector<int> a(n - 1);
        for(int i = 0; i < a.size(); i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        for(int i = 0; i < a.size(); i++){
            if(first >= a[i]){
                continue;
            }
            int diff = a[i] - first;
            first += (diff + 1) / 2;
        }
        cout << first << "\n";
    }
    
    return 0;
}
