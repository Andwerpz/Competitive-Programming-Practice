
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 29C

//learned alot about how to use maps in c++ with this one. Iterators are confusing, especially since they're handled automatically in java

//you can just start at one end, and traverse to the other end.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    map<int, int> dict;
    map<int, vector<int>> c;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        // c[a] = b;
        // c[b] = a;
        // c.insert(a, b);
        // c.insert(b, a);
        if(c.find(a) == c.end()){
            c.insert(pair<int, vector<int>>(a, {b}));
        }
        else{
            c.at(a).push_back(b);
        }
        if(c.find(b) == c.end()){
            c.insert(pair<int, vector<int>>(b, {a}));
        }
        else{
            c.at(b).push_back(a);
        }
        // c.insert(std::pair<int, int>(a, b));
        // c.insert(std::pair<int, int>(b, a));
        if(dict.find(a) != dict.end()){
            dict.at(a) = dict.find(a)->second + 1;
        }
        else {
            dict.insert(pair<int, int>(a, 1));
        }
        if(dict.find(b) != dict.end()){
            dict.at(b) = dict.find(b)->second + 1;
        }
        else{
            dict.insert(pair<int, int>(b, 1));
        }
    }
    int pointer = -1;
    for(map<int, int>::iterator i = dict.begin(); i != dict.end(); i++){
        if(i->second == 1){
            pointer = i->first;
            break;
        }
    }
    cout << pointer << " ";
    set<int> v;
    v.insert(pointer);
    while(true){
        vector<int> cur = c.find(pointer)->second;
        bool cont = false;
        for(int i = 0; i < cur.size(); i++){
            int next = cur[i];
            if(v.find(next) == v.end()){
                v.insert(next);
                pointer = next;
                cout << pointer << " ";
                cont = true;
                break;
            }
        }
        if(!cont){
            break;
        }
    }
    //cout << "END";
    cout << endl;

    return 0;
}



