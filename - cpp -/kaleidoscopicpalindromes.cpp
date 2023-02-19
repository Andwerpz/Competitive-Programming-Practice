#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//NCNA 2018 Regional J

//brute force solution is enough. The probability of a number being a palindrome in multiple bases is very small, 
//so we can just keep track of what numbers are palindromes and remove the ones that aren't. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, k;
    cin >> a >> b >> k;
    set<int> p;
    for(int i = a; i <= b; i++){
        p.insert(i);
    }
    for(int i = 2; i <= k; i++){
        set<int> r;
        for(auto j = p.begin(); j != p.end(); j++){
            int next = *j;
            vector<int> d(0);
            while(next != 0){
                d.push_back(next % i);
                next /= i;
            }
            bool isValid = true;
            for(int k = 0; k < d.size() / 2; k++){
                if(d[k] != d[d.size() - k - 1]) {
                    isValid = false;
                    break;
                }
            }
            if(!isValid){
                r.insert(*j);
            }
        }
        for(auto j = r.begin(); j != r.end(); j++){
            p.erase(*j);
        }
    }
    cout << p.size() << "\n";
    
    return 0;
}
