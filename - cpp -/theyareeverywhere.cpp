#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 701C

//classic 2 pointer subarray with set problem. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    set<char> s;
    string c;
    cin >> c;
    for(int i = 0; i < c.size(); i++){
        s.insert(c[i]);
    }
    int numUnique = s.size();
    int j = 0;
    int ans = n;
    map<char, int> m;
    for(int i = 0; i < n; i++){
        while(j < n && m.size() < numUnique){
            if(m.find(c[j]) != m.end()){
                m.find(c[j]) -> second ++;
            }
            else{
                m.insert({c[j], 1});
            }
            j++;
        }
        if(m.size() == numUnique){
            ans = min(ans, j - i);
        }
        m.find(c[i]) -> second --;
        if(m.find(c[i]) -> second == 0){
            m.erase(c[i]);
        }
    }
    cout << ans << endl;
    
    return 0;
}
