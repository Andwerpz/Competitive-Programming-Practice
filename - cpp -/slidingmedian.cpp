
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1076 

//the idea is to maintain 2 sets of numbers, a set of numbers below and above the median. 

//when moving the window, you add a number to one of the sets, and you remove a number from one of the sets. 
//after doing so, you just need to re-equalize the sets, and find the new median. This can be done in constant time. 

void highToLow(map<int, int>& low, map<int, int>& high){  //moves lowest number from high to low
    auto highIter = high.begin();
    int key = highIter -> first;
    int val = highIter -> second;
    if(val == 1){
        high.erase(key);
    }
    else{
        highIter -> second --;
    }
    if(low.find(key) == low.end()){
        low.insert({key, 0});
    }
    low.find(key) -> second ++;
}

void lowToHigh(map<int, int>& low, map<int, int>& high){  //moves highest number of low to high
    auto lowIter = low.end();
    lowIter --;
    int key = lowIter -> first;
    int val = lowIter -> second;
    //cout << "MOVE : " << key << endl;
    if(val == 1){
        low.erase(key);
    }
    else{
        lowIter -> second --;
    }
    if(high.find(key) == high.end()){
        high.insert({key, 0});
    }
    high.find(key) -> second ++;
}

void r(map<int, int>& m, int key){
    auto iter = m.find(key);
    iter -> second --;
    if(iter -> second == 0){
        m.erase(key);
    }
}

void a(map<int, int>& m, int key){
    if(m.find(key) == m.end()){
        m.insert({key, 0});
    }
    auto iter = m.find(key);
    iter -> second ++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    map<int, int> low;
    map<int, int> high;
    for(int i = 0; i < k; i++){
        int next = nums[i];
        if(low.find(next) == low.end()){
            low.insert({next, 0});
        }
        auto iter = low.find(next);
        iter->second ++;
        //cout << next << " : " << iter -> second << endl;
    }
    for(int i = 0; i < k / 2; i++){
        lowToHigh(low, high);
    }
    auto iter = low.end();
    iter --;
    int prevMid = iter -> first;
    int lowSize = k - (k / 2);
    int highSize = k / 2;
    cout << prevMid << " ";
    for(int i = 1; i < n - k + 1; i++){
        int add = nums[i + k - 1];
        int remove = nums[i - 1];
        //cout << "ADD: " << add << " " << remove << endl;
        if(high.find(remove) != high.end()){
            r(high, remove);
            highSize --;
        }
        else{
            r(low, remove);
            lowSize --;
        }
        if(add > prevMid){
            a(high, add);
            highSize ++;
        }
        else{
            a(low, add);
            lowSize ++;
        }
        while(lowSize < highSize){
            highToLow(low, high);
            lowSize ++;
            highSize --;
        }
        while(lowSize > highSize + 1){
            lowToHigh(low, high);
            lowSize --;
            highSize ++;
        }
        //cout << "SIZE: " << lowSize << " " << highSize << endl;
        auto iter = low.end();
        iter --;
        prevMid = iter -> first;
        cout << prevMid << " ";
    }
    cout << endl;
    
    return 0;
}
