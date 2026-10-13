#include <bits/stdc++.h>
using namespace std;
typedef __int128 LL;
// f[a][b][state]: state 0 none,1 last A,2 last C,3 last B run1,4 last B run2
typedef vector<vector<array<LL,5>>> T;
T run(int L){T f(L+1,vector<array<LL,5>>(L+1));for(auto&r:f)for(auto&x:r)x.fill(0);f[0][0][0]=1;
 for(int p=0;p<L;p++){T g(L+1,vector<array<LL,5>>(L+1));for(auto&r:g)for(auto&x:r)x.fill(0);
  for(int a=0;a<=p;a++)for(int b=0;a+b<=p;b++)for(int s=0;s<5;s++){LL w=f[a][b][s];if(!w)continue;
   if(s!=1)g[a+1][b][1]+=w; if(s!=2)g[a][b][2]+=w; if(s<3)g[a][b+1][3]+=w; else if(s==3)g[a][b+1][4]+=w;}
  f=g;}
 return f;}
void pr(LL x){if(x==0){puts("0");return;}string s;while(x>0){s+=char('0'+(int)(x%10));x/=10;}reverse(s.begin(),s.end());puts(s.c_str());}
int main(){int w,d;cin>>w>>d;
 auto ok=[&](int a,int b,int c){return abs(a-b)<=d&&abs(a-c)<=d&&abs(b-c)<=d;};
 LL tot=0;{T f=run(w);for(int a=0;a<=w;a++)for(int b=0;a+b<=w;b++)if(ok(a,b,w-a-b))for(int s=0;s<5;s++)tot+=f[a][b][s];}
 LL pal=0;int h=w/2;T f=run(h);
 for(int a=0;a<=h;a++)for(int b=0;a+b<=h;b++){int c=h-a-b;
  if(w%2==0){if(ok(2*a,2*b,2*c))pal+=f[a][b][3];}
  else{ // middle A, C, B
   if(ok(2*a+1,2*b,2*c))for(int s=0;s<5;s++)if(s!=1)pal+=f[a][b][s];
   if(ok(2*a,2*b,2*c+1))for(int s=0;s<5;s++)if(s!=2)pal+=f[a][b][s];
   if(ok(2*a,2*b+1,2*c))for(int s=0;s<3;s++)pal+=f[a][b][s];}}
 pr(tot-pal);}
