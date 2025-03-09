#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Topcoder - 7357

//pretty nice problem. 

//first, fix which beam is load bearing, and fix its horizontal position. Then, we want to move the center of
//mass as far to the left as possible. 

//for any beam above it, this means placing it such that the center of mass is exactly on the left edge of the
//load bearing beam. 

//for any beam below it, we consider them from top to bottom. Then, we just place each beam as far to the left
//as possible, with the center of mass of the rest of the beams above just barely on the right edge of 
//each bottom beam. 

class Overhang {
public:
    double hang(vector<int> beam, int LOAD) {
        ld ans = 0;
        int n = beam.size();
        vd L(n);
        for(int i = 0; i < n; i++) L[i] = beam[i];
        //fix some beam to hang the load off of
        for(int i = 0; i < n; i++){
            ld com = 0, mass = L[i];
            //add weight
            {
                ld ncom = L[i] / 2, nmass = LOAD;
                com = (com * mass + ncom * nmass) / (mass + nmass);
                mass += nmass;
            }
            //add beams on top
            for(int j = i + 1; j < n; j++){
                ld ncom = -L[i] / 2, nmass = L[j];
                com = (com * mass + ncom * nmass) / (mass + nmass);
                mass += nmass;
            }
            //add beams on bottom
            for(int j = i - 1; j >= 0; j--){
                ld ncom = com - (L[j] / 2), nmass = L[j];
                com = (com * mass + ncom * nmass) / (mass + nmass);
                mass += nmass;
            }
            ans = max(ans, -com + (L[i] / 2));
        }
        return (double) ans;
    }
};

int main() {
    int n0; cin >> n0;
    vector<int> arg0(n0);
    for (int i=0;i<n0;++i) { cin >> arg0[i]; }
    int arg1;
    cin >> arg1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = Overhang();
    double ret = c.hang(arg0, arg1);
    cout << setprecision(numeric_limits<double>::max_digits10) << ret;
}