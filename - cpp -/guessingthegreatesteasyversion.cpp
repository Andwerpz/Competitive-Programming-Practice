
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1486C1

//ugh, interactive problem

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int low = 1;
    int high = n;
    int mid = low + (high - low) / 2;
    int prevSecondMax = 0;
    int counter = 1;
    cout << "? " << 1 << " " << n << endl;
    cout.flush();
    cin >> prevSecondMax;
    while(abs(high - low) + 1 >= 4){
        if(counter == 39){
            cout << "! " << 1 << endl;
            break;
        }
        counter += 2;
        int lowSecondMax, highSecondMax;
        cout << "? " << low << " " << mid << endl;
        cout.flush();
        cin >> lowSecondMax;
        cout << "? " << mid + 1 << " " << high << endl;
        cout.flush();
        cin >> highSecondMax;
        if(prevSecondMax <= mid){
            if(prevSecondMax == lowSecondMax){
                high = mid;
            }
            else{
                low = mid;
                prevSecondMax = highSecondMax;
            }
        }
        else{
            if(prevSecondMax == highSecondMax){
                low = mid;
            }
            else{
                high = mid;
                prevSecondMax = lowSecondMax;
            }
        }
    }
    if(counter != 39){
        int ans = 0;
        if(abs(high - low) + 1 == 2){
            cout << "? " << low << " " << high << endl;
            cout.flush();
            int secondMax;
            cin >> secondMax;
            if(secondMax == low){
                ans = high;
            }
            else{
                ans = low;
            }
        }
        else if(abs(high - low) + 1 == 3){
            set<int> dict;
            cout << "? " << low << " " << low + 1 << endl;
            cout.flush();
            int next;
            cin >> next;
            dict.insert(next);
            cout << "? " << low + 1 << " " << high << endl;
            cout.flush();
            cin >> next;
            dict.insert(next);
            for(int i = low; i <= high; i++){
                if(dict.find(i) == dict.end()){
                    ans = i;
                    break;
                }
            }
        }
        cout << "! " << ans << endl;
        cout.flush();

    }
    
    return 0;
}



