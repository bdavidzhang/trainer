#include <bits/stdc++.h>
using namespace std;
int n,m,k;
vector<int> pre, diff_, q;
vector<char> vis;
int W; // m+1
inline int rect(int i,int j,int s){ // top-left (i,j) 0-indexed, size s
    return pre[(i+s)*W+j+s]-pre[i*W+j+s]-pre[(i+s)*W+j]+pre[i*W+j];
}
bool ok(int s){
    int R=n-s+1,C=m-s+1;
    if(R<=0||C<=0)return false;
    int si=-1,sj=-1;
    for(int i=0;i<R&&si<0;i++)for(int j=0;j<C;j++) if(rect(i,j,s)==0){si=i;sj=j;break;}
    if(si<0)return false;
    fill(vis.begin(),vis.end(),0);
    fill(diff_.begin(),diff_.end(),0);
    int qh=0,qt=0;
    q[qt++]=si*m+sj; vis[si*m+sj]=1;
    static const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
    while(qh<qt){
        int c=q[qh++]; int i=c/m,j=c%m;
        diff_[i*W+j]++; diff_[(i+s)*W+j]--; diff_[i*W+j+s]--; diff_[(i+s)*W+j+s]++;
        for(int t=0;t<4;t++){
            int a=i+dx[t],b=j+dy[t];
            if(a<0||b<0||a>=R||b>=C||vis[a*m+b])continue;
            if(rect(a,b,s))continue;
            vis[a*m+b]=1; q[qt++]=a*m+b;
        }
    }
    long long cov=0;
    // 2D prefix of diff in place
    for(int i=0;i<n;i++){
        int run=0;
        for(int j=0;j<m;j++){
            run+=diff_[i*W+j];
            int v=run+(i?diff_[(i-1)*W+j]:0);
            diff_[i*W+j]=v;
            if(v>0)cov++;
        }
    }
    return cov==(long long)n*m-k;
}
int main(){
    scanf("%d %d %d",&n,&m,&k);
    W=m+1;
    pre.assign((size_t)(n+1)*W,0); diff_.assign((size_t)(n+1)*W,0); vis.assign((size_t)n*m,0); q.assign((size_t)n*m,0);
    for(int t=0;t<k;t++){int i,j;scanf("%d %d",&i,&j);pre[i*W+j]=1;}
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)pre[i*W+j]+=pre[(i-1)*W+j]+pre[i*W+j-1]-pre[(i-1)*W+j-1];
    int lo=0,hi=min(n,m);
    while(lo<hi){
        int mid=(lo+hi+1)/2;
        if(ok(mid))lo=mid;else hi=mid-1;
    }
    printf("%d\n",lo==0?-1:lo);
}
