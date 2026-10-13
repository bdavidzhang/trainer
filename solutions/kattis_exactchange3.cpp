#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);string a,b;cin>>a>>b;
if(a.size()<b.size())a=string(b.size()-a.size(),'0')+a;
size_t L=b.size();long long pc=0;size_t i=0;
while(i<L&&a[i]==b[i]){pc+=a[i]=='1';i++;}
// a==b: popcount. else: prefix popcount + all coins 2^0..2^d where d is the top differing bit
if(i<L)pc+=(long long)(L-i);
printf("%lld\n",pc);}
