#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 03 B

//for each person, if they arrive at time a, assign them the workstation of the person who left at time b, 
//where b is minimal and b <= a && a - b <= m. 

//process the people in ascending order of a. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    map<int, int> leave;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        int arrive, s;
        cin >> arrive >> s;
        a[i] = arrive;
        int lTime = s + arrive;
        if(leave.find(lTime) == leave.end()) {
            leave.insert({lTime, 0});
        }
        leave.find(lTime) -> second ++;
    }    
    int ans = 0;
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++){
        int next = a[i];
        auto ptr = leave.lower_bound(next - m);
        if(ptr == leave.end()) {
            continue;
        }
        int pLeave = ptr -> first;
        //cout << pLeave << " " <<  next << "\n";
        if(next - pLeave <= m && pLeave <= next) {
            ans ++;
            ptr -> second --;
            if(ptr -> second == 0){
                leave.erase(ptr -> first);
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
