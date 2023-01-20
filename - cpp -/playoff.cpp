#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1767D

//i can't really explain why this solution works, for that, go look at the tutorial. 

//lets say that there are 'a' rounds where high skill wins, and 'b' rounds where low skill wins. 
//2^a - 1 of the lowest skill players can't win, and 2^b - 1 of the highest skill players can't win. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    int l = 1;
    int r = (1 << n);
    int pl = 0;
    int pr = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '1') {
            l += (1 << pl);
            pl ++;
        }
        else {
            r -= (1 << pr);
            pr ++;
        }
    }
    for(int i = l; i <= r; i++){
        cout << i << " ";
    }
    cout << "\n";
    
    return 0;
}
