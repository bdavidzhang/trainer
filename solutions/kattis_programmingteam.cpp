#include <bits/stdc++.h>
using namespace std;
int k,n;int s[2505],p[2505],sz[2505],ordv[2505];
vector<int> ch[2505];
static double f[2503][2503];
int main(){
    scanf("%d %d",&k,&n);
    for(int i=1;i<=n;i++){int r;scanf("%d %d %d",&s[i],&p[i],&r);ch[r].push_back(i);}
    // preorder (iterative), CEO excluded
    vector<int> ord;{vector<int> st;for(int i=(int)ch[0].size()-1;i>=0;i--)st.push_back(ch[0][i]);
        while(!st.empty()){int u=st.back();st.pop_back();ord.push_back(u);for(int i=(int)ch[u].size()-1;i>=0;i--)st.push_back(ch[u][i]);}}
    for(int i=n;i>=1;i--){sz[i]++;}
    // subtree sizes: children have larger index
    {vector<int> parent(n+1,0);for(int r=0;r<=n;r++)for(int c:ch[r])parent[c]=r;
     for(int i=n;i>=1;i--)if(parent[i])sz[parent[i]]+=sz[i];}
    const double NEG=-1e18;
    double lo=0,hi=10001;
    for(int it=0;it<50;it++){
        double mid=(lo+hi)/2;
        for(int j=0;j<=k;j++)f[n][j]=j?NEG:0;
        for(int i=n-1;i>=0;i--){
            int u=ord[i];double v=p[u]-mid*s[u];
            double*a=f[i+sz[u]],*b=f[i+1],*c=f[i];
            c[0]=0;
            for(int j=1;j<=k;j++){double x=a[j],y=b[j-1]+v;c[j]=x>y?x:y;}
        }
        if(f[0][k]>=0)lo=mid;else hi=mid;
    }
    printf("%.3f\n",lo);
}
