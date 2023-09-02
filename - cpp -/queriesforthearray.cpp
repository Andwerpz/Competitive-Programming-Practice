#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1861C

//we just need to check if the input contradicts itself. 

//there are two situations where it can contradict itself:
// - if we know the current array is sorted, and the input says the array is not sorted, that's a contradiction. 
// - if we know the current array is not sorted, and the input says the array is sorted, that's a contradiction. 

//we can keep track of the maximum known sorted prefix of the array, and the minimum known unsorted prefix 
//of the array. 

//If the current size of the array is equal to the maximum sorted prefix, then the array has to be sorted.
//If the current size of the array is greater than the minimum unsorted prefix, then the array has to be unsorted. 
//otherwise, we don't know the current status of the array. 

//note that the maximum sorted prefix cannot be larger than the size of the array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int curSize = 0;
        int sortedThreshold = 0;
        set<int> unsortedPos;
        bool isValid = true;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '+') {
                curSize ++;
                if(curSize == 1){
                    sortedThreshold = 1;
                }
            }
            else if(s[i] == '-'){
                if(unsortedPos.find(curSize) != unsortedPos.end()) {
                    unsortedPos.erase(curSize);
                }
                curSize --;
                if(curSize < sortedThreshold) {
                    sortedThreshold = curSize;
                }
            }
            else {
                bool isSorted = s[i] == '1';
                if(isSorted) {
                    if(unsortedPos.size() != 0){
                        isValid = false;
                        break;
                    }
                    sortedThreshold = curSize;
                }
                else {
                    if(sortedThreshold == curSize) {
                        isValid = false;
                        break;
                    }
                    unsortedPos.insert(curSize);
                }
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
