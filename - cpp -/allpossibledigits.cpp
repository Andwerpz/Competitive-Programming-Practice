#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1759F

//largely an implementation problem. 
//codebandageforces

//lets say that the given number is a, and a[i] denotes the ith digit from the right; a[0] is the least significant digit, 
//and a[len(a) - 1] is the most significant. 

//if you write all numbers from a to a + p - 1 on the board, then it's guaranteed that you'll have written all the numbers in
//the base p digit system on the board, since the ones digit will have become each digit at one point. 

//notice that apart from the ones digit, all the other digits will only have 1 number different from when the ones digit flips back
//around to 0. 

//so we have two cases, the last digit missing is greater than a[0], and the last digit missing is less than a[0]. If the last digit missing is greater
//than a[0], then we just have to take the difference from a[0] to that digit. 

//if it's less than a[0], then gotta do some more casework D:

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, p;
        cin >> n >> p;
        int last = 0;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        last = a[n - 1];
        int lastNot9 = 0;
        for(int i = n - 2; i >= 0; i--){
            if(a[i] != p - 1) {
                lastNot9 = a[i];
                break;
            }
        }
        a.push_back(p);
        a.push_back(-1);
        sort(a.begin(), a.end());
        int missingB = -1;  //before last
        int missingA = -1;  //after last
        //check if there are any numbers under last that need filling
        //if there is, record the last number
        for(int i = 0; i < a.size() - 1; i++){
            //cout << a[i + 1] << " " << a[i] << endl;
            if(a[i + 1] - a[i] >= 2){
                //cout << "mis " << a[i + 1] << " " << a[i] << endl;
                missingA = a[i + 1] - 1;
                if(a[i + 1] <= last){
                    if(a[i + 1] - 1 == lastNot9 + 1 && a[i + 1] - 2 == a[i]) {
                        if(missingB == -1){
                            missingB = 0;
                        }
                        continue;
                    }
                    missingB = a[i + 1] - 1;
                }
            }
        }
        if(missingB == lastNot9 + 1) {
            missingB --;
        }
        //cout << missingB << " " << missingA << endl;
        int ans = 0;
        if(missingB != -1){
            ans = p - (last - missingB);
        }
        else if(missingA != -1){
            ans = missingA - last;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
