#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 784A

//April Fools 2017

//first problem is usually just recognizing an integer sequence. In this case, it was joke numbers, or
//smith numbers. 

//composite numbers n such that sum of digits of n = sum of digits of prime factors of n

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a;
    cin >> a;
    vector<int> b = {4, 22, 27, 58, 85, 94, 121, 166, 202, 265, 274, 319, 346, 355, 378, 382, 391, 438, 454, 483, 517, 526, 535, 562, 576, 588, 627, 634, 636, 645, 648, 654, 663, 666, 690, 706, 728, 729, 762, 778, 825, 852, 861, 895, 913, 915, 922, 958, 985, 1086, 1111, 1165, 1219};
    cout << b[a - 1] << "\n";
    
    return 0;
}
