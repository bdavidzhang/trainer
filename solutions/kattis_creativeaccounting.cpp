#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,l,h;scanf("%d %d %d",&n,&l,&h);vector<int>p(n+1,0);
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);p[i]=p[i-1]+x;}
    int mn=INT_MAX,mx=-1;
    for(int s=l;s<=h;s++)for(int o=1;o<=s;o++){
        int c=0,prev=0;
        for(int b=min(o,n);;b=min(b+s,n)){ if(p[b]>p[prev])c++; prev=b; if(b==n)break;}
        mn=min(mn,c);mx=max(mx,c);
    }
    printf("%d %d\n",mn,mx);
}
