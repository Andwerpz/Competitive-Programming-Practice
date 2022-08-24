#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1707B

//just simulate it, but don't simulate the zeroes. 

//notice that if there are duplicate numbers in 'a', then on the next step they will all be removed
//and turned into zeroes. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(0);
        int nrZero = 0;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(next == 0){
                nrZero ++;
            }
            else{
                a.push_back(next);
            }
        }
        if(a.size() == 0){
            a.push_back(0);
        }
        while(a.size() > 1){
            //set<int> s;
            vector<int> next(0);
            if(nrZero != 0){
                nrZero --;
                next.push_back(a[0]);
                //s.insert(a[0]);
            }
            for(int i = 0; i < a.size() - 1; i++){
                if(a[i + 1] - a[i] == 0){
                    nrZero ++;
                }
                else{
                    next.push_back(a[i + 1] - a[i]);
                    //s.insert(a[i + 1] - a[i]);
                }
            }
            if(next.size() == 0){
                next.push_back(0);
            }
            sort(next.begin(), next.end());
            // for(int i : next){
            //     cout << i << " ";
            // }
            // cout << endl;
            a = next;
        }
        cout << a[0] << "\n";
    }
    
    return 0;
}
