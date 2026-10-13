#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,k;scanf("%d %d %d",&n,&m,&k);vector<bitset<2000>> a(n);
for(int i=0;i<m;i++){int x,y;scanf("%d %d",&x,&y);x--;y--;a[x][y]=1;a[y][x]=1;}
for(int i=0;i<n;i++){if((int)a[i].count()<k)continue;for(int j=i+1;j<n;j++)if((int)(a[i]&a[j]).count()>=k){puts("YES");return 0;}}
puts("NO");}
