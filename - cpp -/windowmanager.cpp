#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2015 - M

//just implementation, don't have to be too clever about it. 

ll sWidth, sHeight;
vector<vector<ll>> windows;    //xmin, ymin, xmax, ymax, open time
vector<pair<ll, string>> errors;
ll cmdCnt;
vector<ll> max_right;

vector<ll> get_intersecting(ll x_min, ll y_min, ll x_max, ll y_max, ll exclude = -1) {
    vector<ll> ans(0);
    for(ll i = 0; i < windows.size(); i++){
        if(i == exclude) {
            continue;
        }
        if(x_max < windows[i][0] || x_min > windows[i][2]) {
            continue;
        }
        if(y_max < windows[i][1] || y_min > windows[i][3]) {
            continue;
        }
        ans.push_back(i);
    }
    return ans;
}

void calc_max_right() {
    //sort the windows according to their right bound
    sort(windows.begin(), windows.end(), [](vector<ll>& a, vector<ll>& b) -> bool {
        return a[2] > b[2];
    });
    //go through, and calculate max_right
    max_right = vector<ll>(windows.size(), -1);
    for(int i = 0; i < windows.size(); i++){
        //cout << "MR I : " << i << " ";
        max_right[i] = sWidth - windows[i][2];
        //for all windows to the right, they will shrink max_right. 
        vector<ll> intersect = get_intersecting(windows[i][0], windows[i][1], sWidth, windows[i][3], i);
        for(int j = 0; j < intersect.size(); j++){
            ll x_min = windows[intersect[j]][0];
            x_min += max_right[intersect[j]];
            max_right[i] = min(max_right[i], x_min - windows[i][2] - 1);
            //cout << x_min << " ";
        }
        //cout << " : " << max_right[i] << "\n";
        //cout << "\n";
    }
    //cout << "\n";
}

void move_right(ll w, ll amt, bool root = true) {
    //cout << "MOVE :: " << w << " " << amt << "\n";
    if(amt > max_right[w]) {
        if(root) {
            errors.push_back({cmdCnt, "MOVE - moved " + to_string(max_right[w]) + " instead of " + to_string(amt)});
        }
        amt = max_right[w];
    }
    if(amt <= 0){
        return;
    }
    ll x_min = windows[w][0];
    ll y_min = windows[w][1];
    ll x_max = windows[w][2];
    ll y_max = windows[w][3];
    while(true) {
        vector<ll> intersect = get_intersecting(x_min, y_min, x_max + amt, y_max, w);
        bool noMove = true;
        vector<pair<ll, ll>> w_sort(intersect.size(), {0, 0});
        for(ll i = 0; i < w_sort.size(); i++){
            w_sort[i].first = intersect[i];
            w_sort[i].second = windows[intersect[i]][0];
        }
        sort(w_sort.begin(), w_sort.end(), [](pair<ll, ll>& a, pair<ll, ll>& b) -> bool {
            return a.second < b.second;
        });
        for(ll i = 0; i < w_sort.size(); i++){
            ll nextWindow = w_sort[i].first;
            ll x_dist = windows[nextWindow][0] - windows[w][2] - 1;
            //cout << "MOVE : " << w << " " << intersect[i] << " " << amt - x_dist << "\n";
            //cout << windows[intersect[i]][0] << " " << x_max << "\n";
            if(amt - x_dist <= 0){
                continue;
            }
            noMove = false;
            move_right(nextWindow, amt - x_dist, false);
        }
        if(noMove) {
            break;
        }
    }
    windows[w][0] += amt;
    windows[w][2] += amt;
    max_right[w] -= amt;
    //cout << "FINISH MOVING : " << w << " " << windows[w][0] << " " << windows[w][2] << "\n";
}

void rotate_CW() {
    for(ll i = 0; i < windows.size(); i++){
        ll n_h = windows[i][2] - windows[i][0] + 1;
        ll n_w = windows[i][3] - windows[i][1] + 1;
        ll n_xmin = sHeight - windows[i][3];
        ll n_ymin = windows[i][0];
        ll n_xmax = n_xmin + n_w - 1;
        ll n_ymax = n_ymin + n_h - 1;
        windows[i][0] = n_xmin;
        windows[i][1] = n_ymin;
        windows[i][2] = n_xmax;
        windows[i][3] = n_ymax;
    }
    swap(sWidth, sHeight);
}

