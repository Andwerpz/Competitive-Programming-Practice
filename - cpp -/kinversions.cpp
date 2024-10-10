#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - kinversions

//fft

const double PI = acos(-1);

void fft(vector<complex<double>> & a, bool invert) {
    int n = a.size();
    if (n == 1) {
        return;
    }

    vector<complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    complex<double> w(1), wn(cos(ang), sin(ang));
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
vector<int> fft_multiply(vector<int> const& a, vector<int> const& b) {
    vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
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

    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }
    return result;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n * 2, 0), b(n * 2, 0);
    for(int i = 0; i < n; i++) {
        a[i] = s[i] == 'A';
        b[n - i - 1] = s[i] == 'B';
    }
    vector<int> res = fft_multiply(a, b);
    for(int i = 0; i < n - 1; i++){
        cout << res[n + i] << "\n";
    }

    return 0;
}
