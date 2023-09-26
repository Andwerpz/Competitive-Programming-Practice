#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - aplusb

//the idea is to model this using polynomial multiplication, and use fft to speed it up. 

//let's define a[i] as the number of occurrences of the number i in the input array. Then, in our
//polynomial, we'll set the coefficient of x^i to a[i]. Then, when we take the square of this polynomial, 
//we notice that the coefficient of some x^j is equal to the number of distinct pairs of values in the input
//array that add up to j. 

//now, the problem we have is that we are overcounting; polynomial multiplication doesn't ensure that we choose
//pairs with distinct indices. 

//one special case is the zeros in the original array; I found it easier to just set a[0] to 0, and manually
//count the triples formed using the zeroes. 

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1) {
        return;
    }

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
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
    
    ll a_zero = 50000;
    int n;
    cin >> n;
    vector<ll> a(50000 + 1 + 50000, 0);
    for(int i = 0; i < n; i++){
        ll next;
        cin >> next;
        a[next + a_zero] ++;
    }
    ll nr_zero = a[a_zero];
    a[a_zero] = 0;
    vector<ll> b = fft_multiply(a, a);
    ll b_zero = a_zero * 2;
    ll ans = 0;
    if(nr_zero >= 3){
        ans += nr_zero * (nr_zero - 1) * (nr_zero - 2);
    }
    for(int i = 0; i < b.size(); i++){
        ll val = i - b_zero;
        if(val < -50000 || val > 50000) {
            continue;
        }
        if(val == 0){
            ans += b[b_zero] * nr_zero;
            continue;
        }
        ll mul = a[val + a_zero];
        ans += b[i] * mul;
        //account for adding same number
        if(val % 2 == 0){
            ll cnt = a[(val / 2) + a_zero];
            ans -= cnt * mul;
        }
        //account for adding 0
        if(mul >= 1){
            ans += nr_zero * mul * (mul - 1) * 2;
        }
        // if(b[i] != 0){
        //     cout << val << " : " << b[i] << "\n";
        // }
    }
    cout << ans << "\n";
    
    return 0;
}
