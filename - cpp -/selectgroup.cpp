#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 02 D

//interesting problem related to parsing in nested inputs

map<string, set<string>> m;

set<string> find(vector<string> a) {
    string command = a[0];
    if(a.size() == 1) {
        return m.find(a[0]) -> second;
    }
    set<string> ans;
    //split command into subcommands
    int l = 1;
    int r = 1;
    int cmdCnt = 0;
    int gCnt = 0;
    for(int i = 1; i < a.size(); i++){
        if(a[i] == "union" || a[i] == "intersection" || a[i] == "difference") {
            cmdCnt ++;
        }
        else {
            gCnt ++;
        }
        if(cmdCnt + 1 == gCnt) {
            r = i;
            break;
        }
    }
    vector<string> lCmd, rCmd;
    for(int i = l; i <= r; i++){
        lCmd.push_back(a[i]);
    }
    for(int i = r + 1; i < a.size(); i++){
        rCmd.push_back(a[i]);
    }
    set<string> lAns = find(lCmd);
    set<string> rAns = find(rCmd);
    if(a[0] == "union") {
        for(auto i = lAns.begin(); i != lAns.end(); i++){
            ans.insert(*i);
        }
        for(auto i = rAns.begin(); i != rAns.end(); i++){
            ans.insert(*i);
        }
    }
    else if(a[0] == "intersection") {
        for(auto i = lAns.begin(); i != lAns.end(); i++){
            if(rAns.find(*i) != rAns.end()) {
                ans.insert(*i);
            }
        }
    }
    else if(a[0] == "difference") {
        for(auto i = lAns.begin(); i != lAns.end(); i++){
            if(rAns.find(*i) == rAns.end()) {
                ans.insert(*i);
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while(!cin.eof()) {
        string line;
        getline(cin, line);
        line += " ";
        vector<string> a(0);
        int l = 0;
        while(l < line.size()) {
            int r = line.find_first_of(' ', l);
            a.push_back(line.substr(l, r - l));
            l = r + 1;
        }
        if(a[0] == "group") {
            string name = a[1];
            set<string> group;
            for(int i = 3; i < a.size(); i++){
                group.insert(a[i]);
            }
            m.insert({name, group});
            continue;
        }
        set<string> ans = find(a);
        for(auto i = ans.begin(); i != ans.end(); i++) {
            cout << *i << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
