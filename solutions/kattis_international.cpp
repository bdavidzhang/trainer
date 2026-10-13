#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
template<class T> struct Ev{
    T px[3],py[3],hx[3],hy[3],d[3];
    // returns min over t of max_i(|t-c_i|-d_i); t in (tx,ty)
    T eval(T th,T&tx,T&ty)const{
        T cs=cos(th),sn=sin(th);
        T cx[3],cy[3];
        for(int i=0;i<3;i++){cx[i]=hx[i]-(cs*px[i]-sn*py[i]);cy[i]=hy[i]-(sn*px[i]+cs*py[i]);}
        T best=1e30;
        auto tryp=[&](T x,T y){
            T F=-1e30;
            for(int i=0;i<3;i++){T v=sqrt((x-cx[i])*(x-cx[i])+(y-cy[i])*(y-cy[i]))-d[i];if(v>F)F=v;}
            if(F<best){best=F;tx=x;ty=y;}
        };
        for(int i=0;i<3;i++)tryp(cx[i],cy[i]);
        for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){
            T dx=cx[j]-cx[i],dy=cy[j]-cy[i];T D=sqrt(dx*dx+dy*dy);
            if(D<=0)continue;
            T l=(D+d[i]-d[j])/2;if(l<0)l=0;if(l>D)l=D;
            tryp(cx[i]+dx*l/D,cy[i]+dy*l/D);
        }
        // three active
        T u2x=cx[1]-cx[0],u2y=cy[1]-cy[0],u3x=cx[2]-cx[0],u3y=cy[2]-cy[0];
        T det=u2x*u3y-u2y*u3x;
        T sc=sqrt((u2x*u2x+u2y*u2y)*(u3x*u3x+u3y*u3y));
        if(sc>0 && fabs(det)>1e-12*sc){
            T k2=(u2x*u2x+u2y*u2y-(d[1]-d[0])*(d[1]+d[0]))/2,k3=(u3x*u3x+u3y*u3y-(d[2]-d[0])*(d[2]+d[0]))/2;
            T e2=-(d[1]-d[0]),e3=-(d[2]-d[0]);
            // t.u2 = k2 + r e2 ; t.u3 = k3 + r e3
            T ax=(k2*u3y-k3*u2y)/det,ay=(u2x*k3-u3x*k2)/det;
            T bx=(e2*u3y-e3*u2y)/det,by=(u2x*e3-u3x*e2)/det;
            T qa=bx*bx+by*by-1,qb=2*(ax*bx+ay*by-d[0]),qc=ax*ax+ay*ay-d[0]*d[0];
            if(fabs(qa)<1e-14){
                if(fabs(qb)>0){T r=-qc/qb;tryp(cx[0]+ax+r*bx,cy[0]+ay+r*by);}
            }else{
                T disc=qb*qb-4*qa*qc;
                if(disc<0)disc=0;
                T sq=sqrt(disc);
                T q=-(qb+(qb>=0?sq:-sq))/2;
                T r1=q/qa;tryp(cx[0]+ax+r1*bx,cy[0]+ay+r1*by);
                if(q!=0){T r2=qc/q;tryp(cx[0]+ax+r2*bx,cy[0]+ay+r2*by);}
            }
        }
        return best;
    }
};
int main(){
    double P[3][3],Hh[3][3];
    for(int i=0;i<3;i++)scanf("%lf %lf %lf",&P[i][0],&P[i][1],&P[i][2]);
    for(int i=0;i<3;i++)scanf("%lf %lf %lf",&Hh[i][0],&Hh[i][1],&Hh[i][2]);
    const ld PI=acosl(-1.0L);
    ld bestG=1e30,bestTh=0,bestTx=0,bestTy=0;
    // centre the plug to reduce magnitudes
    ld gx=(P[0][0]+P[1][0]+P[2][0])/3,gy=(P[0][1]+P[1][1]+P[2][1])/3;
    for(int as=0;as<2;as++){
        int perm[3]={0,as?2:1,as?1:2};
        Ev<double> E;Ev<ld> EL;bool bad=false;
        ld maxP=0;
        for(int i=0;i<3;i++){
            EL.px[i]=P[i][0]-gx;EL.py[i]=P[i][1]-gy;
            EL.hx[i]=Hh[perm[i]][0];EL.hy[i]=Hh[perm[i]][1];
            EL.d[i]=Hh[perm[i]][2]-P[i][2];
            if(EL.d[i]<0)bad=true;
            E.px[i]=EL.px[i];E.py[i]=EL.py[i];E.hx[i]=EL.hx[i];E.hy[i]=EL.hy[i];E.d[i]=EL.d[i];
            maxP=max(maxP,sqrtl(EL.px[i]*EL.px[i]+EL.py[i]*EL.py[i]));
        }
        if(bad)continue;
        const int NS=40000;
        ld step=2*PI/NS;
        vector<double> g(NS);
        double tx,ty;
        for(int i=0;i<NS;i++)g[i]=E.eval((double)(i*step),tx,ty);
        ld bound=2*maxP*step*1.5+1e-3; // possible drop of g between samples
        int refined=0;
        // refine most promising local minima first
        vector<int> cand;
        for(int i=0;i<NS;i++){
            double a=g[(i+NS-1)%NS],b=g[(i+1)%NS];
            if(g[i]<=a&&g[i]<=b&&g[i]<=bound)cand.push_back(i);
        }
        sort(cand.begin(),cand.end(),[&](int x,int y){return g[x]<g[y];});
        for(int i:cand){
            if(refined>=3000)break;
            refined++;
            ld lo=(i-1)*step,hi=(i+1)*step;
            ld ltx,lty;
            for(int it=0;it<80;it++){
                ld m1=lo+(hi-lo)/3,m2=hi-(hi-lo)/3;
                ld v1=EL.eval(m1,ltx,lty),v2=EL.eval(m2,ltx,lty);
                if(v1<v2)hi=m2;else lo=m1;
            }
            ld th=(lo+hi)/2;
            ld v=EL.eval(th,ltx,lty);
            // also consider sample point itself
            ld ltx2,lty2;ld v2=EL.eval(i*step,ltx2,lty2);
            if(v2<v){v=v2;th=i*step;ltx=ltx2;lty=lty2;}
            if(v<bestG){
                bestG=v;bestTh=th;
                // translation in original coordinates: p' = R(p-g)+t
                bestTx=ltx;bestTy=lty;
            }
            if(bestG<=0)break;
        }
        if(bestG<=0)break;
    }
    if(bestG<=1.5e-6L){
        puts("YES");
        ld cs=cosl(bestTh),sn=sinl(bestTh);
        for(int i=0;i<3;i++){
            ld x=P[i][0]-gx,y=P[i][1]-gy;
            printf("%.10Lf %.10Lf\n",cs*x-sn*y+bestTx,sn*x+cs*y+bestTy);
        }
    }else puts("NO");
}
