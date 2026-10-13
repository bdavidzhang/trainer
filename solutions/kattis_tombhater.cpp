#include <bits/stdc++.h>
using namespace std;
int m,n,k;
int ch[2600][26];bool term[2600];int T=1;
char g[50][50];
int main(){
    scanf("%d %d %d",&m,&n,&k);
    for(int i=0;i<m;i++)for(int j=0;j<n;j++){char s[8];scanf("%s",s);g[i][j]=s[0];}
    memset(ch,-1,sizeof ch);
    for(int i=0;i<k;i++){char w[64];scanf("%s",w);int u=0;for(int j=0;w[j];j++){int c=w[j]-'A';if(ch[u][c]<0)ch[u][c]=T++;u=ch[u][c];}term[u]=true;}
    size_t S=(size_t)m*n*3*T;
    vector<unsigned short> dist(S,0xFFFF);
    vector<int> q;q.reserve(1<<20);
    auto id=[&](int r,int c,int d,int v){return (int)((((size_t)(r*n+c))*3+d)*T+v);};
    auto push=[&](int r,int c,int d,int v,int dd){int s=id(r,c,d,v);if(dist[s]==0xFFFF){dist[s]=dd;q.push_back(s);}};
    for(int j=0;j<n;j++){int v=ch[0][g[0][j]-'A'];if(v>=0)push(0,j,0,v,1);}
    for(size_t h=0;h<q.size();h++){
        int s=q[h];int v=s%T;int rest=s/T;int d=rest%3;int cell=rest/3;int r=cell/n,c=cell%n;int dd=dist[s];
        if(r==m-1&&term[v]){printf("%d\n",dd);return 0;}
        // moves: 0 south, 1 west, 2 east
        for(int mv=0;mv<3;mv++){
            if(mv==1&&d==2)continue;
            if(mv==2&&d==1)continue;
            int nr=r+(mv==0),nc=c+(mv==1?-1:mv==2?1:0);
            if(nr>=m||nc<0||nc>=n)continue;
            int L=g[nr][nc]-'A';
            int w=ch[v][L];if(w>=0)push(nr,nc,mv,w,dd+1);
            if(term[v]){w=ch[0][L];if(w>=0)push(nr,nc,mv,w,dd+1);}
        }
    }
    puts("impossible");
}
