#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - figurinefigures

//classic FFT problem? i think so

//idk why this works lol, somehow polynomial multiplication can count the number of unique sets. 

using cd = complex<ld>;
const double PI = acos(-1);

int reverse(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
        if (num & (1 << i))
            res |= 1 << (lg_n - 1 - i);
    }
    return res;
}

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n)
        lg_n++;

    for (int i = 0; i < n; i++) {
        if (i < reverse(i, lg_n))
            swap(a[i], a[reverse(i, lg_n)]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        ld ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

//given two polynomials, returns the product. 
//if the two polynomials sizes arent same or powers of 2, this handles that. 
vector<ll> fft_multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(60001, 0);
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        a[next] ++;
    }
    vector<ll> b = fft_multiply(fft_multiply(a, a), fft_multiply(a, a));
    int min = -1;
    int max = -1;
    int cnt = 0;
    ld ev = 0;
    ld ev_cnt = 0;
    for(int i = 0; i < b.size(); i++){
        if(b[i] == 0){
            continue;
        }
        if(min == -1){
            min = i;
        }
        max = i;
        cnt ++;
        ev_cnt += (ld) b[i];
        ev += (ld) b[i] * (ld) i;
    }
    cout << max << " " << min << " " << cnt << " " << fixed << setprecision(10) << (ev / ev_cnt) << "\n";
    
    return 0;
}
