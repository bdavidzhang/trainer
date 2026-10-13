#include <bits/stdc++.h>
using namespace std;
int main(){
    int h,w; scanf("%d %d",&h,&w);
    int N=h*w;
    vector<int> a(N);
    for(auto&v:a) scanf("%d",&v);
    vector<vector<int>> nb(N);
    for(int i=0;i<h;i++)for(int j=0;j<w;j++){
        int c=i*w+j;
        if(i) nb[c].push_back(c-w);
        if(i+1<h) nb[c].push_back(c+w);
        if(j) nb[c].push_back(c-1);
        if(j+1<w) nb[c].push_back(c+1);
    }
    vector<int> mx(N,0);
    vector<int> head(N),nxt(N),dist(N),q(N);
    for(int dc=0;dc<N;dc++){
        int d=a[dc];
        fill(head.begin(),head.end(),-1);
        for(int c=0;c<N;c++) if(c!=dc){
            int best=-1,bd=INT_MAX,bc=INT_MAX;
            for(int o:nb[c]){
                int x=abs(a[o]-d),y=abs(a[o]-a[c]);
                if(x<bd||(x==bd&&y<bc)){bd=x;bc=y;best=o;}
            }
            nxt[c]=head[best];head[best]=c;
        }
        fill(dist.begin(),dist.end(),-1);
        int qh=0,qt=0;q[qt++]=dc;dist[dc]=0;
        while(qh<qt){int v=q[qh++];for(int c=head[v];c!=-1;c=nxt[c]){dist[c]=dist[v]+1;q[qt++]=c;}}
        for(int c=0;c<N;c++){
            if(dist[c]<0) mx[c]=INT_MAX;
            else if(mx[c]!=INT_MAX) mx[c]=max(mx[c],dist[c]);
        }
    }
    int bp=-1,bv=INT_MAX;
    for(int c=0;c<N;c++) if(mx[c]<bv||(mx[c]==bv&&bv!=INT_MAX&&a[c]<bp)){bv=mx[c];bp=a[c];}
    if(bv==INT_MAX) puts("impossible"); else printf("%d %d\n",bp,bv);
}
