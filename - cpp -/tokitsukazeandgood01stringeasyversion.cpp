#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1678B1

//generate a new array with the lengths for each segment. 

//notice that you only need to edit the lengths of the segments between two odd length segments. 

//You can edit each at most once to resolve the oddness of the endpoints. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> groups(0);
        char prev = s[0];
        int count = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == prev){
                count ++;
            }
            else{
                prev = s[i];
                groups.push_back(count);
                count = 1;
            }
        }
        groups.push_back(count);
        int ans = 0;
        count = 0;
        bool resolvingOdd = false;
        for(int i = 0; i < groups.size(); i++){
            if(groups[i] % 2 == 1){
                if(!resolvingOdd){
                    resolvingOdd = true;
                }
                else{
                    resolvingOdd = false;
                    ans += count + 1;
                    count = 0;
                }
            }
            else if(resolvingOdd){
                count ++;
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
