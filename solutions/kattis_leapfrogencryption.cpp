#include <bits/stdc++.h>
using namespace std;
int main(){string t,k;cin>>t>>k;string line,rest;getline(cin,rest);getline(cin,line);
string s;for(char ch:line)if(isalpha((unsigned char)ch))s+=tolower(ch);
int N=s.size();vector<int>perm(N,-1);int idx=0;
for(int p=0;p<=(int)k.size()&&idx<N;p++){int d=p<(int)k.size()?k[p]-'a'+2:1;int cnt=0;
 for(int q=0;q<N&&idx<N;q++){int pos=(p%2==0)?q:N-1-q;if(perm[pos]!=-1)continue;cnt++;if(cnt%d==0)perm[pos]=idx++;}}
string out(N,'?');
if(t=="E"){for(int i=0;i<N;i++)out[i]=s[perm[i]];}else{for(int i=0;i<N;i++)out[perm[i]]=s[i];}
cout<<out<<endl;}
