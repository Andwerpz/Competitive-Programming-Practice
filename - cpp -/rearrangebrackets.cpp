#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1821E

//how is this problem rated 2100?
//it seems like this is not the intended solution, the intended solution is more rigorous and uses dp.

//the idea is that nested brackets = bad. Every time there is a nested bracket, the cost increases because we have to 
//remove the brackets that are nested first, the 'children', before we can remove the 'parent'. 

//for each bracket, we count how many brackets it has nested inside it. That is the contribution of this bracket to the cost. 

//using one operation, we can choose one parent, and make it so that it doesn't have any children anymore. Thus it's contribution
//to the cost is now 0. 

//now, we want to enumerate for each bracket, what is the cost it contributes, and remove the k highest costs using the operations. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int k;
        cin >> k;
        string s;
        cin >> s;
        stack<int> st;
        vector<int> c(0);
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '(') {
                st.push(0);
            }
            else {
                int next = st.top();
                st.pop();
                c.push_back(next);
                if(st.size() != 0){
                    st.top() += next + 1;
                }
            }
        }
        ll ans = 0;
        sort(c.begin(), c.end());
        for(int i = 0; i < (int) c.size() - k; i++){
            ans += c[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
