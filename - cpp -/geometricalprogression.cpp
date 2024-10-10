#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 758F

//if n = 1, then there are exactly r - l + 1 progressions. 
//if n = 2, we can start at any number in [l, r], and the second number can be any other number in [l, r],
//leading to (r - l - 1) * (r - l - 2) progressions. 

//otherwise, we can write a general solution. 
//first, notice that if the first and last elements of a geometric sequence are within the range, all the
//other elements must be in the range as well. 

//second, we must be able to multiply by some rational number to get from the first to last number in any
//geometric sequence. And depending on the length of the sequence, n, the numerator and denominator of that
//number must be a perfect n-1th power. 

//third, the numerator and denominator of the aforementioned rational number must be <= r. 

//so, we can go ahead and generate all perfect n-1th powers under r, and then iterate through all possible
//rational numbers to get from the first to last element in the sequence. Note that some rational numbers
//we generate will be duplicates, so we can always just divide by gcd and use a set to check for those. 

//at this point, it's worth noting that I couldn't get this implementation to pass on C++20 64bit, due to MLE
//(and probably TLE too) but it passed on C++17 32bit, with 200ms margin, so not too good performance wise. 

//determining how many numbers in the range [l, r] can get multiplied by some rational number A / B back into
//the range [l, r] and remain an integer is an exercise left to the reader. 

//the editorial mentions some other optimizations that can be done. 

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, l, r;
    cin >> n >> l >> r;
    if(n == 1){
        cout << r - l + 1 << "\n";
        return 0;
    }
    else if(n == 2) {
        ll amt = r - l + 1;
        cout << amt * (amt - 1) << "\n";
        return 0;
    }
    //n >= 3
    vector<int> p(0);
    for(int i = 1; i <= 1e7; i++){
        bool cont = true;
        ll cur = 1;
        for(int j = 0; j < n - 1; j++){
            cur *= i;
            if(cur > r) {
                cont = false;
                break;
            }
        }
        if(!cont) {
            break;
        }
        p.push_back(cur);
    }
    ll ans = 0;
    set<pair<int, int>> v;
    for(int i = 0; i < p.size(); i++){
        for(int j = 0; j < p.size(); j++){
            int numer = p[i];
            int denom = p[j];
            int g = gcd(numer, denom);
            numer /= g;
            denom /= g;
            if((numer == 1 && denom == 1) || v.count({numer, denom})){
                continue;
            }
            v.insert({numer, denom});
            //compute the range of numbers after being divided by denom
            ll cl = (l + denom - 1) / denom;
            ll cr = r / denom;
            //compute range after multiplied by numer
            cl *= numer;
            cr *= numer;
            //add length of intersection to ans
            if(cl < l){
                ll diff = l - cl;
                ll mult = (diff + numer - 1) / numer;
                cl += mult * numer;
            }
            if(cr > r) {
                ll diff = cr - r;
                ll mult = (diff + numer - 1) / numer;
                cr -= mult * numer;
            }
            if(cl <= cr) {
                // cout << "ND : " << numer << "/" << denom << "\n";
                // cout << "clr : " << cl << " " << cr << "\n";
                ans += (cr - cl) / numer + 1;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
