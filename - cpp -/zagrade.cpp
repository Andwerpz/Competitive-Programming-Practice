#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 05 H

//notice that through removal of brackets, an invalid set of brackets will never become valid; you have to remove an invalid
//set to make another invalid set into a valid one. 

//therefore, there are only a maximum of 10 pairs of brackets, which leads to 2^10 - 1 ways to remove them. 

//note that some pairs of brackets when removed generate the same expression, so you should check for duplicates using a 
//set or something. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    vector<pair<int, int>> p(0);
    stack<int> st;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '('){
            st.push(i);
        }
        if(s[i] == ')'){
            int prev = st.top();
            if(s[prev + 1] != '-' || prev == 0){
                p.push_back({prev, i});
            }
            st.pop();
        }
    }
    set<string> ans;
    for(int i = 1; i < (1 << p.size()); i++){
        set<int> r;
        string next = "";
        for(int j = 0; j < p.size(); j++){
            if((i >> j) & 1 == 1){
                r.insert(p[j].first);
                r.insert(p[j].second);
            }
        }
        for(int j = 0; j < s.length(); j++){
            if(r.find(j) != r.end()){
                continue;
            }
            next += s[j];
        }
        ans.insert(next);
    }
    vector<string> ans2(0);
    for(auto i = ans.begin(); i != ans.end(); i++){
        ans2.push_back(*i);
    }
    sort(ans2.begin(), ans2.end());
    for(int i = 0; i < ans2.size(); i++){
        cout << ans2[i] << "\n";
    }
    
    return 0;
}
