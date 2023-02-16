#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//NCNA 2018 Regional C

//consider the example number, 123.456 56 repeating. 

//lets try to represent 123.4 and 56 repeating as two seperate rational numbers, then add and simplify
//the fraction. 

//123.4 is simple, it's simply 1234 / 10. 

//56 repeating is a little harder. Consider that x = 56 repeating. 100x = 56.56 repeating, and
//99x = 56. Thus, x = 56 / 99. 

//from here, we just need to evaluate 1234 / 10 + 56 / 99, and simplify the fraction. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    int p;
    cin >> s >> p;
    ll d = 0;
    int ptr = 0;
    ll before = 0;
    bool flag = false;
    bool seenDecimal = false;
    ll decCnt = 0;
    for(int i = s.length() - 1; i >= 0; i--){
        if(s[i] == '.'){
            seenDecimal = true;
            continue;
        }
        if(flag) {
            before *= 10;
            before += (int) (s[i] - '0');
            if(!seenDecimal){
                decCnt ++;
            }
        }
        if(ptr < p){
            d *= 10.0;
            d += (int) (s[i] - '0');
            ptr ++;
            if(ptr == p){
                flag = true;
            }
        }
    }
    string sd = to_string(d), sbef = to_string(before);
    reverse(sd.begin(), sd.end());
    reverse(sbef.begin(), sbef.end());
    d = stoll(sd);
    before = stoll(sbef);
    ll denom = 0;
    for(int i = 0; i < p; i++){
        denom *= 10;
        denom += 9;
    }
    before *= denom;
    ll numerator = before + d;
    denom *= pow(10, decCnt);
    ll g = gcd(denom, numerator);
    denom /= g;
    numerator /= g;
    cout << numerator << "/" << denom << "\n";
    
    return 0;
}
