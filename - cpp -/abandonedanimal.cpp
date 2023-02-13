#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 04 B

//for each ingredient that is bought, find all the shops that hold that ingredient. 
//denote min(a) as the minimum shop that holds ingredient a, and max(a) as the maximum. 

//notice that if ingredient b comes after ingredient a, then we cannot visit any shop in b
//that is less than min(a). 

//likewise, we cannot visit any shop in a that is greater than max(b) for a similar reason. 

//thus, we just need to narrow the shops down with two passes, one from the beginning and one from the end, 
//since a given shop affects all shops before and after it. 

//if there exists an ingredient after the reduction passes with more than two shops, then the path
//is ambiguous. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<pair<int, string>> inpt(k);
    for(int i = 0; i < k; i++){
        cin >> inpt[i].first >> inpt[i].second;
    }
    map<string, int> order;
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        string s;
        cin >> s;
        order.insert({s, i});
    }
    vector<set<int>> range(m, set<int>());
    for(int i = 0; i < k; i++){
        string s = inpt[i].second;
        int store = inpt[i].first;
        if(order.find(s) == order.end()) {
            continue;
        }
        int ind = order.find(s) -> second;
        range[ind].insert(store);
    }
    bool isPossible = true;
    bool isUnique = true;
    for(int i = 1; i < m && isPossible; i++){
        int pMin = *range[i - 1].begin();
        while(range[i].size() != 0 && *range[i].begin() < pMin) {
            range[i].erase(*range[i].begin());
        }
        if(range[i].size() == 0){
            isPossible = false;
            break;
        }
    }
    for(int i = m - 2; i >= 0 && isPossible; i--) {
        int pMax = *range[i + 1].begin();
        while(range[i].size() != 0 && *range[i].rbegin() > pMax) {
            range[i].erase(*range[i].rbegin());
        }
        if(range[i].size() == 0){
            isPossible = false;
            break;
        }
    }
    for(int i = 0; i < m; i++){
        //cout << range[i].first << " " << range[i].second << "\n";
        if(range[i].size() == 0) {
            isPossible = false;
        }
        if(range[i].size() != 1) {
            isUnique = false;
        }
    }
    if(!isPossible) {
        cout << "impossible\n";
    }
    else if(isUnique) {
        cout << "unique\n";
    }
    else {
        cout << "ambiguous\n";
    }
    
    return 0;
}
