#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 03 D
//Kattis - pizzahawaii

//you just have to print all pairs of english and foreign ingredients that both appear in the same pizzas. 

//since there are 60 pizzas, and 20 ingredients each, we can do a brute force approach. 
//for each ingredient, we can keep track of which pizzas it's in using a long hash. 

//then at the end, just go through all foreign ingredients, and check what english ones match . 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        map<string, ll> english;
        map<string, ll> foreign;
        for(int i = 0; i < n; i++){
            string pizzapizza;
            cin >> pizzapizza;
            int amt;
            cin >> amt;
            for(int j = 0; j < amt; j++){
                string next;
                cin >> next;
                if(foreign.find(next) == foreign.end()) {
                    foreign.insert({next, 0});
                }
                foreign.find(next) -> second += ((ll) 1 << i);
            }
            cin >> amt;
            for(int j = 0; j < amt; j++){
                string next;
                cin >> next;
                if(english.find(next) == english.end()) {
                    english.insert({next, 0});
                }
                english.find(next) -> second += ((ll) 1 << i);
            }
        }   
        vector<pair<string, string>> ans(0);
        for(auto i = foreign.begin(); i != foreign.end(); i++){
            string a = i -> first;
            ll hash = i -> second;
            for(auto j = english.begin(); j != english.end(); j++) {
                if(hash == j -> second) {
                    cout << "(" << a << ", " << j -> first << ")\n";
                }
            }
        }
        cout << "\n";
    }
    
    return 0;
}
