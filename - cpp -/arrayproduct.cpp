
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1042C

//remember to double check which way you want to sort stuff.

//notice that you can at least make the product 0 in all situations. 

//If there are no zeroes in the array, look at the amount of negatives. If the amount of negatives is odd, then take away the negative with the least absolute value, and then
//combine all the values.

//If there are zeroes in the array, first, you can combine all the zeroes. Then, take a look at the negatives again. If the amount of negatives is odd, then combine the negative
//with the least absolute value with the remaining 0, and then remove it. Then, just combine all the rest of the numbers.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<pair<int, int>> positive;
    vector<pair<int, int>> negative;
    vector<int> zero;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        if(next == 0){
            zero.push_back(i + 1);
        }
        else if(next > 0){
            positive.push_back({next, i + 1});
        }
        else {
            negative.push_back({next, i + 1});
        }
    }
    sort(negative.begin(), negative.end(), [&](pair<int, int> a, pair<int, int> b) -> bool {return a.first < b.first;});
    sort(positive.begin(), positive.end(), [&](pair<int, int> a, pair<int, int> b) -> bool {return a.first < b.first;});
    int pointer = -1;
    if(zero.size() != 0){
        pointer = zero[zero.size() - 1];
        for(int i = 0; i < zero.size(); i++){
            if(i != zero.size() - 1){
                cout << "1 " << zero[i] << " " << zero[i + 1] << endl;
            }
        }
        if(positive.size() == 0 && negative.size() == 0){
            
        }
        else if(positive.size() == 0 && negative.size() == 1){
            cout << "2 " << negative[negative.size() - 1].second << endl;
        }
        else if(negative.size() % 2 == 1){
            cout << "1 " << pointer << " " << negative[negative.size() - 1].second << endl;
            cout << "2 " << negative[negative.size() - 1].second << endl;
        }
        else{
            cout << "2 " << pointer << endl;
        }
    }
    else{
        if(negative.size() % 2 == 1){
            cout << "2 " << negative[negative.size() - 1].second << endl;
        }
    }
    pointer = -1;
    for(int i = 0; i < positive.size(); i++){
        if(i == positive.size() - 1){
            pointer = positive[positive.size() - 1].second;
        }
        else{
            cout << "1 " << positive[i].second << " " << positive[i + 1].second << endl;
        }
    }
    if(pointer != -1 && negative.size() > 1){
        cout << "1 " << pointer << " " << negative[0].second << endl;
    }
    for(int i = 0; i < negative.size() - (negative.size() % 2); i++){
        if(i != negative.size() - (negative.size() % 2) - 1){
            cout << "1 " << negative[i].second << " " << negative[i + 1].second << endl;
        }
    }

    return 0;
}



