#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;

//RMRC 2020 - H

//we can handle all the sensors and droplets in ascending order of y value. 
//all we need is some datastructure that allows us to perform the following actions:
// - add a segment [l, r)
// - remove a segment [l, r)
// - query a point x to find the most recent segment [l, r) such that l <= x < r

//we can implement such a datastructure using sqrt decomposition. 
//first we'll need to compress the coordinates, so that they're in range [0, N). 
//then we'll keep N + sqrt(N) stacks. 

//when adding a segment, we'll add it to up to 2 * sqrt(N) stacks. Then, when we query some x, 
//we just look at both the stack at x, and the stack of the bucket that contains x, and just take the 
//segment that is higher out of the two. 

//to handle removals, we'll just mark a segment as removed, and when we query some point, if the top segment
//is marked as removed, we'll just pop it and get the next highest segment. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int d, s;
    cin >> d >> s;
    vector<int> dx(d), dy(d), sl(s), sr(s), sy(s);
    for(int i = 0; i < d; i++) cin >> dx[i] >> dy[i];
    for(int i = 0; i < s; i++) cin >> sl[i] >> sr[i] >> sy[i];
    for(int i = 0; i < s; i++) sr[i] ++;
    int n;
    {
        set<int> st;
        for(int i = 0; i < d; i++) st.insert(dx[i]);
        for(int i = 0; i < s; i++) {
            st.insert(sl[i]);
            st.insert(sr[i]);
        }
        map<int, int> mp;
        n = 0;
        for(auto i = st.begin(); i != st.end(); i++) {
            mp[*i] = n ++;
        }
        for(int i = 0; i < d; i++) dx[i] = mp[dx[i]];
        for(int i = 0; i < s; i++) {
            sl[i] = mp[sl[i]];
            sr[i] = mp[sr[i]];
        }
    }
    int B = sqrt(100000);
    // int B = 2;
    int N = (n + B - 1) / B;
    vector<stack<int>> a(n), A(N);
    vector<array<int, 3>> ev(0);   //{y, ind, type}
    for(int i = 0; i < d; i++) ev.push_back({dy[i], i, 0});
    for(int i = 0; i < s; i++) ev.push_back({sy[i], i, 1});
    sort(ev.begin(), ev.end());
    vector<int> dtime(s, 1e9 + 100);
    vector<int> ans(d, -1);
    for(int i = 0; i < ev.size(); i++) {
        int y = ev[i][0];
        int ind = ev[i][1];
        int type = ev[i][2];
        // cout << "I : " << y << " " << ind << " " << type << endl;
        if(type == 0) { //droplet
            int x = dx[ind];
            int X = x / B;
            // cout << "X : " << x << endl;
            while(true) {
                int _y = -1, _Y = -1;
                if(a[x].size() != 0) {
                    _y = sy[a[x].top()];
                }
                if(A[X].size() != 0) {
                    _Y = sy[A[X].top()];
                }
                if(_y == -1 && _Y == -1) break;
                assert(_y != _Y);
                if(_y > _Y) {
                    int sind = a[x].top();
                    int cdtime = y - sy[sind];
                    assert(cdtime > 0);
                    if(dtime[sind] < cdtime) {
                        a[x].pop();
                        continue;
                    }
                    // cout << "SIND : " << dtime[sind] << " " << sind << " " << cdtime << endl;
                    assert(dtime[sind] == (1e9 + 100) || dtime[sind] == cdtime);
                    dtime[sind] = min(dtime[sind], cdtime);
                    ans[ind] = max(ans[ind], sy[sind]);
                    break;
                }
                else {
                    int sind = A[X].top();
                    int cdtime = y - sy[sind];
                    assert(cdtime > 0);
                    if(dtime[sind] < cdtime) {
                        A[X].pop();
                        continue;
                    }
                    assert(dtime[sind] == (1e9 + 100) || dtime[sind] == cdtime);
                    dtime[sind] = min(dtime[sind], cdtime);
                    // ans[ind] = min(ans[ind], cdtime);
                    ans[ind] = max(ans[ind], sy[sind]);
                    break;
                }
            }
            if(ans[ind] == -1) ans[ind] = 0;
            // cout << "ANS : " << ans[ind] << " " << ind << "\n";
        }
        else {  //segment
            int l = sl[ind], r = sr[ind];
            int L = ((l + B - 1) / B) * B;
            int R = (r / B) * B;
            // cout << "LR : " << l << " " << r << " " << L << " " << R << " " << B << endl;
            if(L <= R) {
                for(int i = l; i < L; i++) {
                    a[i].push(ind);
                }
                for(int i = r - 1; i >= R; i--) {
                    a[i].push(ind);
                }
                L /= B, R /= B;
                // cout << "LR : " << L << " " << R << endl;
                for(int i = L; i < R; i++) {
                    // cout << "I : " << i << endl;
                    A[i].push(ind);
                }
            }
            else {
                for(int i = l; i < r; i++) {
                    a[i].push(ind);
                }
            }
        }
    }
    for(int i = 0; i < d; i++) cout << ans[i] << "\n";
    // cout << "\n";

    return 0;
}