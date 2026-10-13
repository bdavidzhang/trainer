#include <bits/stdc++.h>
using namespace std;
int main(){
    int p,u;cin>>p>>u;int n=p+u;
    vector<int>a(n),pos(n+1),pin0(n+1);
    for(int i=0;i<n;i++){cin>>a[i];pos[a[i]]=i;pin0[a[i]]=i<p;}
    int p2,u2;cin>>p2>>u2;
    vector<int>b(n);for(auto&x:b)cin>>x;
    // cost if everything is touched
    int cost=0;
    for(int i=0;i<n;i++){int f=i<p2; cost+= (f==pin0[b[i]])?2:1;}
    // untouched prefix of final pinned list
    int last=-1;
    for(int i=0;i<p2;i++){int x=b[i]; if(!pin0[x]||pos[x]<last)break; last=pos[x]; cost-=2;}
    // untouched suffix of final unpinned list
    last=n;
    for(int i=n-1;i>=p2;i--){int x=b[i]; if(pin0[x]||pos[x]>last)break; last=pos[x]; cost-=2;}
    cout<<cost<<endl;
}