ll find_window(ll cmd) {
    for(int i = 0; i < windows.size(); i++){
        if(windows[i][4] == cmd){
            return (ll) i;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> sWidth >> sHeight;
    sWidth --;
    sHeight --;
    windows = vector<vector<ll>>(0);
    string cmd;
    cin >> cmd;
    cmdCnt = 0;
    errors = vector<pair<ll, string>>(0);
    while(!cin.eof()) {
        cmdCnt ++;
        if(cmd == "STOP") {
            break;
        }
        if(cmd == "OPEN") {
            ll x, y, w, h;
            cin >> x >> y >> w >> h;
            ll x_min = x;
            ll x_max = x_min + w - 1;
            ll y_min = y;
            ll y_max = y_min + h - 1;
            if(x_max <= sWidth && y_max <= sHeight && (get_intersecting(x_min, y_min, x_max, y_max).size() == 0)) {
                windows.push_back({x_min, y_min, x_max, y_max, cmdCnt});
            }
            else {
                errors.push_back({cmdCnt, "OPEN - window does not fit"});
            }
        }
        else if(cmd == "CLOSE") {
            ll x, y;
            cin >> x >> y;
            vector<ll> w = get_intersecting(x, y, x, y);
            if(w.size() != 0){
                windows.erase(windows.begin() + w[0]);
            }
            else {
                errors.push_back({cmdCnt, "CLOSE - no window at given position"});
            }
        }
        else if(cmd == "RESIZE") {
            ll x, y, w, h;
            cin >> x >> y >> w >> h;
            vector<ll> window = get_intersecting(x, y, x, y);
            if(window.size() != 0){
                ll x_min = windows[window[0]][0];
                ll x_max = x_min + w - 1;
                ll y_min = windows[window[0]][1];
                ll y_max = y_min + h - 1;
                //cout << "RESIZED : " << x_min << " " << y_min << " " << x_max << " " << y_max << "\n";
                if(x_max <= sWidth && y_max <= sHeight && (get_intersecting(x_min, y_min, x_max, y_max, window[0]).size() == 0)){
                    windows[window[0]] = {x_min, y_min, x_max, y_max, windows[window[0]][4]};
                }
                else {
                    errors.push_back({cmdCnt, "RESIZE - window does not fit"});
                }
            }
            else {
                errors.push_back({cmdCnt, "RESIZE - no window at given position"});
            }
        }
        else if(cmd == "MOVE") {
            ll x, y, dx, dy;
            cin >> x >> y >> dx >> dy;
            vector<ll> w = get_intersecting(x, y, x, y);
            if(w.size() != 0){
                ll cmd = windows[w[0]][4];
                if(dx > 0) {
                    //moving to the right
                    calc_max_right();
                    move_right(find_window(cmd), abs(dx - dy));
                }
                else if(dx < 0){
                    //moving to the left
                    rotate_CW();
                    rotate_CW();
                    calc_max_right();
                    move_right(find_window(cmd), abs(dx - dy));
                    rotate_CW();
                    rotate_CW();
                }
                else if(dy > 0){
                    //moving down
                    rotate_CW();
                    rotate_CW();
                    rotate_CW();
                    calc_max_right();
                    move_right(find_window(cmd), abs(dx - dy));
                    rotate_CW();
                }
                else if(dy < 0){
                    //moving up
                    rotate_CW();
                    calc_max_right();
                    move_right(find_window(cmd), abs(dx - dy));
                    rotate_CW();
                    rotate_CW();
                    rotate_CW();
                }
            }
            else {
                errors.push_back({cmdCnt, "MOVE - no window at given position"});
            }
        }
        // cout << windows.size() << " window(s):" << "\n";
        // for(ll i = 0; i < windows.size(); i++){
        //     ll w = windows[i][2] - windows[i][0] + 1;
        //     ll h = windows[i][3] - windows[i][1] + 1;
        //     cout << windows[i][0] << " " << windows[i][1] << " " << w << " " << h << "\n";
        // }
        // cout << endl;
        cin >> cmd;
    }
    for(ll i = 0; i < errors.size(); i++){
        cout << "Command " << errors[i].first << ": " << errors[i].second << "\n";
    }
    sort(windows.begin(), windows.end(), [](vector<ll>& a, vector<ll>& b) -> bool {
        return a[4] < b[4];
    });
    cout << windows.size() << " window(s):" << "\n";
    for(ll i = 0; i < windows.size(); i++){
        ll w = windows[i][2] - windows[i][0] + 1;
        ll h = windows[i][3] - windows[i][1] + 1;
        cout << windows[i][0] << " " << windows[i][1] << " " << w << " " << h << "\n";
    }
    
    return 0;
}
