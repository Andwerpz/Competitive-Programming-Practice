#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 02 F

//we can use two double ended queues to store the right and left side of the teque. 
//whenever an operation is done on the teque, we just need to rebalance it, so that each side
//stores exactly 1/2 of the teque. This is to facilitate the push_middle operation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    deque<int> l;
    deque<int> r;
    for(int i = 0; i < n; i++){
        string type;
        int val;
        cin >> type >> val;
        if(type == "push_back") {
            r.push_back(val);
        }
        else if(type == "push_front") {
            l.push_front(val);
        }
        else if(type == "push_middle") {
            l.push_back(val);
        }
        else if(type == "get") {
            if(val < l.size()) {
                cout << l[val] << "\n";
            }
            else {
                cout << r[val - l.size()] << "\n";
            }
        }
        //balance so that l.size() == floor((l.size() + r.size()) / 2)
        int tot = l.size() + r.size();
        while(l.size() > (tot + 1) / 2) {
            int val = l.back();
            l.pop_back();
            r.push_front(val);
        }
        while(l.size() < (tot + 1) / 2) {
            int val = r.front();
            r.pop_front();
            l.push_back(val);
        }
    }
    
    return 0;
}
