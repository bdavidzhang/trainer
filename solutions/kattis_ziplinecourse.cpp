#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){
    int s,l; cin>>s>>l; vector<ld> X(s),Y(s); for(int i=0;i<s;i++) cin>>X[i]>>Y[i];
    vector<string> nm(l); vector<int> A(l),B(l); vector<ld> ha(l),hb(l);
    for(int i=0;i<l;i++){ cin>>nm[i]>>ha[i]>>hb[i]; A[i]=nm[i][0]-'A'; B[i]=nm[i][1]-'A'; }
    vector<int> adj(l,0); const ld EPS=1e-9;
    for(int i=0;i<l;i++) for(int j=i+1;j<l;j++){
        bool bad=false;
        bool same=(A[i]==A[j]&&B[i]==B[j]), rev=(A[i]==B[j]&&B[i]==A[j]);
        if(same||rev){
            ld d1=fabsl(ha[i]-(same?ha[j]:hb[j])), d2=fabsl(hb[i]-(same?hb[j]:ha[j]));
            ld s1=ha[i]-(same?ha[j]:hb[j]), s2=hb[i]-(same?hb[j]:ha[j]);
            ld mn=min(d1,d2); if((s1<0&&s2>0)||(s1>0&&s2<0)) mn=0;
            bad=mn<6-EPS;
        } else if(A[i]==A[j]||A[i]==B[j]||B[i]==A[j]||B[i]==B[j]){
            bad=false;
        } else {
            ld x1=X[A[i]],y1=Y[A[i]],x2=X[B[i]],y2=Y[B[i]],x3=X[A[j]],y3=Y[A[j]],x4=X[B[j]],y4=Y[B[j]];
            ld den=(x2-x1)*(y4-y3)-(y2-y1)*(x4-x3);
            if(fabsl(den)>1e-12){
                ld t=((x3-x1)*(y4-y3)-(y3-y1)*(x4-x3))/den;
                ld u=((x3-x1)*(y2-y1)-(y3-y1)*(x2-x1))/den;
                if(t>-1e-12&&t<1+1e-12&&u>-1e-12&&u<1+1e-12){
                    ld h1=ha[i]+t*(hb[i]-ha[i]), h2=ha[j]+u*(hb[j]-ha[j]);
                    bad=fabsl(h1-h2)<6-EPS;
                }
            }
        }
        if(bad){ cout<<nm[i]<<" "<<nm[j]<<" too close\n"; adj[i]|=1<<j; adj[j]|=1<<i; }
    }
    int best=0;
    vector<char> ok(1<<l,0); ok[0]=1;
    for(int m=1;m<(1<<l);m++){ int v=__builtin_ctz(m); int r=m&(m-1); if(ok[r]&&!(adj[v]&r)){ ok[m]=1; best=max(best,__builtin_popcount(m)); } }
    cout<<best<<" ziplines\n";
}
