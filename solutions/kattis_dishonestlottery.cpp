#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;int c[51]={0};for(int i=0;i<50*n;i++){int x;cin>>x;c[x]++;}
 bool any=false;for(int v=1;v<=50;v++)if(c[v]>2*n){if(any)cout<<' ';cout<<v;any=true;}
 if(!any)cout<<-1;cout<<endl;}
