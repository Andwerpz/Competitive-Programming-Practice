#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 08 C

//just like CSES Movie Festival II except endpoints cannot overlap

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    map<int, int> people;
    people.insert({0, k});
    vector<pair<int, int>> movies(n);
    for(int i = 0; i < n; i++){
        cin >> movies[i].first >> movies[i].second;
    }
    sort(movies.begin(), movies.end(), [](const pair<int, int>& a, const pair<int, int>& b){return a.second == b.second? a.first < b.first : a.second < b.second;});
    int ans = 0;
    for(int i = 0; i < n; i++){
        int start = movies[i].first;
        int end = movies[i].second;
        if(start <= people.begin() -> first){    //there is no person that will be able to watch this one
            continue;
        }
        ans++;
        auto iter = people.lower_bound(start);
        if(iter == people.end() || iter -> first >= start){
            iter --;
        }
        int key = iter -> first;
        //cout << "KEY : " << key << endl;
        iter -> second --;
        if(iter -> second == 0){
            people.erase(key);
        }
        if(people.find(end) == people.end()){
            people.insert({end, 0});
        }
        auto nextIter = people.find(end);
        nextIter -> second ++;
    }
    cout << ans << endl;
    
    return 0;
}
