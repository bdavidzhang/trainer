#include <bits/stdc++.h>
using namespace std;
int main(){string s[2];long long ip[2],fi[2],fp[2];for(int i=0;i<2;i++){cin>>s[i];size_t d=s[i].find('.');ip[i]=stoll(s[i].substr(0,d));string f=s[i].substr(d+1);fi[i]=stoll(f);while(f.size()<5)f+='0';fp[i]=stoll(f);}
 auto cmp=[](long long a,long long b,long long c,long long d){if(a!=c)return a<c?-1:1;if(b!=d)return b<d?-1:1;return 0;};
 int t=cmp(ip[0],fi[0],ip[1],fi[1]),r=cmp(ip[0],fp[0],ip[1],fp[1]);
 if(t!=r)cout<<-1<<"\n";else cout<<(r>0?s[0]:s[1])<<"\n";}
