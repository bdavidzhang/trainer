#include <bits/stdc++.h>
using namespace std;
// Work on prefix xors p[0..n]: answer(u,v) = highest differing bit of p[u-1], p[v].
// Highest-differing-bit is an ultrametric, so insert points one at a time into the known
// structure, always comparing against the candidate farthest away in index (cheapest query).
static int H[105][105];
static int query(int i,int j){
    if(i>j) swap(i,j);
    printf("? %d %d\n",i+1,j); fflush(stdout);
    int r; if(scanf("%d",&r)!=1||r==-2) exit(0);
    return r;
}
int main(){
    int t; if(scanf("%d",&t)!=1) return 0;
    while(t--){
        int n; if(scanf("%d",&n)!=1||n==-2) return 0;
        vector<int> order; vector<bool> used(n+1,false);
        for(int g=128;g>=1;g/=2) for(int i=0;i<=n;i+=g) if(!used[i]){used[i]=true;order.push_back(i);}
        vector<int> ins;
        for(int x:order){
            H[x][x]=-1;
            vector<int> C=ins;
            while(!C.empty()){
                int r=C[0];
                for(int y:C) if(abs(y-x)>abs(r-x)) r=y;
                int b=query(x,r);
                vector<int> nc;
                for(int y:C){
                    if(H[r][y]!=b) H[x][y]=H[y][x]=max(b,H[r][y]);
                    else nc.push_back(y);
                }
                if(b==-1){ for(int y:nc) H[x][y]=H[y][x]=H[r][y]; nc.clear(); }
                C=nc;
            }
            ins.push_back(x);
        }
        puts("!");
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++) printf("%d ",H[i-1][j]);
            puts("");
        }
        fflush(stdout);
    }
}
