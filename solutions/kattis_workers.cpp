#include <bits/stdc++.h>
using namespace std;
int n;
// returns min cost, asg[row]=col
int hungarian(const vector<vector<int>>&a, vector<int>&asg){
    const int INF=1e9;
    vector<int> u(n+1),v(n+1),p(n+1),way(n+1);
    for(int i=1;i<=n;i++){
        p[0]=i;int j0=0; vector<int> minv(n+1,INF); vector<char> used(n+1,0);
        do{ used[j0]=1; int i0=p[j0],delta=INF,j1=0;
            for(int j=1;j<=n;j++)if(!used[j]){ int cur=a[i0-1][j-1]-u[i0]-v[j]; if(cur<minv[j]){minv[j]=cur;way[j]=j0;} if(minv[j]<delta){delta=minv[j];j1=j;} }
            for(int j=0;j<=n;j++) if(used[j]){u[p[j]]+=delta;v[j]-=delta;} else minv[j]-=delta;
            j0=j1;
        }while(p[j0]!=0);
        do{int j1=way[j0];p[j0]=p[j1];j0=j1;}while(j0);
    }
    asg.assign(n,0); for(int j=1;j<=n;j++)asg[p[j]-1]=j-1;
    return -v[0];
}
int main(){
    scanf("%d",&n);
    vector<vector<array<int,2>>> W(n,vector<array<int,2>>(n)),S=W;
    for(auto&r:W)for(auto&x:r)scanf("%d %d",&x[0],&x[1]);
    for(auto&r:S)for(auto&x:r)scanf("%d %d",&x[0],&x[1]);
    int best=INT_MAX,bk=0; vector<int> bw,bs;
    for(int k=0;k<=n;k++){ // gates 0..k-1 use A, rest B
        vector<vector<int>> a(n,vector<int>(n)),b=a;
        for(int i=0;i<n;i++)for(int g=0;g<n;g++){a[i][g]=W[i][g][g<k?0:1];b[i][g]=S[i][g][g<k?0:1];}
        vector<int> x,y; int c=hungarian(a,x)+hungarian(b,y);
        if(c<best){best=c;bk=k;bw=x;bs=y;}
    }
    vector<int> gs(n); for(int j=0;j<n;j++)gs[bs[j]]=j;
    printf("%d\n",best);
    for(int i=0;i<n;i++) printf("%d %d%c %d\n",i+1,bw[i]+1,bw[i]<bk?'A':'B',gs[bw[i]]+1);
}
