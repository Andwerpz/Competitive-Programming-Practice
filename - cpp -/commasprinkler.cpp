#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2018 B

//we can treat this like a graph problem. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    getline(cin, s);
    vector<string> a(0);
    int l = 0;
    vector<bool> hasComma(0);
    vector<bool> hasPeriod(0);
    map<string, vector<int>> m;
    map<string, pair<int, int>> v;  //first : after this one, second : before this one
    for(int i = 0; i <= s.size(); i++){
        if(i == s.size() || s[i] == ' '){
            string next = s.substr(l, i - l);
            hasPeriod.push_back(*next.rbegin() == '.');
            hasComma.push_back(*next.rbegin() == ',');
            if(hasPeriod[hasPeriod.size() - 1] || hasComma[hasComma.size() - 1]) {
                next = next.substr(0, next.size() - 1);
            }
            a.push_back(next);
            if(m.find(next) == m.end()){
                m.insert({next, vector<int>(0)});
            }
            m.find(next) -> second.push_back(a.size() - 1);
            if(v.find(next) == v.end()) {
                v.insert({next, {false, false}});
            }
            l = i + 1;
            //cout << next << " " << *hasComma.rbegin() << " " << *hasPeriod.rbegin() << "\n";
        }
    }
    queue<pair<string, int>> q;
    for(int i = 0; i < a.size(); i++){
        if(!hasComma[i]) {
            continue;
        }
        if(!v[a[i]].first){
            v[a[i]].first = true;
            q.push({a[i], 0});
        }
        if(i != a.size() - 1 && !v[a[i + 1]].second) {
            v[a[i + 1]].second = true;
            q.push({a[i + 1], 1});
        }
    }
    while(q.size() != 0){
        string curs = q.front().first;
        int type = q.front().second;
        q.pop();
        if(type == 0){
            //mark strings of the same type with commas
            for(int i = 0; i < m[curs].size(); i++){
                int ind = m[curs][i];
                if(hasPeriod[ind]) {
                    continue;
                }
                hasComma[ind] = true;
                if(ind != a.size() - 1 && !v[a[ind + 1]].second) {
                    v[a[ind + 1]].second = true;
                    q.push({a[ind + 1], 1});
                }
            }
        }
        else {
            //mark strings before with commas
            for(int i = 0; i < m[curs].size(); i++){
                int ind = m[curs][i];
                if(ind == 0){
                    continue;
                }
                if(hasPeriod[ind - 1]) {
                    continue;
                }
                if(!v[a[ind - 1]].first) {
                    v[a[ind - 1]].first = true;
                    q.push({a[ind - 1], 0});
                }
            }
        }
    }
    for(int i = 0; i < a.size(); i++){
        cout << a[i];
        if(hasPeriod[i]) {
            cout << ".";
        }
        else if(hasComma[i]) {
            cout << ",";
        }
        cout << " ";
    }
    cout << "\n";
    
    return 0;
}
