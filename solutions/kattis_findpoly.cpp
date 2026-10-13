#include <bits/stdc++.h>
using namespace std;
int p[10000];int f(int x){return p[x]==x?x:p[x]=f(p[x]);}
int main(){string s,all;while(getline(cin,s))all+=s+" ";
 vector<int>v;for(size_t i=0;i<all.size();){if(isdigit((unsigned char)all[i])){int x=0;while(i<all.size()&&isdigit((unsigned char)all[i]))x=x*10+all[i++]-'0';v.push_back(x);}else i++;}
 for(int i=0;i<10000;i++)p[i]=i;
 vector<int>deg(10000,0);
 for(size_t i=0;i+3<v.size();i+=4){int a=v[i]*100+v[i+1],b=v[i+2]*100+v[i+3];deg[a]++;deg[b]++;p[f(a)]=f(b);}
 map<int,bool>ok;
 for(int i=0;i<10000;i++)if(deg[i]){int r=f(i);if(!ok.count(r))ok[r]=true;if(deg[i]!=2)ok[r]=false;}
 int c=0;for(auto&k:ok)c+=k.second;
 printf("%d %d\n",(int)ok.size(),c);}
