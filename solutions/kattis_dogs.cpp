#include <bits/stdc++.h>
using namespace std;
typedef double D;
int main(){
    int n,m;
    scanf("%d",&n); vector<D> ax(n),ay(n); for(int i=0;i<n;i++) scanf("%lf %lf",&ax[i],&ay[i]);
    scanf("%d",&m); vector<D> bx(m),by(m); for(int i=0;i<m;i++) scanf("%lf %lf",&bx[i],&by[i]);
    int i=0,j=0; // currently on segment i->i+1, j->j+1
    D ua=0,ub=0; // distance travelled along current segment
    D best=hypot(ax[0]-bx[0],ay[0]-by[0]);
    while(i<n-1&&j<m-1){
        D la=hypot(ax[i+1]-ax[i],ay[i+1]-ay[i]), lb=hypot(bx[j+1]-bx[j],by[j+1]-by[j]);
        D dax=(ax[i+1]-ax[i])/la, day=(ay[i+1]-ay[i])/la;
        D dbx=(bx[j+1]-bx[j])/lb, dby=(by[j+1]-by[j])/lb;
        D ra=la-ua, rb=lb-ub;
        D dt=min(ra,rb);
        D px=ax[i]+dax*ua-(bx[j]+dbx*ub), py=ay[i]+day*ua-(by[j]+dby*ub);
        D vx=dax-dbx, vy=day-dby;
        D vv=vx*vx+vy*vy;
        D t=0;
        if(vv>1e-18){ t=-(px*vx+py*vy)/vv; if(t<0)t=0; if(t>dt)t=dt; }
        best=min(best,hypot(px+vx*t,py+vy*t));
        best=min(best,hypot(px+vx*dt,py+vy*dt));
        if(ra<=rb){ i++; ua=0; } else ua+=dt;
        if(rb<=ra){ j++; ub=0; } else ub+=dt;
    }
    printf("%.9f\n",best);
}
