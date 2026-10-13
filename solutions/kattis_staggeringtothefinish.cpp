#include <bits/stdc++.h>
using namespace std;
int main(){
    int N; double R,S,W,F,L1,L2;
    scanf("%d %lf %lf %lf %lf %lf %lf",&N,&R,&S,&W,&F,&L1,&L2);
    const double PI=acos(-1.0);
    double D;
    while(scanf("%lf",&D)==1){
        printf("%.3f",D);
        for(int i=0;i<N;i++){
            double rin=R+i*W, r=rin+(i==0?L1:L2);
            double per=2*S+2*PI*r;
            double d=fmod(D,per);
            double x,y;
            double segs[5]={F+S/2,PI*r,S,PI*r,S};
            int k=0;
            while(k<4 && d>segs[k]){d-=segs[k];k++;}
            if(k==0){x=F-d;y=-rin;}
            else if(k==1){double th=1.5*PI-d/r;x=-S/2+rin*cos(th);y=rin*sin(th);}
            else if(k==2){x=-S/2+d;y=rin;}
            else if(k==3){double th=0.5*PI-d/r;x=S/2+rin*cos(th);y=rin*sin(th);}
            else {x=S/2-d;y=-rin;}
            printf(" %.4f %.4f",x,y);
        }
        printf("\n");
    }
}
