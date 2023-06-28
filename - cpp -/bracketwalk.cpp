#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1838D

//note that if n is odd, then it is impossible for the bracket to be walkable regardless of the path you take. 

//convert all elements in S, '(' to 1 and ')' to -1. What we want on a valid bracket walk is to have the cumulative sum to 
//never be negative, and end on 0. 

//Maintain a set A that contains all i where S[i] != (i % 2 == 0? 1 : -1). note that S is 0 indexed. 
//in the case where A is empty, the bracket sequence will look like '()()()'. 

//if the lowest element in A is even, then the bracket sequence will look like: '())...'
//in this case, the array is never walkable, since you cannot get past the first 'wrong' element without the sum going negative. 

//if the largest element in A is odd, then the bracket sequence will look like: '...(()'
//in this case, the array isn't walkable, since once you get past the last 'wrong' element, your sum will never go to 0. 

//the array is walkable if A is empty, or (the lowest element is even, and the largest element is odd).

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    set<int> st;
    for(int i = 0; i < n; i++){
        if((i % 2 == 0) ^ (s[i] == '(')) {
            st.insert(i);
        }
    }
    while(q--) {
        int i;
        cin >> i;
        i --;
        if(st.find(i) == st.end()){
            st.insert(i);
        }
        else {
            st.erase(i);
        }
        if(n % 2 == 0 && (st.size() == 0 || (*st.begin() % 2 == 1 && *st.rbegin() % 2 == 0))) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
