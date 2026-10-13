#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static vector<ll> A,H,O;int Lh;
void solve(int klo,int khi,int ilo,int ihi){ if(klo>khi)return;int mid=(klo+khi)/2;int a=max(ilo,mid-Lh),b=min(ihi,mid);ll bv=LLONG_MIN;int bi=a;
 for(int i=a;i<=b;i++){ll v=A[i]+H[mid-i];if(v>bv){bv=v;bi=i;}}
 O[mid]=bv;solve(klo,mid-1,ilo,bi);solve(mid+1,khi,bi,ihi);}
int main(){int n,k;scanf("%d %d",&n,&k);vector<char>ty(n);vector<int>val(n);for(int i=0;i<n;i++){char s[4];scanf("%s %d",s,&val[i]);ty[i]=s[0];}
 // dp[j] : vector over number of adds used c (0..adds so far)
 vector<vector<ll>> dp(1,vector<ll>(1,0));
 int i=0;
 while(i<n){
  if(ty[i]=='a'){vector<int>seg;while(i<n&&ty[i]=='a')seg.push_back(val[i++]);sort(seg.rbegin(),seg.rend());
   Lh=seg.size();H.assign(Lh+1,0);for(int t=0;t<Lh;t++)H[t+1]=H[t]+seg[t];
   for(auto&d:dp){A=d;int N=A.size();O.assign(N+Lh,0);solve(0,N+Lh-1,0,N-1);d=O;}
  }else{
   int m=val[i++];int J=dp.size();
   if(J<=k&&J<=40){dp.push_back(vector<ll>());}
   for(int j=(int)dp.size()-1;j>=1;j--){auto&src=dp[j-1];auto&dst=dp[j];if(dst.size()<src.size())dst.resize(src.size(),0);
    for(size_t c=0;c<src.size();c++)dst[c]=max(dst[c],src[c]*m);}
  }
 }
 vector<ll>best(n+2,0);
 for(size_t j=0;j<dp.size();j++)for(size_t c=0;c<dp[j].size();c++){size_t t=c+j;if(t<=(size_t)n)best[t]=max(best[t],dp[j][c]);}
 for(int s=1;s<=n;s++){best[s]=max(best[s],best[s-1]);printf("%lld\n",best[s]);}
}
