#include <bits/stdc++.h>
using namespace std;
static char buf[1<<25];size_t bl=0,bp=0;
inline int gc(){if(bp==bl){bl=fread(buf,1,sizeof(buf),stdin);bp=0;if(!bl)return -1;}return buf[bp++];}
inline int rd(){int c=gc();while(c!='-'&&(c<'0'||c>'9'))c=gc();int x=0;while(c>='0'&&c<='9'){x=x*10+c-'0';c=gc();}return x;}
const int MX=2003;
static int g[MX][MX];   // difference grid -> blocked
static int cnt[MX][MX]; // cnt[h][L]
int hgt[MX],stH[MX],stS[MX];
int main(){int X=rd(),Y=rd(),N=rd(),D=rd();
 for(int i=0;i<N;i++){int x=rd(),x2=rd(),y=rd(),y2=rd();g[x][y]++;g[x2][y]--;g[x][y2]--;g[x2][y2]++;}
 for(int x=0;x<=X;x++)for(int y=0;y<=Y;y++){int v=g[x][y];if(x)v+=g[x-1][y];if(y)v+=g[x][y-1];if(x&&y)v-=g[x-1][y-1];g[x][y]=v;}
 // rows indexed by y, columns by x. heights along y.
 // cnt[h][L] difference over h: runs of length L valid for heights in (lo,hi]
 for(int y=0;y<Y;y++){int top=0;
  for(int x=0;x<=X;x++){int h;
   if(x<X){if(g[x][y])hgt[x]=0;else hgt[x]++;h=hgt[x];}else h=0;
   int start=x;
   while(top&&stH[top-1]>=h){top--;int hh=stH[top],s=stS[top];int lo=max(h,top?stH[top-1]:0);
    if(hh>lo){int L=x-s;cnt[lo+1][L]++;cnt[hh+1][L]--;}
    start=s;}
   if(h>0){stH[top]=h;stS[top]=start;top++;}
  }}
 // prefix over h, then for each h: ans[h][w]=sum_{L>=w} c[L]*(L-w+1)
 for(int h=1;h<=Y;h++){for(int L=1;L<=X;L++)cnt[h][L]+=cnt[h-1][L];}
 for(int h=Y;h>=1;h--){ // overwrite in place; safe since prefix already done for all rows
  long long s1=0,s2=0;
  for(int L=X;L>=1;L--){s1+=cnt[h][L];s2+=s1;cnt[h][L]=(int)s2;}}
 string out;
 for(int i=0;i<D;i++){int w=rd(),h=rd();out+=to_string(cnt[h][w]);out+='\n';}
 fputs(out.c_str(),stdout);}
