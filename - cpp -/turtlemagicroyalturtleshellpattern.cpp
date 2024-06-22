#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1933G

//i feel like this is kinda dumb problem, but editorial has nice proof for my observation, so maybe it isn't
//that dumb 

//the sample testcases for the problem have a pretty big hint; although intuitively one might think that there
//are many potential solutions, for a 5x5 grid there are only 8 solutions, and curiously that doesn't change
//for the 6x7 grid. 

//We might want to try to identify the solutions for the 5x5 grid. If you try to come up with it, you'll probably
//land on something like this:

//0 0 1 1 0
//1 1 0 0 1
//0 0 1 1 0
//1 1 0 0 1
//0 0 1 1 0

//since this solution can be inverted, and rotated 90 degrees to each give another unique solution, this is
//representative of all 8 solutions for the 5x5 grid. 

//so my solution is for each cookie they put, i'll just check that cookie to see if it's consistent against
//all 8 possible solutions. If it isn't consistent against one of them, then i'll just take that off the 
//list of possible solutions, and then just print out the number of remaining possible solutions. 

//so, how do we prove that this solution is correct? first, we can prove that for some 2x2 region that doesn't
//touch the edge of the grid, it has to have 2 0s and 2 1s exactly. We can prove this by casework:

//all zeroes:
//0 0 
//0 0 
//1 1 1   <-- required

//3 zeroes, 1 one:
//0 0 1
//0 1 ^
//1 <- required

//all other cases can be proven by rotation and inversion. 

//so therefore, any 2x2 region that isn't touching the edge must look something like this:

//0 0   0 1   1 0
//1 1   0 1   0 1   etc...

//ok, so if we start with this:
//0 0
//1 1

//and want to extend it horizontally, our only option is to do this:
//0 0 1 
//1 1 0

//likewise if we want to extend it vertically, and so we arrive at the conclusion that any valid answer must be
// a tesselation of the patterns we discovered above. 

//note that this doesn't work in the general case; there are 32 valid answers for a 3x3 grid. 

bool gen_tile(int r, int c, int opt) {
    if(opt & (1 << 0)) {
        swap(r, c);
    }
    if(opt & (1 << 1)) {
        r ++;
    }
    if(opt & (1 << 2)) {
        c ++;
    }
    bool res = r % 2;
    if(c & (1 << 1)) {
        res = !res;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, q;
        cin >> n >> m >> q;
        cout << "8\n";
        vector<bool> v(8, true);
        for(int i = 0; i < q; i++){
            int r, c;
            string shape;
            cin >> r >> c >> shape;
            bool s = shape == "circle";
            r --;
            c --;
            //go through each of 8 conditions
            for(int j = 0; j < 8; j++){
                if(s != gen_tile(r, c, j)){
                    v[j] = false;
                }
            }
            int ans = 0;
            for(int j = 0; j < 8; j++){
                ans += v[j];
            }
            cout << ans << "\n";
        }

        // for(int i = 0; i < 8; i++){
        //     for(int r = 0; r < n; r++){
        //         for(int c = 0; c < m; c++){
        //             cout << gen_tile(r, c, i) << " ";
        //         }
        //         cout << "\n";
        //     }
        //     cout << "\n";
        // }
    }
    
    return 0;
}