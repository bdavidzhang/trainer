#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,s,n; scanf("%d %d %d",&r,&s,&n);
    vector<int> a(r),b(s),c(n); for(auto&x:a)scanf("%d",&x); for(auto&x:b)scanf("%d",&x); for(auto&x:c)scanf("%d",&x);
    long long SA=0,SB=0; for(int x:a)SA+=x; for(int x:b)SB+=x;
    vector<vector<int>> PA(r,vector<int>(r)),PB(s,vector<int>(s));
    for(int i=0;i<r;i++){int t=0;for(int u=0;u<r;u++){PA[i][u]=t;t+=a[(i+u)%r];}}
    for(int i=0;i<s;i++){int t=0;for(int u=0;u<s;u++){PB[i][u]=t;t+=b[(i+u)%s];}}
    long long g=std::gcd(SA,SB); long long A=SA/g,B=SB/g; long long ia=0;
    for(long long i=0;i<B;i++) if(A*i%B==1%B){ia=i;break;}
    int W=SA+SB+1;
    vector<char> cur(r*s,0),nx; cur[0]=1;
    vector<char> ok(W);
    for(int t=0;t<n;t++){
        long long C=c[t];
        for(int w=0;w<W;w++){ long long V=C-w; ok[w]=0; if(V<0||V%g)continue; long long p0=(V/g)%B*ia%B; ok[w]=(p0*SA<=V); }
        nx.assign(r*s,0); bool any=false;
        for(int i=0;i<r;i++)for(int j=0;j<s;j++)if(cur[i*s+j]){
            for(int u=0;u<r;u++){ int wa=PA[i][u]; if(wa>C)break; int ni=(i+u)%r; const int*pb=PB[j].data();
                for(int v=0;v<s;v++){ if(ok[wa+pb[v]]){ nx[ni*s+(j+v)%s]=1; any=true; } } }
        }
        if(!any){puts("No");return 0;}
        cur.swap(nx);
    }
    puts("Yes");
}
