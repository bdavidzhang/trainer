#include <bits/stdc++.h>
using namespace std;
static char buf[1<<25];size_t bl=0,bp=0;
inline int gc(){if(bp==bl){bl=fread(buf,1,sizeof buf,stdin);bp=0;if(!bl)return -1;}return buf[bp++];}
inline int ri(){int c=gc();while(c!='-'&&(c<'0'||c>'9'))c=gc();int x=0;while(c>='0'&&c<='9'){x=x*10+c-'0';c=gc();}return x;}
int main(){int r=ri(),c=ri(),q=ri();
size_t W=c+2;vector<int> D((size_t)(r+2)*W,0);
vector<int> up(c+1,0),sh(c+2),ss(c+2);
for(int i=0;i<r;i++){int sp=0;
 for(int j=0;j<=c;j++){int cur=0;
  if(j<c){int ch=gc();while(ch!='.'&&ch!='#')ch=gc();up[j]=(ch=='.')?up[j]+1:0;cur=up[j];}
  int st=j;
  while(sp>0&&sh[sp-1]>=cur){int H=sh[sp-1],S=ss[sp-1];sp--;int L=j-S;int P=max(cur,sp>0?sh[sp-1]:0);
   if(H>P){D[(size_t)(P+1)*W+L]++;D[(size_t)(H+1)*W+L]--;}
   st=S;}
  if(cur>0){sh[sp]=cur;ss[sp]=st;sp++;}
 }}
// prefix over h, then double suffix over w
for(int h=1;h<=r;h++){int*a=&D[(size_t)h*W];int*b=&D[(size_t)(h-1)*W];for(int w=1;w<=c;w++)a[w]+=b[w];}
for(int h=1;h<=r;h++){int*a=&D[(size_t)h*W];long long s1=0,s2=0;for(int w=c;w>=1;w--){s1+=a[w];s2+=s1;a[w]=(int)s2;}}
string out;while(q--){int h=ri(),w=ri();out+=to_string(D[(size_t)h*W+w]);out+='\n';}
fwrite(out.data(),1,out.size(),stdout);}
