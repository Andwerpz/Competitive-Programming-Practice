#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1277B

//the best strategy is to sort the numbers in decending order and check if they can be divided by 2.

//if they can be, then increment your operation count, and divide it by 2, placing the quotient back 
//into the array. 

//if they can't then just remove it. 

//since you can divide all of the same number at a time, you can get rid of duplicates. Just use a set. 
//set is also useful since you can define an ordering. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        auto compare = [] (int a, int b) {return b < a;};
        set<int, decltype(compare)> s(compare);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            s.insert(next);
        }
        int ans = 0;
        while(s.size() != 0){
            int next = *s.begin();
            if(next % 2 == 0){
                ans ++;
                s.insert(next / 2);
            }
            s.erase(next);
        }
        cout << ans << endl;
    }
    
    return 0;
}
