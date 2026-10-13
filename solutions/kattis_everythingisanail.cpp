#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);vector<int>t(n);for(auto&x:t)scanf("%d",&x);
    int p[3]={0,1,2},ans=0;
    do{
        int d[3]={0,0,0};
        for(int x:t){
            if(x==p[2])d[2]=max({d[0],d[1],d[2]})+1;
            if(x==p[1])d[1]=max(d[0],d[1])+1;
            if(x==p[0])d[0]++;
        }
        ans=max({ans,d[0],d[1],d[2]});
    }while(next_permutation(p,p+3));
    printf("%d\n",ans);
}
