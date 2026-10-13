#include <bits/stdc++.h>
using namespace std;
const int OFF=1000, W=2001, INF=1e9;
struct BB{
    int x1=INF,x2=-INF,y1=INF,y2=-INF;
    bool empty()const{return x1>x2;}
    void add(int x,int y){x1=min(x1,x);x2=max(x2,x);y1=min(y1,y);y2=max(y2,y);}
    void merge(const BB&o){x1=min(x1,o.x1);x2=max(x2,o.x2);y1=min(y1,o.y1);y2=max(y2,o.y2);}
    bool good()const{ // nonempty and does not contain the origin
        if(empty())return false;
        return !(x1<=0&&0<=x2&&y1<=0&&0<=y2);
    }
};
int n;
vector<int> PX,PY;
// transformed frame t: 0:(x,y) 1:(-x,y) 2:(y,x) 3:(-y,x)
static void tr(int t,int x,int y,int&X,int&Y){
    if(t==0){X=x;Y=y;}else if(t==1){X=-x;Y=y;}else if(t==2){X=y;Y=x;}else{X=-y;Y=x;}
}
static BB back(int t,const BB&b){
    BB r;
    if(t==0)r=b;
    else if(t==1){r.x1=-b.x2;r.x2=-b.x1;r.y1=b.y1;r.y2=b.y2;}
    else if(t==2){r.x1=b.y1;r.x2=b.y2;r.y1=b.x1;r.y2=b.x2;}
    else{r.x1=b.y1;r.x2=b.y2;r.y1=-b.x2;r.y2=-b.x1;}
    return r;
}
static void pr(int v10){
    if(v10<0){putchar('-');v10=-v10;}
    printf("%d.%d",v10/10,v10%10);
}
static void output(vector<BB> v){
    printf("%d\n",(int)v.size());
    for(auto&b:v){
        int a=b.x1*10-3,c=b.x2*10+3,d=b.y1*10-3,e=b.y2*10+3;
        int xs[4]={a,c,c,a},ys[4]={d,d,e,e};
        for(int i=0;i<4;i++){pr(xs[i]);putchar(' ');pr(ys[i]);putchar(i==3?'\n':' ');}
    }
}
int main(){
    scanf("%d",&n);PX.resize(n);PY.resize(n);
    BB all;
    for(int i=0;i<n;i++){scanf("%d %d",&PX[i],&PY[i]);all.add(PX[i],PY[i]);}
    if(all.good()){output({all});return 0;}
    vector<BB> best;
    // per frame data
    for(int pass=2;pass<=3&&best.empty();pass++){
        for(int t=0;t<4&&best.empty();t++){
            vector<BB> col(W),pre(W),suf(W+1);
            vector<vector<int>> colpts(W);
            for(int i=0;i<n;i++){int X,Y;tr(t,PX[i],PY[i],X,Y);col[X+OFF].add(X,Y);colpts[X+OFF].push_back(Y);}
            for(int c=0;c<W;c++){pre[c]=col[c];if(c)pre[c].merge(pre[c-1]);}
            for(int c=W-1;c>=0;c--){suf[c]=col[c];suf[c].merge(suf[c+1]);}
            if(pass==2){
                for(int c=0;c+1<W;c++)if(pre[c].good()&&suf[c+1].good()){
                    best={back(t,pre[c]),back(t,suf[c+1])};break;
                }
                continue;
            }
            vector<BB> row(W),rsuf(W+1);
            for(int c=0;c+1<W&&best.empty();c++){
                int cx=c-OFF;
                for(int y:colpts[c])row[y+OFF].add(cx,y);
                if(!suf[c+1].good())continue;
                if(pre[c].empty())continue;
                // (a) vertical sub-split
                BB mid;
                for(int c2=c-1;c2>=0;c2--){
                    mid.merge(col[c2+1]);
                    if(pre[c2].empty())break;
                    if(mid.good()&&pre[c2].good()){
                        best={back(t,suf[c+1]),back(t,mid),back(t,pre[c2])};break;
                    }
                }
                if(!best.empty())break;
                // (b) horizontal sub-split
                for(int d=W-1;d>=0;d--){rsuf[d]=row[d];rsuf[d].merge(rsuf[d+1]);}
                BB lo;
                for(int d=0;d+1<W;d++){
                    lo.merge(row[d]);
                    if(lo.good()&&rsuf[d+1].good()){
                        best={back(t,suf[c+1]),back(t,lo),back(t,rsuf[d+1])};break;
                    }
                }
            }
        }
    }
    if(best.empty()){
        BB g[4];
        for(int i=0;i<n;i++){
            int x=PX[i],y=PY[i];
            if(x>=1&&y>=0)g[0].add(x,y);
            else if(x<=0&&y>=1)g[1].add(x,y);
            else if(x<=-1&&y<=0)g[2].add(x,y);
            else g[3].add(x,y);
        }
        for(int i=0;i<4;i++)if(!g[i].empty())best.push_back(g[i]);
    }
    output(best);
}
