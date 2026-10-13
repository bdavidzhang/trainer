#include <bits/stdc++.h>
using namespace std;
// Faces of the rhombic triacontahedron <-> edges of an icosahedron.
// Vertices: 0 = bottom B, 1..5 = lower pentagon L0..L4, 6..10 = upper pentagon U0..U4, 11 = top T.
// Numbering read from the statement figures:
//  piece i (1..5)      : B  - L(i-1)
//  piece 6+j           : Lj - L(j+1)
//  piece 11+2j         : L(j+1) - Uj
//  piece 12+2j         : L(j+1) - U(j+1)
//  piece 21+j          : Uj - U(j+1)
//  piece 26+j          : T  - Uj
int main(){
    const double PI=acos(-1.0);
    double V[12][3];
    double h=1/sqrt(5.0),rr=2/sqrt(5.0);
    V[0][0]=0;V[0][1]=0;V[0][2]=-1;V[11][0]=0;V[11][1]=0;V[11][2]=1;
    for(int j=0;j<5;j++){
        double a=2*PI*j/5,b=2*PI*(j+0.5)/5;
        V[1+j][0]=rr*cos(a);V[1+j][1]=rr*sin(a);V[1+j][2]=-h;
        V[6+j][0]=rr*cos(b);V[6+j][1]=rr*sin(b);V[6+j][2]=h;
    }
    auto L=[](int j){return 1+((j%5)+5)%5;};
    auto U=[](int j){return 6+((j%5)+5)%5;};
    int ea[31],eb[31];
    for(int i=1;i<=5;i++){ea[i]=0;eb[i]=L(i-1);}
    for(int j=0;j<5;j++){
        ea[6+j]=L(j);eb[6+j]=L(j+1);
        ea[11+2*j]=L(j+1);eb[11+2*j]=U(j);
        ea[12+2*j]=L(j+1);eb[12+2*j]=U(j+1);
        ea[21+j]=U(j);eb[21+j]=U(j+1);
        ea[26+j]=11;eb[26+j]=U(j);
    }
    int eid[12][12];memset(eid,-1,sizeof eid);
    for(int i=1;i<=30;i++){eid[ea[i]][eb[i]]=eid[eb[i]][ea[i]]=i-1;}
    auto dot=[&](const double*a,const double*b){return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];};
    auto cross=[&](const double*a,const double*b,double*c){c[0]=a[1]*b[2]-a[2]*b[1];c[1]=a[2]*b[0]-a[0]*b[2];c[2]=a[0]*b[1]-a[1]*b[0];};
    // rotations: map the adjacent pair (B, L0) to any ordered adjacent pair (p,q)
    vector<array<int,30>> rots;
    double c0[3];cross(V[0],V[1],c0);
    for(int p=0;p<12;p++)for(int q=0;q<12;q++){
        if(p==q||eid[p][q]<0)continue;
        double c1[3];cross(V[p],V[q],c1);
        // x = a*V0 + b*V1 + c*c0  ->  a*Vp + b*Vq + c*c1 ; solve coordinates via dual basis
        int perm[12];bool ok=true;
        double d00=dot(V[0],V[0]),d01=dot(V[0],V[1]),d11=dot(V[1],V[1]),dcc=dot(c0,c0);
        double det=d00*d11-d01*d01;
        for(int v=0;v<12&&ok;v++){
            double x0=dot(V[v],V[0]),x1=dot(V[v],V[1]),xc=dot(V[v],c0);
            double a=(x0*d11-x1*d01)/det,b=(x1*d00-x0*d01)/det,c=xc/dcc;
            double w[3];for(int k=0;k<3;k++)w[k]=a*V[p][k]+b*V[q][k]+c*c1[k];
            int bi=-1;
            for(int u=0;u<12;u++){double dd=0;for(int k=0;k<3;k++)dd+=(w[k]-V[u][k])*(w[k]-V[u][k]);if(dd<1e-9)bi=u;}
            if(bi<0)ok=false;perm[v]=bi;
        }
        if(!ok)continue;
        array<int,30> e;
        for(int i=1;i<=30;i++)e[i-1]=eid[perm[ea[i]]][perm[eb[i]]];
        rots.push_back(e);
    }
    unsigned m[3];int tot=0;
    for(int s=0;s<3;s++){int k;scanf("%d",&k);tot+=k;m[s]=0;for(int i=0;i<k;i++){int x;scanf("%d",&x);m[s]|=1u<<(x-1);}}
    if(tot!=30){puts("No");return 0;}
    auto ap=[&](const array<int,30>&e,unsigned mk){unsigned r=0;for(int i=0;i<30;i++)if(mk>>i&1)r|=1u<<e[i];return r;};
    const unsigned FULL=(1u<<30)-1;
    vector<unsigned> a,b;
    for(auto&e:rots){a.push_back(ap(e,m[1]));b.push_back(ap(e,m[2]));}
    for(unsigned x:a){ if(x&m[0])continue; for(unsigned y:b) if((m[0]|x|y)==FULL){puts("Yes");return 0;} }
    puts("No");
}
