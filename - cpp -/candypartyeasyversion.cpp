#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1868B1

//ok, today we learned that std::multiset is very bad, and very no good, and we should always just 
//use a custom implementation of multiset. 

//first, we can compute the average candies. If the sum of candies isn't divisible by the number of people, 
//then it's impossible to give everyone the average amount, and the answer is NO. 

//otherwise, each person needs to either increase, decrease, or keep the same amount of candies. In the case
//where one already has the average amount, they don't really matter for reasons i'll discuss later. 

//In the case where one needs to increase the amount of candies, they need to recieve more than they give away. 
//Let's denote 'D' as the amount of candies they need to gain. We want to construct D from 2 integers that are
//both powers of 2; D = 2^X - 2^Y, naturally, X > Y. I claim that if it is possible to construct D, then there
//is only 1 combination of X and Y to do so. 

//note that the case where one needs to decrease the amount of candies is very similar, just opposite. 

//we can tally up the total for each power of 2 that needs to be given, and needs to be taken, and see if all
//demands are met. Note that in this step, anyone who already has the average amount of candies can give and
//take any power of 2 they want, which means they don't add or take from the demand. 

//if all the demand is met, then the answer is YES. 

pair<ll, ll> construct(ll a) {
    ll high = 1;
    ll low = 1;
    bool pre = false;
    while(a != 0){
        if(a & 1) {
            pre = true;
        }
        if(pre) {
            if((a & 1) == 0) {
                return {-1, -1};
            }
        }
        else {
            low *= 2;
        }
        high *= 2;
        a /= 2;
    }
    return {high, low};
}

void insert(map<ll, ll>& m, ll val) {
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m[val] ++;
}

void erase(map<ll, ll>& m, ll val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        vector<ll> a(n);
        map<ll, ll> give;
        map<ll, ll> take;
        bool isValid = true;
        ll avg = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            avg += a[i];
        }
        if(avg % n != 0){
            //cout << "NOT DIVISIBLE\n";
            cout << "NO\n";
            continue;
        }
        avg /= n;
        for(int i = 0; i < n; i++){
            ll diff = abs(a[i] - avg);
            if(diff == 0){
                continue;
            }
            pair<ll, ll> c = construct(diff);
            if(c.first == -1){
                //cout << "ELEMENT NOT CONSTRUCTIBLE\n";
                isValid = false;
                break;
            }
            if(a[i] < avg) {
                swap(c.first, c.second);
            }
            //cout << "CONSTRUCT : " << diff << " " << c.first << " " << c.second << "\n";
            insert(give, c.first);
            insert(take, c.second);
        }
        for(auto i = give.begin(); i != give.end(); i++){
            ll val = i -> first;
            //cout << "VAL : " << val << "\n";
            if(take.find(val) == take.end() || give[val] != take[val]) {
                isValid = false;
                break;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
