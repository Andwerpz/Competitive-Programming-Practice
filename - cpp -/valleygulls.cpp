#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef long double ld;

//ICPC ECNA 2025 - L

//not too hard to see the solution, kinda tricky to implement

//first, the problem is kind of unclear as to what the rain is doing. The rain only falls between the cliffs
//marked out by the survey points, and it falls at a rate of R feet/hour, which means that if the land was
//perfectly flat, then the water depth would increase by R feet/hour

//the water is also implied to behave like water (duh) and flow downwards. This means that valleys will become
//full first, and if a valley fills up, then it will start overflowing into its adjacent valley, making the
//adjacent one fill up faster. 

//I treat valleys as 'ranges'. The key invariant on a range is:
// - the water level across a range needs to be flat

//in addition to the water level, I also keep the 'filling rate' of the range, which is the volume of water
//per hour that gets added to this range. 

//if a range gets full, then I try to merge it with one of its adjacent ranges. This can happen if an adjacent
//range is also full, and is 'facing towards' this range. The filling rates get added up.

//otherwise, this range will start 'pouring' water to some range, not necessarily adjacent. (the water you
//pour into an adjacent range can get poured into the next range over). This manifests as a donation of
//filling rate from the filled range to the range being filled. 

//at each step, I calculate the range that's closest to being filled, or the nest that's closest to being flooded,
//and jump the simulation to the closest one. Observe that between events, the behaviour of water is relatively
//easy to predict. 

struct vec2 {
    ld x, y;
};

struct range {
    int l, r;   //l and r are 'edges' of range, [l, r]
    ld fill_rate;
    ld wlevel;
    bool full;

    range() {}

    range(int _l, int _r, ld _fill_rate, ld _wlevel) {
        l = _l, r = _r;
        fill_rate = _fill_rate;
        wlevel = _wlevel;
        full = false;
    }
};

vector<vec2> a;
vector<range> b;

const int ETYPE_FILL = 0;
const int ETYPE_NEST = 1;
const ld epsilon = 1e-9;

ld lerp(ld x1, ld t1, ld x2, ld t2, ld t3) {
    ld v = (x2 - x1) / (t2 - t1);
    return x1 + v * (t3 - t1);
}

ld lerp(vec2 a, vec2 b, ld y) {
    return lerp(a.x, a.y, b.x, b.y, y);
}

ld calc_rftime(int ind, ld nlevel) {
    range cr = b[ind];
    if(nlevel <= cr.wlevel) return 0;
    vec2 l = a[cr.l];
    vec2 r = a[cr.r];
    ld ty = nlevel;
    ld wy = cr.wlevel;
    if(ty < wy) {
        cout << "BAD : " << ty << " " << wy << endl;
    }
    assert(ty >= wy);
    ld wlen = lerp(a[cr.r - 1], a[cr.r], wy) - lerp(a[cr.l], a[cr.l + 1], wy);
    ld tlen = lerp(a[cr.r - 1], a[cr.r], ty) - lerp(a[cr.l], a[cr.l + 1], ty);
    ld area = ((wlen + tlen) / 2.0) * (ty - wy);
    if(cr.fill_rate == 0) {
        if(area != 0) {
            // cout << "AREA : " << area << endl;
            // cout << l.x << " " << l.y << " " << r.x << " " << r.y << "\n";
            // cout << cr.l << " " << cr.r << endl;
            assert(false);
        }
    }
    ld dtime = 0;
    // cout << "FILL RATE : " << cr.fill_rate << " " << area << endl;
    if(cr.fill_rate != 0) dtime = (area / cr.fill_rate);
    return dtime;
}

