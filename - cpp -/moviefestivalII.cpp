
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1632

//just like movie festival 1, you want to prioritize watching movies based on ascending end time, but unlike movie
//festival 1, k is no longer stuck at 1. 

//the key is to choose the right person to watch each movie. Given a movie's start time, you want to pick the person with 
//their next available time as close to that start time as possible. 

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
        if(start < people.begin() -> first){    //there is no person that will be able to watch this one
            continue;
        }
        ans++;
        auto iter = people.lower_bound(start);
        if(iter == people.end() || iter -> first > start){
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
