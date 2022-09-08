#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1728B

//notice that the maximum value of a given permutation of size n is 2n - 1. 

//this is due to the fact that we can only add to x, or the value, if x is less than an element 
//in the permutation. The maximum element in a permutation of size n is equal to n, and so if x = n - 1, 
//then the most we can do is add n to it. 

//The idea is to have the last two elements of the permutation be n - 1, and n, in that order. 

//The first n - 2 elements, then need to have a value of 0, as if the value after going through the
//first n - 2 elements is not 0, then we won't be able to add the nth element to x. 

//So in the case of n is even, we can arrange the permutation like so: 2, 1 4, 3, 6, 5, ... , n - 1, n. 
//we swap every two elements except for the last 2. This makes it so that x is incremented on even indices, and
//reset back to 0 on odd indicies, except for the last 2 indices, where they both increment. 

//for n is odd, we can do the same thing, but start from index 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            a[i] = i + 1;
        }
        for(int i = n % 2; i < n - 2; i += 2){
            int temp = a[i];
            a[i] = a[i + 1];
            a[i + 1] = temp;
        }
        for(int i : a){
            cout << i << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
