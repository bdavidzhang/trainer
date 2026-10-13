#include <bits/stdc++.h>
using namespace std;
// x=f^n(1) lies on a cycle. Find its length L by baby-step/giant-step (~2*sqrt(n) queries),
// then c=x and r=f^{(-c) mod L}(c) gives f^c(r)=c.
#ifdef LOCAL
static vector<int> F; static int NQ=0;
int ask(int c,int r){NQ++; for(int i=0;i<c;i++) r=F[r]; return r;}
#else
int ask(int c,int r){printf("? %d %d\n",c,r);fflush(stdout);int h;if(scanf("%d",&h)!=1)exit(0);return h;}
#endif
pair<int,int> solve(int n){
    int x=ask(n,1);
    int B=450; int L=-1;
    vector<int> baby(n+1,-1); baby[x]=0;
    int lim=min(B-1,n);
    for(int i=1;i<=lim;i++){ int v=ask(i,x); if(v==x){L=i;break;} baby[v]=i; }
    if(L<0){ // L >= B, baby[] holds f^i(x) for i=0..B-1 (all distinct)
        for(int m=n;m>=B;m-=B){ int v=ask(m,x); if(baby[v]>=0){ int d=m-baby[v]; if(d>0&&(L<0||d<L)) L=d; } }
    }
    int c=x; int m=((-(long long)c)%L+L)%L; if(m==0) m=L;
    int r=ask(m,c);
    return {c,r};
}
int main(int argc,char**argv){
#ifdef LOCAL
    mt19937 rng(atoi(argv[1])); int worst=0;
    for(int it=0;it<400;it++){
        int n; int mode=rng()%6;
        if(mode==0) n=1+rng()%8; else if(mode==1) n=1+rng()%2000; else n=200000-rng()%3;
        F.assign(n+1,0);
        int t=rng()%4;
        if(t==0) for(int i=1;i<=n;i++) F[i]=1+rng()%n;
        else if(t==1){ vector<int> p(n); iota(p.begin(),p.end(),1); shuffle(p.begin(),p.end(),rng); for(int i=0;i<n;i++) F[p[i]]=p[(i+1)%n]; }
        else if(t==2){ vector<int> p(n); iota(p.begin(),p.end(),1); shuffle(p.begin(),p.end(),rng); int k=1+rng()%n; for(int i=0;i<n;i++) F[p[i]]= i+1<n? p[i+1] : p[n-k]; }
        else { vector<int> p(n); iota(p.begin(),p.end(),1); shuffle(p.begin(),p.end(),rng); int k=max(1,n-(int)(rng()%1000)); for(int i=0;i<n;i++) F[p[i]]= i<k? p[(i+1)%k] : p[rng()%i]; }
        NQ=0; auto [c,r]=solve(n); int used=NQ; worst=max(worst,used);
        if(c<1||c>n||r<1||r>n||ask(c,r)!=c||used>1000){printf("FAIL n=%d t=%d q=%d\n",n,t,used);return 1;}
    }
    printf("ok worst queries %d\n",worst);
#else
    int n; if(scanf("%d",&n)!=1) return 0;
    auto [c,r]=solve(n);
    printf("! %d %d\n",c,r);fflush(stdout);
#endif
}
