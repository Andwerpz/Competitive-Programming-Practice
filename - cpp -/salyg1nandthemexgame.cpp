#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1867C

//first observe that if 0 doesn't exist within the set, then it is always optimal for alice to add the 0, 
//and end the game. 

//if alice doesn't add the 0, then she either added the new minimum element in S, in which case the game would end
//and MEX(S) would be 0, or if she didn't add the minimum element, bob would just take the minimum element, making it
//so that MEX(S) == 0 is guaranteed. 

//otherwise, S contains 0, and it is optimal for alice to add into S, MEX(S). 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        set<int> s;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            s.insert(next);
        }
        //find all elements that don't have the next element
        set<int> no;
        for(auto i = s.begin(); i != s.end(); i++){
            int val = *i;
            if(s.find(val + 1) == s.end()) {
                no.insert(val + 1);
            }
        }
        bool gameEnd = false;
        while(s.find(0) != s.end()) {
            //insert the minimum value that is missing
            int nval = *no.begin();
            s.insert(nval);
            no.erase(nval);
            if(s.find(nval + 1) == s.end()) {
                no.insert(nval + 1);
            }
            cout << nval << endl;
            int rm;
            cin >> rm;
            if(rm == -1){
                gameEnd = true;
                break;
            }
            s.erase(rm);
            if(no.find(rm + 1) == no.end()) {
                no.erase(rm + 1);
            }
            if(s.find(rm - 1) != s.end()) {
                no.insert(rm);
            }
        }
        if(!gameEnd) {
            cout << "0" << endl;
            int rm;
            cin >> rm;
        }
    }
    
    return 0;
}
