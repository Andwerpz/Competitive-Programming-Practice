#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 474F

//For a given segment, lets say the cumulative gcd of all the elements in the segment is 'g'. 

//If and only if g % s_i == 0, then the ith ant goes free. 

//notice that g % s_i == 0 can only resolve to true if s_i is the minimum value over the segment. If 
//s_i wasn't the minimum, then there would always be at least 1 other element that s_i couldn't divide, since
//that element would be smaller than s_i. 

//So, we can just count the number of appearances of the min value in the segment. If the min divides g, then 
//they go free, else, nobody goes free. 

//to solve, we can save 3 seg trees, one for min, one for gcd, and one for cnt. The cnt seg tree will take only 
//n * log(n) memory in worst case, as there are only log(n) layers. 

int n;
vector<int> tMin(1e5 * 2);
vector<int> tGCD(1e5 * 2);
vector<map<int, int>> tCnt(1e5 * 2);

int gcd(int a, int b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void combineCnt(map<int, int>& a, map<int, int>& b, map<int, int>& dest){
    for(pair<int, int> i : a){
        if(dest.find(i.first) == dest.end()){
            dest.insert({i.first, i.second});
        }
        else{
            dest.find(i.first) -> second += i.second;
        }
    }
    for(pair<int, int> i : b){
        if(dest.find(i.first) == dest.end()){
            dest.insert({i.first, i.second});
        }
        else{
            dest.find(i.first) -> second += i.second;
        }
    }
}

int getGCD(int l, int r){
    int ans = 0;
    for(l += n, r += n, ans = tGCD[l]; l < r; l /= 2, r /= 2){
        if(l % 2 == 1) {ans = gcd(ans, tGCD[l++]);}
        if(r % 2 == 1) {ans = gcd(ans, tGCD[--r]);}
    }
    return ans;
}

int getMin(int l, int r){
    int ans = 0;
    for(l += n, r += n, ans = tMin[l]; l < r; l /= 2, r /= 2){
        if(l % 2 == 1) {ans = min(ans, tMin[l++]);}
        if(r % 2 == 1) {ans = min(ans, tMin[--r]);}
    }
    return ans;
}

int getCnt(int l, int r, int val){
    int ans = 0;
    for(l += n, r += n; l < r; l /= 2, r /= 2){
        if(l % 2 == 1) {ans += tCnt[l++].find(val) -> second;}
        if(r % 2 == 1) {ans += tCnt[--r].find(val) -> second;}
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        tMin[i + n] = next;
        tGCD[i + n] = next;
        tCnt[i + n].insert({next, 1});
    }
    //construct trees
    for(int i = n - 1; i > 0; i--){
        tMin[i] = min(tMin[i * 2], tMin[i * 2 + 1]);
        tGCD[i] = gcd(tGCD[i * 2], tGCD[i * 2 + 1]);
        combineCnt(tCnt[i * 2], tCnt[i * 2 + 1], tCnt[i]);
    }
    //process queries
    int t;
    cin >> t;
    while(t-- > 0){
        int l, r;
        cin >> l >> r;
        l --;
        //only min can be freed
        int min = getMin(l, r);
        int gcd = getGCD(l, r);
        int total = r - l;
        if(gcd % min == 0){
            cout << total - getCnt(l, r, min) << endl;
        }
        else{
            cout << total << endl;
        }
    }
    
    return 0;
}
