#include <bits/stdc++.h>
using namespace std;
int n,k,p,m;
vector<int> pre,cnt0,lastpos;
bool build(int c,vector<int>&seq){
    seq.assign(pre.begin(),pre.end());seq.resize(n);
    vector<int> rem(k+1);
    priority_queue<pair<int,int>> pq;
    for(int col=1;col<=k;col++){rem[col]=c-cnt0[col];
        bool blocked=lastpos[col]>=0&&lastpos[col]>m-p; // within positions m-p+1..m-1
        if(!blocked&&rem[col]>0)pq.push({rem[col],col});}
    for(int i=m;i<n;i++){
        if(i>m&&i-p>=0){int col=seq[i-p];if(rem[col]>0)pq.push({rem[col],col});}
        if(pq.empty())return false;
        int col=pq.top().second;pq.pop();rem[col]--;seq[i]=col;
    }
    return true;
}
int main(){
    scanf("%d %d %d %d",&n,&k,&p,&m);pre.resize(m);cnt0.assign(k+1,0);lastpos.assign(k+1,-1);
    bool ok=true;int mx=0;
    for(int i=0;i<m;i++){scanf("%d",&pre[i]);int c=pre[i];if(lastpos[c]>=0&&i-lastpos[c]<p)ok=false;lastpos[c]=i;mx=max(mx,++cnt0[c]);}
    vector<int> seq;
    if(!ok||!build(n,seq)){puts("impossible");return 0;}
    int lo=mx,hi=n;
    while(lo<hi){int mid=(lo+hi)/2;if(build(mid,seq))hi=mid;else lo=mid+1;}
    build(lo,seq);
    string out;for(int i=0;i<n;i++){out+=to_string(seq[i]);out+=i+1<n?' ':'\n';}
    fputs(out.c_str(),stdout);
}