void inc_wlevel(int ind, ld dtime) {
    //increment water level
    if(b[ind].full) return;
    //just binary search for the correct level lmao
    ld low = b[ind].wlevel;
    ld high = low + 1e6;
    while((high - low) > epsilon) {
        ld mid = low + (high - low) / 2.0;
        ld val = calc_rftime(ind, mid);
        if(val > dtime) high = mid;
        else low = mid;
    }
    b[ind].wlevel = low;
}   

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    ld R;
    cin >> n >> R >> m;
    a = vector<vec2>(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    // cout << "READ INPUT" << endl;
    sort(a.begin(), a.end(), [](vec2 a, vec2 b) -> bool {
        return a.x < b.x;
    });
    reverse(a.begin(), a.end());
    a.push_back({a[a.size() - 1].x, 1e5});
    reverse(a.begin(), a.end());
    a.push_back({a[a.size() - 1].x, 1e6});
    n += 2;
    vector<ld> nx(m);
    vector<ld> ny(m);
    for(int i = 0; i < m; i++) cin >> nx[i];
    sort(nx.begin(), nx.end());
    {
        int aptr = 0;
        for(int i = 0; i < m; i++) {
            while(a[aptr + 1].x < nx[i]) aptr ++;
            ny[i] = lerp(a[aptr].y, a[aptr].x, a[aptr + 1].y, a[aptr + 1].x, nx[i]);
        }
    }
    // cout << "INIT b" << endl;
    for(int i = 0; i < n - 1; i++) {
        if(a[i + 1].y < a[i].y) {
            assert(i != n - 2);
            if(a[i + 2].y > a[i + 1].y) {
                //dip
                b.push_back(range(i, i + 2, R * (a[i + 2].x - a[i].x), a[i + 1].y));
                i ++;
            }
            else {
                //slope
                b.push_back(range(i, i + 1, R * (a[i + 1].x - a[i].x), a[i + 1].y));
            }
        }
        else {
            assert(a[i + 1].y > a[i].y);
            //just a slope
            b.push_back(range(i, i + 1, R * (a[i + 1].x - a[i].x), a[i].y));
        }
    }
    //event loop
    // cout << "EVENT LOOP : " << endl;
    ld time = 0;
    vector<ld> ans(m, -1);
    int unansed = m;
    while(true) {
        int ev_type = -1;
        int ev_ind = -1;
        ld ev_dtime = 1e18;
        for(int i = 0; i < b.size(); i++) {
            range cr = b[i];
            if(cr.full) continue;
            vec2 l = a[cr.l];
            vec2 r = a[cr.r];
            ld dtime = calc_rftime(i, min(l.y, r.y));
            if(dtime < ev_dtime) {
                ev_dtime = dtime;
                ev_type = ETYPE_FILL;
                ev_ind = i;
            }
        }
        {
            int rptr = 0;
            for(int i = 0; i < m; i++) {
                if(ans[i] >= 0) continue;
                while(nx[i] > a[b[rptr].r].x) rptr ++;
                if(b[rptr].full) continue;
                ld dtime = calc_rftime(rptr, ny[i]);
                if(dtime < ev_dtime) {
                    ev_dtime = dtime;
                    ev_type = ETYPE_NEST;
                    ev_ind = i;
                }
            }
        }
        assert(ev_dtime != 1e18);
        time += ev_dtime;
        // cout << "EVENT : " << time << " " << ev_ind << " " << ev_type << "\n";
        //increment water level of all ranges
        for(int i = 0; i < b.size(); i++) {
            inc_wlevel(i, ev_dtime);
        }
        //special actions
        if(ev_type == ETYPE_FILL) {
            b[ev_ind].full = true;
            vec2 l = a[b[ev_ind].l];
            vec2 r = a[b[ev_ind].r];
            b[ev_ind].wlevel = min(l.y, r.y);
            // cout << "LR : " << b[ev_ind].l << " " << b[ev_ind].r << " " << l.y << " " << r.y << endl;
            if(l.y < r.y) {
                assert(ev_ind > 0);
                //check if we can merge to left
                int ptr = ev_ind - 1;
                if(b[ptr].full && a[b[ptr].r].y < a[b[ptr].l].y) {
                    //can merge
                    assert(b[ev_ind].wlevel == b[ptr].wlevel);
                    b[ev_ind].l = b[ptr].l;
                    b[ev_ind].fill_rate += b[ptr].fill_rate;
                    b[ev_ind].full = 0;
                    b.erase(b.begin() + ptr);
                }
                else {
                    //pouring to left
                    while(b[ptr].full && a[b[ptr].r].y > a[b[ptr].l].y) {
                        assert(ptr != 0);
                        ptr --;
                    }
                    b[ptr].fill_rate += b[ev_ind].fill_rate;
                    b[ev_ind].fill_rate = 0;
                }
            }
            else {
                assert(l.y > r.y);
                assert(ev_ind < b.size() - 1);
                //check if we can merge right
                int ptr = ev_ind + 1;
                if(b[ptr].full && a[b[ptr].r].y > a[b[ptr].l].y) {
                    //can merge
                    assert(b[ev_ind].wlevel == b[ptr].wlevel);
                    b[ev_ind].r = b[ptr].r;
                    b[ev_ind].fill_rate += b[ptr].fill_rate;
                    b[ev_ind].full = 0;
                    b.erase(b.begin() + ptr);
                }
                else {
                    //pouring to the right
                    while(b[ptr].full && a[b[ptr].r].y < a[b[ptr].l].y) {
                        assert(ptr != b.size() - 1);
                        ptr ++;
                    }
                    b[ptr].fill_rate += b[ev_ind].fill_rate;
                    b[ev_ind].fill_rate = 0;
                }
            }
        }
        else if(ev_type == ETYPE_NEST) {
            ans[ev_ind] = time;
            unansed --;
            if(!unansed) break;
        }   
        else assert(false);
    }
    for(int i = 0; i < ans.size(); i++) cout << fixed << setprecision(10) << ans[i] << "\n";

    return 0;
}