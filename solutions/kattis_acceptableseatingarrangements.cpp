#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,c; scanf("%d %d",&r,&c);
    int N=r*c;
    vector<int> lab(N+1),tg(N+1),pr(N+1),pc(N+1);
    for(int i=0;i<r;i++)for(int j=0;j<c;j++){int h;scanf("%d",&h);lab[h]=i;pr[h]=i;pc[h]=j;}
    for(int i=0;i<r;i++)for(int j=0;j<c;j++){int h;scanf("%d",&h);tg[h]=i;}
    vector<array<int,4>> ops;
    auto sw=[&](int a,int b){ // swap students of heights a,b (different rows, nobody of those rows strictly between)
        ops.push_back({pr[a]+1,pc[a]+1,pr[b]+1,pc[b]+1});
        swap(pr[a],pr[b]);swap(pc[a],pc[b]);swap(lab[a],lab[b]);
    };
    for(int p=1;p<=N;p++){
        if(lab[p]==tg[p])continue;
        int X=lab[p],Y=tg[p];
        int q=p+1; while(lab[q]!=Y)q++;
        int cur=q;
        for(int t=q-1;t>=p;t--) if(lab[t]==X){ sw(t,cur); cur=t; }
    }
    printf("%d\n",(int)ops.size());
    for(auto&o:ops)printf("%d %d %d %d\n",o[0],o[1],o[2],o[3]);
}
