#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,Q,E; scanf("%d %d %d",&n,&Q,&E);
    vector<vector<int>> adj(n,vector<int>(n,0));
    int cnt=0;
    while(cnt<E){
        int u,k; scanf("%d %d",&u,&k); u--;
        for(int i=0;i<k;i++){int v; scanf("%d",&v); v--; adj[u][v]=adj[v][u]=1; cnt++;}
    }
    for(int qi=0;qi<Q;qi++){
        int id,s,t; scanf("%d %d %d",&id,&s,&t); s--; t--;
        if(s==t){ printf("%.6f\n",0.0); continue; }
        // unknown voltages for all nodes except t (grounded); inject 1A at s
        vector<int> idx(n,-1); int m=0;
        for(int i=0;i<n;i++) if(i!=t) idx[i]=m++;
        vector<vector<double>> a(m,vector<double>(m+1,0));
        for(int i=0;i<n;i++) if(i!=t){
            int r=idx[i];
            for(int j=0;j<n;j++) if(adj[i][j]){
                a[r][r]+=1;
                if(j!=t) a[r][idx[j]]-=1;
            }
        }
        a[idx[s]][m]=1;
        vector<int> where(m,-1); int row=0;
        for(int col=0;col<m&&row<m;col++){
            int piv=row;
            for(int i=row;i<m;i++) if(fabs(a[i][col])>fabs(a[piv][col])) piv=i;
            if(fabs(a[piv][col])<1e-12) continue;
            swap(a[piv],a[row]);
            for(int i=0;i<m;i++) if(i!=row){
                double f=a[i][col]/a[row][col];
                if(f!=0) for(int j=col;j<=m;j++) a[i][j]-=f*a[row][j];
            }
            where[col]=row++;
        }
        double v=0; int w=where[idx[s]];
        if(w>=0) v=a[w][m]/a[w][idx[s]];
        printf("%.6f\n",v);
    }
}
