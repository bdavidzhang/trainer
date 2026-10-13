#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct Ci{ld x,y,r,s;};
int main(){
    int n;scanf("%d",&n);
    vector<Ci> c(n);
    for(auto&q:c){double a,b,r,s;scanf("%lf %lf %lf %lf",&a,&b,&r,&s);q={a,b,r,s};}
    const ld EPS=1e-7L;
    while(c.size()>1){
        ld bt=1e30L;int bi=-1,bj=-1;
        for(size_t i=0;i<c.size();i++)for(size_t j=i+1;j<c.size();j++){
            ld d=hypotl(c[i].x-c[j].x,c[i].y-c[j].y);
            ld t=(d-c[i].r-c[j].r)/(c[i].s+c[j].s);
            if(t<0)t=0;
            if(t<bt){bt=t;bi=i;bj=j;}
        }
        for(auto&q:c)q.r+=q.s*bt;
        Ci nw;
        nw.x=(c[bi].x+c[bj].x)/2;nw.y=(c[bi].y+c[bj].y)/2;
        nw.r=sqrtl(c[bi].r*c[bi].r+c[bj].r*c[bj].r);nw.s=max(c[bi].s,c[bj].s);
        c.erase(c.begin()+bj);c.erase(c.begin()+bi);
        while(true){
            vector<int> hit;
            for(size_t k=0;k<c.size();k++){
                ld d=hypotl(c[k].x-nw.x,c[k].y-nw.y);
                if(d<=c[k].r+nw.r+EPS)hit.push_back(k);
            }
            if(hit.empty())break;
            ld sx=nw.x,sy=nw.y,ar=nw.r*nw.r,s=nw.s;
            for(int k:hit){sx+=c[k].x;sy+=c[k].y;ar+=c[k].r*c[k].r;s=max(s,c[k].s);}
            nw.x=sx/(hit.size()+1);nw.y=sy/(hit.size()+1);nw.r=sqrtl(ar);nw.s=s;
            for(int k=(int)hit.size()-1;k>=0;k--)c.erase(c.begin()+hit[k]);
        }
        c.push_back(nw);
    }
    printf("%.8Lf %.8Lf\n%.8Lf\n",c[0].x,c[0].y,c[0].r);
}
