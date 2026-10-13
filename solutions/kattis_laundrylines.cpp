#include <bits/stdc++.h>
using namespace std;
typedef bitset<2048> BS;
int n;int w[16];
static BS reach_[1<<16];
bool ok(int D){
    BS A;for(int d=1000-D;d<=1000+D;d++)A[d]=1;
    int F=(1<<n)-1;
    for(int m=0;m<=F;m++)reach_[m].reset();
    reach_[0][1000]=1;
    for(int m=0;m<F;m++){
        if(reach_[m].none())continue;
        for(int i=0;i<n;i++)if(!(m>>i&1)){
            reach_[m|1<<i]|=((reach_[m]<<w[i])|(reach_[m]>>w[i]))&A;
        }
    }
    return reach_[F].any();
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&w[i]);
    int lo=0,hi=1000;
    while(lo<hi){int mid=(lo+hi)/2;if(ok(mid))hi=mid;else lo=mid+1;}
    printf("%d\n",lo);
}
