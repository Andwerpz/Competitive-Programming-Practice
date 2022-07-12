#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1701B

//i guess that d = 2 will always be optimal, no matter the given n. 

//we can greedily construct the permutation a. 

//there exist 'chains' of numbers, number c_i * d = c_(i + 1) in chain c. 

//notice that chains cannot intersect; if two chains share a number, then they are the same chain. 

//thus, we can just create a permutation out of a list of maximally sized chains. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        cout << "2\n";
        vector<bool> v(n + 1);
        for(int i = 1; i <= n; i++){
            if(!v[i]){
                for(int j = i; j <= n; j *= 2){
                    cout << j << " ";
                    v[j] = true;
                }
            }
        }
        cout << "\n";
    }
    
    return 0;
}
