#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Meta Hacker Cup 2023 A

//since santa will always take the shortest path to visit all elves, we want to maximize the distance between the rightmost
//and leftmost group. 

//thus, we can just assign the two leftmost elves to the same toy, and the two rightmost elves to the same toy. 
//then, we assign the remaining elves all to one toy. 

//note that if the number of elves is 5, the number of remaining elves is 1, and a toy must have more than 1 elf. So, this remaining
//elf needs to be assigned to one of the outer groups. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::ifstream in("val.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    std::ofstream out("val_out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int caseno = 0;
    while(t--){
        caseno ++;
        int n;
        cin >> n;
        vector<ld> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        if(n == 5){
            ld ans = 0;
            {
                ld first = (a[0] + a[1]) / 2;
                ld last = (a[2] + a[4]) / 2;
                ans = max(ans, last - first);
            }
            {
                ld first = (a[0] + a[2]) / 2;
                ld last = (a[3] + a[4]) / 2;
                ans = max(ans, last - first);
            }
            cout << "Case #" << caseno << ": " << fixed << setprecision(10) << ans << "\n";
            continue;
        }
        ld first = (a[0] + a[1]) / 2;
        ld last = (a[a.size() - 1] + a[a.size() - 2]) / 2;
        ld ans = last - first;
        cout << "Case #" << caseno << ": " << fixed << setprecision(10) << ans << "\n";
    }
    
    return 0;
}
