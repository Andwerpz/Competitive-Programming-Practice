#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
 
using namespace std;

//1496A - Split It!

//notice that if the string is a palindrome, then you can easily partition it into many such k substrings. 

//also notice that the k + 1th substring isn't repeated and reversed. This means that you need to find k substrings from the contents on the edges of the string.

//just iterate through the string, keeping a left and right pointer. See how far you can go while the characters are still palindromic. If the number of palindromic
//characters exceeds or equals k, then the input is valid, else, the input is invalid.

//if k == 0, then the input is always valid, since the only string there is is k + 1.
 
int main()
{
    
    int t, n, k;
    cin >> t;
    while(t-- > 0){
        cin >> n >> k;
        string s;
        cin >> s;
        bool isValid = false;
        if(k == 0){
            isValid = true;
        }
        if(k * 2 + 1 <= n){
            int edgeAmt = 0;
            int l = 0;
            int r = n - 1;
            while(r - l >= 2 && s[l] == s[r]){
                edgeAmt ++;
                l ++;
                r --;
            }
            if(edgeAmt >= k){
                isValid = true;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}