#include <bits/stdc++.h>

//Kattis - bracketnotation
//NAIPC 2016 - A

//code golf lmao
//this problem is mainly just implementation

//for some subarray of brackets, can write a function to compute its translated length given some starting index. 
//to compute some starting index, can reserve some characters for the header, and recurse on children. 
//observe that the length of the children will not require the header to grow too many times, as it requires
//another power of 10 increase in string length before that happens again.

//still need to do some heuristics to cut down on time:
// - start by reserving more characters for the header
// - keep a dp array

//at the end, once you have all the header lengths, you can easily print everything out in one pass. 

using namespace std;using z=pair<int,int>;int f(int x){int a=0;while(x)x/=10,a++;return a;}struct b{vector<b*>c;map<int, z>d;z S(int s){if(d.count(s))return d[s];int x=s+f(s)*2+2,p,t,i;for(;;){for(i=0,p=x;i<c.size();p=c[i++]->S(p).second);t=f(x)+f(p)+2;if(t==x-s)return d[s]={x,p};x=s+t;}}int w(int s){auto [x,e]=S(s);cout<<x<<","<<e<<":";for(int i=0;i<c.size();x=c[i++]->w(x));return x;}};int main(){string s;cin>>s;stack<b*>y;y.push(new b());for(int i=0;i<s.size();i++){if(s[i]=='(')y.push(new b());else{b* c=y.top();y.pop();y.top()->c.push_back(c);}}vector<b*>a=y.top()->c;for(int i=0,p=0;i<a.size();p=a[i++]->w(p));return 0;}