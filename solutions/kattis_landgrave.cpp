#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef __int128 LL;
struct P{ll x,y;int id;};
static LL cross(const P&a,const P&b,const P&c){return (LL)(b.x-a.x)*(c.y-a.y)-(LL)(b.y-a.y)*(c.x-a.x);}
int main(){
    int n; scanf("%d",&n);
    vector<P> p(n);
    for(int i=0;i<n;i++){scanf("%lld %lld",&p[i].x,&p[i].y);p[i].id=i+1;}
    sort(p.begin(),p.end(),[](const P&a,const P&b){return a.x<b.x||(a.x==b.x&&a.y<b.y);});
    vector<char> dead(n,0);
    while(true){
        vector<int> h; // indices into p, strict hull
        vector<int> alive; for(int i=0;i<n;i++) if(!dead[i]) alive.push_back(i);
        int m=alive.size();
        if(m<3){puts("impossible");return 0;}
        for(int pass=0;pass<2;pass++){
            size_t start=h.size();
            for(int t=0;t<m;t++){
                int i=pass?alive[m-1-t]:alive[t];
                while(h.size()>=start+2&&cross(p[h[h.size()-2]],p[h.back()],p[i])<=0) h.pop_back();
                h.push_back(i);
            }
            h.pop_back();
        }
        int k=h.size();
        if(k<3){puts("impossible");return 0;}
        bool any=false;
        for(int i=0;i<k;i++){
            const P&a=p[h[(i+k-1)%k]],&b=p[h[i]],&c=p[h[(i+1)%k]];
            LL dot=(LL)(a.x-b.x)*(c.x-b.x)+(LL)(a.y-b.y)*(c.y-b.y);
            if(dot>0){dead[h[i]]=1;any=true;}
        }
        if(!any){
            printf("%d\n",k);
            for(int i=0;i<k;i++) printf("%d%c",p[h[i]].id,i+1<k?' ':'\n');
            return 0;
        }
    }
}
