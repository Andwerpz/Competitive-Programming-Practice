#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 528A

//use a set to keep track of the segment lengths horizontally and vertically.
//the largest piece always has to be a product of the largest horizontal and vertical segments. 

void insert(map<int, int>& m, int val) {
    if(m.find(val) == m.end()) {    //if m does not contain val
        m.insert({val, 0});
    }
    m[val] ++;
}

void erase(map<int, int>& m, int val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(val);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int w, h, n;
    cin >> w >> h >> n;
    map<int, int> widths, heights;
    set<int> cut_h, cut_v;
    cut_h.insert(0);
    cut_h.insert(h);
    cut_v.insert(0);
    cut_v.insert(w);
    insert(widths, w);
    insert(heights, h);
    for(int i = 0; i < n; i += 1){
        string type;
        cin >> type;
        int coord;
        cin >> coord;
        if(type == "H") {
            //horizontal cut
            //find nearest cut to top and bottom
            auto ptr = cut_h.lower_bound(coord);
            int top = *ptr;
            ptr --;
            int bottom = *ptr;
            int segment_size = top - bottom;
            //cout << "CUT H : " << segment_size << "\n";
            erase(heights, segment_size);
            insert(heights, top - coord);
            insert(heights, coord - bottom);
            cut_h.insert(coord);
        }
        else {
            //vertical cut
            auto ptr = cut_v.lower_bound(coord);
            int top = *ptr;
            ptr --;
            int bottom = *ptr;
            int segment_size = top - bottom;
            //cout << "CUT V : " << segment_size << "\n";
            erase(widths, segment_size);
            insert(widths, top - coord);
            insert(widths, coord - bottom);
            cut_v.insert(coord);
        }
        ll largest_width = widths.rbegin() -> first;
        ll largest_height = heights.rbegin() -> first;
        cout << largest_width * largest_height << "\n";
    }
    
    return 0;
}
