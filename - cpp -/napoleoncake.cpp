
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//1501B - Napoleon Cake

//just go backwards. 

int main() {
    
    int t, n;
    
    cin >> t;
    
    while(t-- > 0){
        vector<int> ans;
        cin >> n;
        int pointer = 0;
        vector<int> nums;
        for(int i = 0; i < n; i++){
            int temp;
            cin >> temp;
            nums.push_back(temp);
        }
        for(int i = n - 1; i >= 0; i--){
            pointer = max(pointer, nums[i]);
            ans.push_back(pointer == 0? 0 : 1);
            pointer --;
        }
        for(int i = n - 1; i >= 0; i--){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

