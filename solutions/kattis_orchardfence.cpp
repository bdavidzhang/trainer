#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct V{ll x,y;};
static inline int half(const V&a){return (a.y>0||(a.y==0&&a.x>0))?0:1;}
static inline ll cross(const V&a,const V&b){return a.x*b.y-a.y*b.x;}
static inline ll dot(const V&a,const V&b){return a.x*b.x+a.y*b.y;}
int main(){
    int n,k; double d;
    scanf("%d %d %lf",&n,&k,&d);
    vector<V> p(n);
    for(auto&q:p){double x,y;scanf("%lf %lf",&x,&y);q.x=llround(x*100);q.y=llround(y*100);}
    const double PI=acos(-1.0);
    if(k==1||n==1){printf("%.10f\n",PI*d);return 0;}
    // prob[m] = C(n-2-m,k-2)/C(n,k): both endpoints kept, m forbidden points all removed
    vector<double> prob(n,0.0);
    prob[0]=(double)k*(k-1)/((double)n*(n-1));
    for(int m=0;m+1<=n-2;m++){
        double num=(double)(n-2-m)-(k-2);
        prob[m+1]=num>0?prob[m]*num/(double)(n-2-m):0.0;
    }
    double total=0;
    int m=n-1;
    vector<V> a(m); vector<int> gsz(m);
    for(int i=0;i<n;i++){
        int c=0;
        for(int j=0;j<n;j++)if(j!=i)a[c++]={p[j].x-p[i].x,p[j].y-p[i].y};
        sort(a.begin(),a.end(),[](const V&u,const V&v){
            int hu=half(u),hv=half(v); if(hu!=hv)return hu<hv;
            ll cr=cross(u,v); if(cr!=0)return cr>0;
            return dot(u,u)<dot(v,v);
        });
        // group sizes
        for(int s=0;s<m;){
            int e=s; while(e<m&&half(a[e])==half(a[s])&&cross(a[s],a[e])==0)e++;
            for(int t=s;t<e;t++)gsz[t]=e-s;
            s=e;
        }
        int e=0; // pointer in doubled index space
        for(int s=0;s<m;){
            int sz=gsz[s];
            if(e<s+sz)e=s+sz;
            while(e<s+m&&cross(a[s],a[e%m])>0)e++;
            int left=e-(s+sz);
            int opp=0;
            if(e<s+m){const V&q=a[e%m]; if(cross(a[s],q)==0&&dot(a[s],q)<0)opp=gsz[e%m];}
            int right=m-sz-left-opp;
            for(int t=0;t<sz;t++){
                int bad=right+opp+(sz-1-t);
                if(bad<=n-2) total+=prob[bad]*sqrt((double)dot(a[s+t],a[s+t]));
            }
            s+=sz;
        }
    }
    printf("%.10f\n",total/100.0+PI*d);
}
