#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1620E

//this is probably much easier with a dsu solution, but i elected to use a map. 

//use a map storing values as keys, and all the indexes in the array that has this value as the value. 

//when adding a new element, it is sufficient to add an entry to the map if there is not an entry for the new value, then
//add the index, which is always going to be the size of the old array. 

//when merging, always merge the smaller vector into the bigger one, this will make it so that each index only has to 
//merge a maximum of log(q) times. 

//note that vector assignment automatically copies, so we want to use pointers when dealing with vectors. 

void printarr(vector<int>& a){
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " \n"[i == a.size() - 1];
    }
}

void printarr(vector<int>* a){
    printarr(*a);
}

void merge(vector<int>& a, vector<int>& b) {
    if(a.size() < b.size()) {
        swap(a, b);
    }
    for(int i = 0; i < b.size(); i++){
        a.push_back(b[i]);
    }
    //cout << "AFTER MERGE : \n";
    //printarr(a);
    //printarr(b);
}

void merge(vector<int>* a, vector<int>* b){
    merge(*a, *b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    cin >> q;
    map<int, vector<int>*> m;
    int n = 0;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int x;
            cin >> x;
            if(m.find(x) == m.end()) {
                m.insert({x, new vector<int>(0)});
            }
            m.find(x) -> second -> push_back(n);
            n ++;
        }
        else {
            int x, y;
            cin >> x >> y;
            if(x != y){
                //cout << "SET : " << x << " " << y << "\n";
                if(m.find(x) == m.end()) {
                    m.insert({x, new vector<int>(0)});
                }
                if(m.find(y) == m.end()) {
                    m.insert({y, new vector<int>(0)});
                }
                // cout << "BEFORE : \n";
                // printarr(m.find(x) -> second);
                // printarr(m.find(y) -> second);
                merge(m.find(x) -> second, m.find(y) -> second);
                // cout << "AFTER : \n";
                // printarr(m.find(x) -> second);
                // printarr(m.find(y) -> second);
                vector<int>* p = (m.find(x) -> second -> size() >= m.find(y) -> second -> size())? m.find(x) -> second : m.find(y) -> second;
                m.erase(x);
                m.erase(y);
                m.insert({y, p});
            }
        }
    }
    vector<int> ans(n);
    for(auto i = m.begin(); i != m.end(); i++){
        for(int j = 0; j < i -> second -> size(); j++){
            ans[i -> second -> at(j)] = i -> first;
        }
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
