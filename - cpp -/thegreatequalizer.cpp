#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1862G

//the main observation is that the final value is equal to the maximum value in the array + the size of the maximum gap in the array. 

//why is this true? note that after every operation, the size of the maximum gap will always go down by 1. Also note that 
//an element that is not originally the maximum element will never 'overtake' the maximum element. So, we will perform exactly 
//x operations where x is equal to the size of the maximum gap in the original array, and we add 1 to the maximum element, y, every
//operation. So the final element in the array is equal to x + y. 

//now, we just have to keep track of the maximum value, and the size of the maximum gap after changing elements in the array. 

//we can do this using two multisets, one storing values in the array, and one storing all the gaps in the array. Whenever we 
//add the first occurrence, or remove the last occurrence of a value in the value set, we will update the gaps set. 

void insert(map<int, int>& m, int val) {
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m.find(val) -> second ++;
}

void erase(map<int, int>& m, int val) {
    m.find(val) -> second --;
    if(m.find(val) -> second == 0){
        //cout << "ERASED : " << val << "\n";
        m.erase(val);
    }
}

void insert(map<int, int>& vmap, map<int, int>& gmap, int val) {
    if(vmap.size() == 0 || vmap.find(val) != vmap.end()) {
        insert(vmap, val);
        return;
    }
    //what gap is this replacing?
    if(vmap.begin() -> first < val && val < vmap.rbegin() -> first) {
        auto i = vmap.lower_bound(val);
        int r = i -> first;
        i --;
        int l = i -> first;
        int gap = r - l;
        erase(gmap, gap);
    }
    //what gap is this introducing?
    if(val < vmap.rbegin() -> first) {
        auto i = vmap.lower_bound(val);
        int r = i -> first;
        int gap = r - val;
        insert(gmap, gap);
    }
    if(val > vmap.begin() -> first) {
        auto i = vmap.lower_bound(val);
        i --;
        int l = i -> first;
        int gap = val - l;
        insert(gmap, gap);
    }
    insert(vmap, val);
}

void erase(map<int, int>& vmap, map<int, int>& gmap, int val) {
    erase(vmap, val);
    if(vmap.find(val) != vmap.end() || vmap.size() == 0){
        return;
    }
    //what gaps is this removing?
    if(val < vmap.rbegin() -> first) {
        auto i = vmap.lower_bound(val);
        int r = i -> first;
        int gap = r - val;
        erase(gmap, gap);
    }
    if(val > vmap.begin() -> first) {
        auto i = vmap.lower_bound(val);
        i --;
        int l = i -> first;
        int gap = val - l;
        erase(gmap, gap);
    }
    //what gap is this introducing?
    if(vmap.begin() -> first < val && val < vmap.rbegin() -> first) {
        auto i = vmap.lower_bound(val);
        int r = i -> first;
        i --;
        int l = i -> first;
        int gap = r - l;
        insert(gmap, gap);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        map<int, int> gmap;    //occurrences of each sized gap
        map<int, int> vmap;
        for(int i = 0; i < n; i++){
            insert(vmap, gmap, a[i]);
        }
        int q;
        cin >> q;
        while(q--){
            int i, x;
            cin >> i >> x;
            i --;
            //erase(vmap, a[i]);
            erase(vmap, gmap, a[i]);
            a[i] = x;
            insert(vmap, gmap, x);

            // cout << "VMAP : " << "\n";
            // for(auto i = vmap.begin(); i != vmap.end(); i++){
            //     cout << i -> first << " : " << i -> second << "\n";
            // }
            // cout << "GMAP : " << "\n";
            // for(auto i = gmap.begin(); i != gmap.end(); i++){
            //     cout << i -> first << " : " << i -> second << "\n";
            // }
            // cout << endl;

            int gap = 0;
            if(gmap.size() != 0){
                gap = gmap.rbegin() -> first;
            }
            cout << (vmap.rbegin() -> first + gap) << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
