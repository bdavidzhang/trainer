#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct P{ld x,y;};
P operator-(P a,P b){return {a.x-b.x,a.y-b.y};}
P operator+(P a,P b){return {a.x+b.x,a.y+b.y};}
P operator*(P a,ld k){return {a.x*k,a.y*k};}
ld dot(P a,P b){return a.x*b.x+a.y*b.y;}
ld cross(P a,P b){return a.x*b.y-a.y*b.x;}
ld len(P a){return sqrtl(dot(a,a));}
ld L;
// point on ray from V away from X where the rope (hull of P,X,Y) has length L
P brk(P V,P X,P Y){
    P u=(V-X)*(1/len(V-X));
    ld K=L-len(V-X)-len(X-Y);
    ld c=len(Y-V);
    ld t=(K*K-c*c)/(2*(K-dot(u,Y-V)));
    return V+u*t;
}
// 1/2 * integral of cross(P,dP) along ccw elliptic arc from S to T; foci F1,F2, sum s
ld arc(P F1,P F2,ld s,P S,P T){
    const ld PI=acosl(-1.0L);
    P M=(F1+F2)*0.5L;
    ld d=len(F2-F1);
    P e1=(F2-F1)*(1/d); P e2={-e1.y,e1.x};
    ld a=s/2, b=sqrtl(max((ld)0,a*a-d*d/4));
    ld t1=atan2l(dot(S-M,e2)/b,dot(S-M,e1)/a);
    ld t2=atan2l(dot(T-M,e2)/b,dot(T-M,e1)/a);
    ld dt=t2-t1; while(dt<0) dt+=2*PI; while(dt>=2*PI) dt-=2*PI;
    return 0.5L*(cross(M,T-S)+a*b*dt);
}
int main(){
    int T; scanf("%d",&T);
    while(T--){
        int K; double bx,cx,cy,l; scanf("%d %lf %lf %lf %lf",&K,&bx,&cx,&cy,&l);
        L=l;
        P V[3]={{0,0},{(ld)bx,0},{(ld)cx,(ld)cy}};
        ld area=0;
        for(int i=0;i<3;i++){
            P A=V[i],B=V[(i+1)%3],C=V[(i+2)%3];
            // edge region across AB
            P q1=brk(A,C,B), q2=brk(B,C,A), q3=brk(B,A,C);
            area+=arc(A,B,L-len(B-C)-len(C-A),q1,q2);
            // vertex region at B
            area+=arc(A,C,L-len(A-C),q2,q3);
        }
        printf("%d %.6f\n",K,(double)area);
    }
}
