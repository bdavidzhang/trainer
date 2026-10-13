#include <bits/stdc++.h>
using namespace std;
int main(){int L,H;cin>>L>>H;int c=0;for(int v=L;v<=H;v++){int m=0,t=v;bool ok=true;while(t){int d=t%10;t/=10;if(d==0||(m>>d&1)||v%d){ok=false;break;}m|=1<<d;}if(ok)c++;}cout<<c<<endl;}
