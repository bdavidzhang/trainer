#include <bits/stdc++.h>
using namespace std;
// max wins of X against Y (both sorted): greedy two pointers
static int wins(const vector<int>&x,const vector<int>&y){int j=0,w=0;for(int v:x){if(j<(int)y.size()&&v>y[j]){w++;j++;}}return w;}
int main(){int n;cin>>n;vector<int>a(n);vector<char>has(2*n+1,0);for(int&x:a){cin>>x;has[x]=1;}vector<int>b;for(int i=1;i<=2*n;i++)if(!has[i])b.push_back(i);sort(a.begin(),a.end());
 cout<<n-wins(b,a)<<" "<<wins(a,b)<<"\n";}
