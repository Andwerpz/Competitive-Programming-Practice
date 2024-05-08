#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1965A

//if we're taking the same amount from every pile, then this situation is identical to if we had a single pile with
//predetermined 'breakpoints' in stones that we can take, which are determined by the size of the individual piles. 

//if the distances between the breakpoints were all greater than 1, then the first person who goes can always win. 
//If the current breakpoint is not the last one, Alice just takes all stones except for the last one, which forces Bob to take
//1 stone. This guarantees that Alice will be the one to 'start' each breakpoint. 

//In the case that there is one gap that is of size one, then all that does is change the parity of who is going first. 
//But, if this gap is not the first one, the person who is currently in control can manipulate it such that after the size
//1 gap, they are still in control. 

//Therefore, we just need to count the number of size 1 gaps at the beginning, to determine who goes first. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        set<int> s;
        s.insert(0);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            s.insert(next);
        }
        vector<int> a(0);
        for(auto i = s.begin(); i != s.end(); i++){
            a.push_back(*i);
        }
        bool alice_win = true;
        for(int i = 1; i < a.size() - 1; i++){
            if(a[i] - a[i - 1] != 1){
                break;
            }
            alice_win = !alice_win;
        }
        cout << (alice_win? "Alice" : "Bob") << "\n";
    }
    
    return 0;
}
