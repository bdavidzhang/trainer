#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size();vector<int>P(n+1,0),mx(n+2),mn(n+2);
for(int i=0;i<n;i++)P[i+1]=P[i]+(s[i]=='R'?1:-1);
mx[n]=mn[n]=P[n];for(int i=n-1;i>=0;i--){mx[i]=max(mx[i+1],P[i]);mn[i]=min(mn[i+1],P[i]);}
int V=0;for(int i=0;i<n;i++)V=max(V,max(mx[i+1]-P[i],P[i]-mn[i+1]));
for(int i=0;i<n;i++)if(max(mx[i+1]-P[i],P[i]-mn[i+1])==V){for(int j=i+1;j<=n;j++)if(abs(P[j]-P[i])==V){printf("%d %d\n",i+1,j);return 0;}}
}
