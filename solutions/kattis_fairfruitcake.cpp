#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// The cut must pass through the centre c (else the strip between the line and its mirror has
// zero area). A line through c gives exactly two parts iff (line ∩ open interior) is one segment,
// i.e. the ray from c in that direction has no interior points after its first boundary hit.
int n;
vector<ll> X,Y;
static inline ll cr(int a,int b){return X[a]*Y[b]-Y[a]*X[b];}
static inline int half(int a){return (Y[a]>0||(Y[a]==0&&X[a]>0))?0:1;}
int main(){
    scanf("%d",&n);
    vector<ll> px(n),py(n);
    for(int i=0;i<n;i++)scanf("%lld %lld",&px[i],&py[i]);
    ll Cx=px[0]+px[n/2],Cy=py[0]+py[n/2];
    X.resize(n);Y.resize(n);
    for(int i=0;i<n;i++){X[i]=2*px[i]-Cx;Y[i]=2*py[i]-Cy;}
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int a,int b){
        int ha=half(a),hb=half(b);
        if(ha!=hb)return ha<hb;
        ll c=cr(a,b);
        if(c!=0)return c>0;
        return X[a]*X[a]+Y[a]*Y[a]<X[b]*X[b]+Y[b]*Y[b];
    });
    vector<int> grp(n);
    vector<vector<int>> mem;
    for(int t=0;t<n;t++){
        int i=ord[t];
        if(t==0||half(ord[t-1])!=half(i)||cr(ord[t-1],i)!=0)mem.push_back({});
        grp[i]=mem.size()-1;
        mem.back().push_back(i); // sorted by distance within group
    }
    int G=mem.size();
    vector<ll> dc(2*G+1,0),ds(2*G+1,0);
    auto add=[&](int l,int r,ll id){ // slots l..r inclusive
        dc[l]++;dc[r+1]--;ds[l]+=id;ds[r+1]-=id;
    };
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        ll c=cr(i,j);
        if(c==0)continue;
        int a=grp[i],b=grp[j];
        if(c<0)swap(a,b);
        int l=2*a+1,r=2*b-1;
        if(l<=r)add(l,r,i);
        else{add(l,2*G-1,i);if(r>=0)add(0,r,i);}
    }
    vector<ll> cnt(2*G),sm(2*G);
    {ll c=0,s=0;for(int i=0;i<2*G;i++){c+=dc[i];s+=ds[i];cnt[i]=c;sm[i]=s;}}
    auto answer=[&](ll dx,ll dy){
        printf("%lld/2 %lld/2 %lld/2 %lld/2\n",Cx,Cy,Cx+dx,Cy+dy);
    };
    for(int g=0;g<G;g++){
        if(cnt[2*g+1]==1){
            int a=mem[g][0],b=mem[(g+1)%G][0];
            answer(X[a]+X[b],Y[a]+Y[b]);
            return 0;
        }
    }
    for(int g=0;g<G;g++){
        ll p=cnt[2*g];
        if(p>1)continue;
        vector<int>&V=mem[g];
        int k=V.size();
        int posCross=-1; // number of vertices before the proper crossing
        if(p==1){
            int e=sm[2*g];int a=e,b=(e+1)%n;
            ll ex=X[b]-X[a],ey=Y[b]-Y[a];
            ll so=ex*(0-Y[a])-ey*(0-X[a]);
            posCross=0;
            for(int v:V){
                ll sv=ex*(Y[v]-Y[a])-ey*(X[v]-X[a]);
                if((sv>0)==(so>0))posCross++;
            }
        }
        // feature list: vertex indices, -1 for the crossing
        vector<int> F;
        for(int t=0;t<k;t++){
            if(posCross==t)F.push_back(-1);
            F.push_back(V[t]);
        }
        if(posCross==k)F.push_back(-1);
        int plus=0;bool ok=true;
        for(size_t t=0;t+1<F.size()&&ok;t++){
            int f=F[t];
            if(f<0)plus++;
            else{
                int u1=(f+1)%n,u2=(f+n-1)%n;
                if(cr(f,u1)>0)plus++;
                if(cr(f,u2)>0)plus++;
            }
            int h=F[t+1];
            bool radial=f>=0&&h>=0&&((f+1)%n==h||(h+1)%n==f);
            if(!radial&&plus%2==0)ok=false;
        }
        if(ok){
            answer(X[V[0]],Y[V[0]]);
            return 0;
        }
    }
    puts("impossible");
}
