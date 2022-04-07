
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1164

//sort the arrival and departure times in ascending order, when arrival and departure times have the same value, then the
//arrival time is lesser. 

//maintain a stack of empty rooms, and a map recording which room belongs to which person

//for each time, if it is arrival, then look for an empty room from the stack. If there is no room, then create a new
//room. 

//if departure, just get the room from the map and put it back into the stack.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> nums(n * 2); //time, person id, arriving? 0 : 1
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        nums[i] = vector<int> {a, i, 0};
        nums[i + n] = vector<int> {b, i, 1};
    }
    sort(nums.begin(), nums.end(), [](const vector<int>& a, const vector<int>& b){return a[0] == b[0]? a[2] < b[2] : a[0] < b[0];});
    map<int, int> m;
    stack<int> empty;
    vector<int> ans(n);

    for(int i = 0; i < nums.size(); i++){
        int nextPerson = nums[i][1];
        if(m.find(nextPerson) == m.end()){  //arrival of person
            int nextRoom = -1;
            if(empty.size() == 0){  //allocate new room
                nextRoom = (int) m.size() + 1;
            }
            else {  //get room from top of stack
                nextRoom = empty.top();
                empty.pop();
            }
            m[nextPerson] = nextRoom;
            ans[nextPerson] = nextRoom;
        }
        else{   //departure of person
            int room = m.find(nextPerson) -> second;
            m.erase(nextPerson);
            empty.push(room);
        }
    }
    cout << empty.size() << endl;
    for(int i : ans){
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
