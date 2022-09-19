#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1463D

//i noticed that if you find the minimum valid x, and maximum valid x, then every x between those are also valid. 
//note that this solution relies on this assumption, i didn't find a convincing proof for this. 

//To compute the minimum valid x, the idea is to pair off the numbers in b in increasing order. If you can find an available
//number not in b that is smaller than b[i], then you want to pair b[i] off to the minimum number that is not in b. Else, 
//pair b[i] off to the maximum number not in b, as to try to preserve the small numbers for the future bigger b[i]. 

//Computing the maximum valid x is very similar, instead of going in ascending order, you go in descending order, and
//you are trying to pair b[i] off to the maximum number not in b. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        set<int> b;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            next --;
            a[i] = next;
            b.insert(next);
        }
        sort(a.begin(), a.end());
        //find min x;
        int minX = 0;
        set<int> notB;
        for(int i = 0; i < 2 * n; i++){
            if(b.find(i) == b.end()){
                notB.insert(i);
            }
        }
        for(int i = 0; i < n; i++){
            int next = a[i];
            if(next > *notB.begin()) {
                notB.erase(*notB.begin());
            }
            else{
                notB.erase(*notB.rbegin());
                minX ++;
            }
        }
        //find max x;
        int maxX = n;
        for(int i = 0; i < 2 * n; i++){
            if(b.find(i) == b.end()){
                notB.insert(i);
            }
        }
        for(int i = n - 1; i >= 0; i--){
            int next = a[i];
            if(next < *notB.rbegin()){
                notB.erase(*notB.rbegin());
            }
            else{
                notB.erase(*notB.begin());
                maxX --;
            }
        }
        cout << (maxX - minX + 1) << "\n";
    }
    
    return 0;
}
