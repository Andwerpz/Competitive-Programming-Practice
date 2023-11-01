#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2017 - L

bool check_poss(vector<pair<int, int>>& bottoms, vector<pair<int, int>>& tops, vector<int>& pairs, int n) {
    vector<vector<int>> ends(0);    //x, is end, y bot, y top
    for(int i = 0; i < n; i++){
        int startX = bottoms[i].first;
        int endX = tops[pairs[i]].first;
        int topY = tops[pairs[i]].second;
        int botY = bottoms[i].second;
        ends.push_back({startX, 1, botY, topY});
        ends.push_back({endX + 1, -1, botY, topY});
    }
    set<int> ends_set;
    sort(ends.begin(), ends.end());
    for(int i = 0; i < ends.size(); i++){
        bool is_end = ends[i][1] == -1;
        int y_bot = ends[i][2];
        int y_top = ends[i][3];
        if(is_end) {
            ends_set.erase(y_bot);
            ends_set.erase(y_top);
            continue;
        }
        //check if there is anything between y bot and y top
        auto it = ends_set.lower_bound(y_bot);
        if(it != ends_set.end()) {
            if(*it <= y_top) {
                return false;
            }
        }
        ends_set.insert(y_bot);
        ends_set.insert(y_top);
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> bottoms(n);
    vector<pair<int,int>> tops(n);
    set<vector<int>> s;
    for(int i = 0; i < n; i++) {
        cin >> bottoms[i].first;
        cin >> bottoms[i].second;
        s.insert({bottoms[i].second, bottoms[i].first, 0, i});
    }
    for(int i = 0; i < n; i++) {
        cin >> tops[i].first;
        cin >> tops[i].second;
        s.insert({tops[i].second, tops[i].first, 1, i});
    }
    //y, x, bottom or top, i
    // vector<pair<int,int>> pairs; //stores index of bottom paired with index of top
    vector<int> pairs(n);
    set<pair<int,int>> active_bottoms; //{ x, index }
    bool poss = true;
    for(auto x : s) {
        //cerr << "X : " << x[3] << ' ' << x[2] << '\n';
        if(x[2] == 0) { //bottom 
            active_bottoms.insert({x[1], x[3]}); //insert 
            //cerr << "inserting: " << x[1] << " " << x[3] << endl;
        } else { //top
            //check if there is a valid one
            if(active_bottoms.empty() || (*active_bottoms.begin()).first > x[1]) {
                //cout << "breaking?\n";
                //cout << active_bottoms.empty() << "\n";
                poss = false;
                break;
            }
            auto it = active_bottoms.upper_bound({x[1], 1e9});
            //cout << (it == active_bottoms.end()) << "\n";s
            it --;
            //cout << "it?" << (*it).second << '\n';
            //cout << "matching: " << (*it).first << " " << (*it).second << " to: " << x[1] << " " << x[0] << '\n';
            pairs[(*it).second] = x[3];
            active_bottoms.erase(*it);
        }
    }
    if(!poss) {
        //cout << "NOT POSS" << "\n";
        cout << "syntax error\n";
        return 0;
    }
    //x, y, 0/1 bottom or top corner
    if(!check_poss(bottoms, tops, pairs, n)){
        //cout << "BAD 1" << "\n";
        cout << "syntax error\n";
        return 0;
    }
    for(int i = 0; i < n; i++){
        swap(bottoms[i].first, bottoms[i].second);
        swap(tops[i].first, tops[i].second);
    }
    if(!check_poss(bottoms, tops, pairs, n)){
        //cout << "BAD 2" << "\n";
        cout << "syntax error\n";
        return 0;
    }
    for(int i = 0; i < n; i++){
        cout << pairs[i] + 1 << "\n";
    }
    
    return 0;
}
