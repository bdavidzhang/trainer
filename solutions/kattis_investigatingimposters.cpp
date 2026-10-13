#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k;scanf("%d %d",&n,&k);
    // reach[j] = set of villagers who (transitively) vouch for j, including j
    vector<bitset<500>> r(n);
    for(int i=0;i<n;i++){
        r[i][i]=1;
        int s;scanf("%d",&s);
        while(s--){int x;scanf("%d",&x);r[x-1][i]=1;}
    }
    // r[j][i]=1 means i -> j (i lists j). closure: if i reaches m and m reaches j
    for(int m=0;m<n;m++)for(int j=0;j<n;j++)if(r[j][m])r[j]|=r[m];
    for(int j=0;j<n;j++)printf("%d\n",(int)r[j].count()<=k?0:1);
}
