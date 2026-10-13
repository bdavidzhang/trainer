#include <bits/stdc++.h>
using namespace std;
int p,m; double r; vector<double> X,Y;
double segArea(int i,double h){ // segment i..i+1
    double w=X[i+1]-X[i], lo=min(Y[i],Y[i+1]), hi=max(Y[i],Y[i+1]);
    if(h<=lo) return 0;
    if(h>=hi) return (h-(lo+hi)/2)*w;
    double len=w*(h-lo)/(hi-lo);
    return 0.5*len*(h-lo);
}
struct Pool{int lo,hi; double vol; bool full; int dir;};
double V(const Pool&q,double h){ double s=0; for(int i=q.lo;i<q.hi;i++) s+=segArea(i,h); return s; }
int main(){
    scanf("%d %lf %d",&p,&r,&m); X.resize(p);Y.resize(p);
    for(int i=0;i<p;i++) scanf("%lf %lf",&X[i],&Y[i]);
    vector<double> nx(m),ny(m),ans(m,-1);
    for(int i=0;i<m;i++){ scanf("%lf",&nx[i]); for(int j=0;j+1<p;j++) if(nx[i]>X[j]&&nx[i]<X[j+1]) ny[i]=Y[j]+(Y[j+1]-Y[j])*(nx[i]-X[j])/(X[j+1]-X[j]); }
    vector<int> b; b.push_back(0);
    for(int i=1;i+1<p;i++) if(Y[i]>Y[i-1]&&Y[i]>Y[i+1]) b.push_back(i);
    b.push_back(p-1);
    vector<Pool> P;
    for(size_t i=0;i+1<b.size();i++) P.push_back({b[i],b[i+1],0.0,false,0});
    const double INF=1e18;
    auto HL=[&](const Pool&q){return q.lo==0?INF:Y[q.lo];};
    auto HR=[&](const Pool&q){return q.hi==p-1?INF:Y[q.hi];};
    double t=0; int left=m;
    while(left>0){
        int n=P.size();
        vector<double> base(n),rate(n,0);
        for(int i=0;i<n;i++) base[i]=r*(X[P[i].hi]-X[P[i].lo]);
        for(int i=0;i<n;i++){ int j=i; while(P[j].full) j+=P[j].dir; rate[j]+=base[i]; }
        double dt=INF; int ev=-1;
        for(int i=0;i<n;i++) if(!P[i].full){
            double H=min(HL(P[i]),HR(P[i])); if(H>=INF) continue;
            double d=(V(P[i],H)-P[i].vol)/rate[i]; if(d<0)d=0;
            if(d<dt){dt=d;ev=i;}
        }
        for(int i=0;i<n;i++) if(!P[i].full){
            for(int j=0;j<m;j++) if(ans[j]<0&&nx[j]>X[P[i].lo]&&nx[j]<X[P[i].hi]){
                double H=min(HL(P[i]),HR(P[i]));
                if(ny[j]>H) continue;
                double d=(V(P[i],ny[j])-P[i].vol)/rate[i]; if(d<0)d=0;
                if(d>dt*(1+1e-12)+1e-12) continue;
                ans[j]=t+d; left--;
            }
        }
        if(ev<0||left==0) break;
        for(int i=0;i<n;i++) if(!P[i].full) P[i].vol+=rate[i]*dt;
        t+=dt;
        double hl=HL(P[ev]),hr=HR(P[ev]); double H=min(hl,hr);
        int side=hl<hr?-1:1; int j=ev+side;
        if(P[j].full&&P[j].dir==-side){
            Pool q; q.lo=min(P[ev].lo,P[j].lo); q.hi=max(P[ev].hi,P[j].hi); q.full=false; q.dir=0; q.vol=V(q,H);
            int a=min(ev,j); P[a]=q; P.erase(P.begin()+a+1);
        } else { P[ev].vol=V(P[ev],H); P[ev].full=true; P[ev].dir=side; }
    }
    for(int i=0;i<m;i++) printf("%.8f\n",ans[i]);
}
