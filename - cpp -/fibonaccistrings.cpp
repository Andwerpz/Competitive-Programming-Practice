#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1718B

//first notice that if the sum of 'a' doesn't equal to the sum of a prefix of 'f', the fibonacci sequence, 
//then a cannot be a semi fibonacci string. 

//next, notice that the largest size of f given the input constraints is somewhere around 50, as in order to form a 
//fibonacci string, you must have a certain amount of equal consecutive characters, and f_50 is much larger than 10^9. 

//given that 'f' is the fibonacci sequence, then f_i - 1 = f_0 + f_1 + ... + f_(i - 2). (idk how it works, i just guessed)

//it boils down to just constructing the fibonacci sequence from greatest to least value, always picking the largest value
//from 'a' that hasn't been picked in the previous step. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n);
        ll sum = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
        }
        vector<ll> f(0);
        ll fSum = 0;
        while(fSum < sum){
            ll next = 0;
            if(f.size() <= 1){
                next = 1;
            }
            else {
                next = f[f.size() - 1] + f[f.size() - 2];
            }
            fSum += next;
            f.push_back(next);
        }
        if(fSum != sum){
            cout << "NO\n";
            continue;
        }
        int prevMax = -1;
        bool isValid = true;
        for(int i = f.size() - 1; i >= 0; i--){
            int max = 0;
            int maxIndex = -1;
            int next = f[i];
            for(int j = 0; j < n; j++){
                if(j != prevMax && a[j] >= next && a[j] > max){
                    max = a[j];
                    maxIndex = j;
                }
            }
            if(maxIndex == -1){
                isValid = false;
                break;
            }
            a[maxIndex] -= next;
            prevMax = maxIndex;
        }       
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
