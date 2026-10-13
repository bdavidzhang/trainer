#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static vector<string> split(const string&s){vector<string> r;string c;for(char ch:s){if(ch=='/'){r.push_back(c);c.clear();}else c+=ch;}r.push_back(c);return r;}
int main(){string s,d;getline(cin,s);getline(cin,d);
while(!s.empty()&&(s.back()=='\r'||s.back()==' '))s.pop_back();
while(!d.empty()&&(d.back()=='\r'||d.back()==' '))d.pop_back();
auto a=split(s),b=split(d);int p=a.size(),q=b.size(),m=min(p,q);
int L=0;while(L<m&&a[L]==b[L])L++;
int R=0;while(R<m&&a[p-1-R]==b[q-1-R])R++;
vector<ll> pa(p+1,0),pb(q+1,0);
for(int i=0;i<p;i++)pa[i+1]=pa[i]+a[i].size()+1;
for(int i=0;i<q;i++)pb[i+1]=pb[i]+b[i].size()+1;
ll best=LLONG_MAX;int bi=0,bj=0;
for(int i=0;i<=L;i++){int j=min(R,m-i);
 // A: first i comps with trailing slash; D: last j with leading slash
 ll len=pa[i]+(pa[p]-pa[p-j]);
 if(p-i-j>0)len+=pa[p-j]-pa[i]-1;
 if(q-i-j>0)len+=pb[q-j]-pb[i]-1;
 if(len<best){best=len;bi=i;bj=j;}}
string out;out.reserve(s.size()+d.size()+16);
for(int i=0;i<bi;i++){out+=a[i];out+='/';}
out+='{';
for(int i=bi;i<p-bj;i++){if(i>bi)out+='/';out+=a[i];}
out+=" => ";
for(int i=bi;i<q-bj;i++){if(i>bi)out+='/';out+=b[i];}
out+='}';
for(int i=p-bj;i<p;i++){out+='/';out+=a[i];}
puts(out.c_str());}
