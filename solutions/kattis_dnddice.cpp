#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
struct B{u64 a[3]={0,0,0};
 void add(const B&o){unsigned __int128 c=0;for(int i=0;i<3;i++){c+=a[i];c+=o.a[i];a[i]=(u64)c;c>>=64;}}
 bool operator<(const B&o)const{for(int i=2;i>=0;i--)if(a[i]!=o.a[i])return a[i]<o.a[i];return false;}
};
int main(){int cnt[5],sd[5]={4,6,8,12,20};for(int i=0;i<5;i++)cin>>cnt[i];
 vector<B> f(1);f[0].a[0]=1;
 for(int t=0;t<5;t++)for(int r=0;r<cnt[t];r++){vector<B> g(f.size()+sd[t]);
  for(size_t i=0;i<f.size();i++)for(int k=1;k<=sd[t];k++)g[i+k].add(f[i]);f=g;}
 int nd=cnt[0]+cnt[1]+cnt[2]+cnt[3]+cnt[4];
 vector<int> id;for(int i=nd;i<(int)f.size();i++)id.push_back(i);
 stable_sort(id.begin(),id.end(),[&](int x,int y){return f[y]<f[x];});
 for(size_t i=0;i<id.size();i++)printf("%d%c",id[i],i+1<id.size()?' ':'\n');}
