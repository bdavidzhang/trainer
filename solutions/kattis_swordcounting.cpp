#include <bits/stdc++.h>
using namespace std;
typedef unsigned __int128 u128;
int main(){
    int n,m;scanf("%d %d",&n,&m);
    vector<int>U(m),W(m),deg(n+1,0);
    for(int i=0;i<m;i++){scanf("%d %d",&U[i],&W[i]);deg[U[i]]++;deg[W[i]]++;}
    vector<vector<pair<int,int>>> out(n+1);
    auto less_=[&](int a,int b){return deg[a]<deg[b]||(deg[a]==deg[b]&&a<b);};
    for(int i=0;i<m;i++){if(less_(U[i],W[i]))out[U[i]].push_back({W[i],i});else out[W[i]].push_back({U[i],i});}
    vector<long long>tri(m,0);vector<int>mark(n+1,-1);
    for(int u=1;u<=n;u++){
        for(auto&e:out[u])mark[e.first]=e.second;
        for(auto&e:out[u]){int v=e.first;
            for(auto&f:out[v]){int w=f.first;if(mark[w]>=0){tri[e.second]++;tri[f.second]++;tri[mark[w]]++;}}
        }
        for(auto&e:out[u])mark[e.first]=-1;
    }
    u128 ans=0;
    auto C3=[](u128 k)->u128{return k<3?0:k*(k-1)*(k-2)/6;};
    auto C2=[](u128 k)->u128{return k<2?0:k*(k-1)/2;};
    for(int i=0;i<m;i++){
        for(int r=0;r<2;r++){
            int D=r?U[i]:W[i],B=r?W[i]:U[i];
            if(deg[D]<4)continue;
            ans+=(u128)(deg[B]-1)*C3(deg[D]-1)-(u128)tri[i]*C2(deg[D]-2);
        }
    }
    string s;if(ans==0)s="0";while(ans>0){s+=char('0'+(int)(ans%10));ans/=10;}
    reverse(s.begin(),s.end());puts(s.c_str());
}
