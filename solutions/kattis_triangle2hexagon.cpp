#include <bits/stdc++.h>
using namespace std;
typedef complex<double> P;
double cr(P a,P b){return imag(conj(a)*b);}
double dt(P a,P b){return real(conj(a)*b);}
P inter(P a,P b,P c,P d){return a+(b-a)*(cr(c-a,d-c)/cr(b-a,d-c));}
int main(){double bx,cx,cy;cin>>bx>>cx>>cy;P A(0,0),B(bx,0),Cc(cx,cy);
double a=abs(B-Cc),b=abs(A-Cc),c=abs(A-B);P I=(a*A+b*B+c*Cc)/(a+b+c);
// circumcenter
P ab=B-A,ac=Cc-A;double d=2*cr(ab,ac);
P O=A+P(ac.imag()*norm(ab)-ab.imag()*norm(ac),ab.real()*norm(ac)-ac.real()*norm(ab))/d;
auto sec=[&](P X){P dd=I-X;double t=-2*dt(X-O,dd)/dt(dd,dd);return X+t*dd;};
P M=sec(A),N=sec(B),Pp=sec(Cc);
P E=inter(N,Pp,A,B),F=inter(N,Pp,A,Cc),G=inter(M,N,A,Cc),H=inter(M,N,B,Cc),J=inter(M,Pp,B,Cc),K=inter(M,Pp,A,B);
printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",abs(E-F),abs(F-G),abs(G-H),abs(H-J),abs(J-K),abs(K-E));}
