#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<string> getLandmarks() {
    int n;
    cin >> n;
    vector<string> ans(n);
    for(int i = 0; i < n; i++){
        cin >> ans[i];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    stack<string> st;
    set<string> v;
    string cur = getLandmarks()[0];
    v.insert(cur);
    cout << cur << endl;
    while(true) {
        vector<string> a = getLandmarks();
        string nextVisit = "";
        bool allVisited = true;
        for(string s : a){
            if(v.find(s) == v.end()){
                v.insert(s);
                st.push(cur);
                nextVisit = s;
                allVisited = false;
                break;
            }
        }
        if(allVisited){
            nextVisit = st.top();
            st.pop();
        }
        cur = nextVisit;
        cout << nextVisit << endl;
        if(nextVisit == "exit"){
            break;
        }
    }    
    
    return 0;
}
