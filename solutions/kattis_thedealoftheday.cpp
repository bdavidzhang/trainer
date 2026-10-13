#include <bits/stdc++.h>
using namespace std;

typedef unsigned __int128 u;
int main(){long long a[10];for(auto&x:a)cin>>x;int k;cin>>k;u e[11]={};e[0]=1;
for(int i=0;i<10;i++)for(int j=10;j>=1;j--)e[j]+=e[j-1]*(u)a[i];
u v=e[k];if(v==0){puts("0");return 0;}string s;while(v>0){s+=char('0'+(int)(v%10));v/=10;}reverse(s.begin(),s.end());cout<<s<<"\n";}
