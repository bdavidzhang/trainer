#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;vector<string>h(n),w(n);string nm;map<string,int>owner;
    for(int i=0;i<n;i++){cin>>nm>>h[i]>>w[i];owner[h[i]]=i;}
    vector<int>nx(n,-1);
    for(int i=0;i<n;i++){auto it=owner.find(w[i]);if(it!=owner.end())nx[i]=it->second;}
    int best=0;
    for(int i=0;i<n;i++){int c=i,len=0;bool ok=false;
        for(int s=0;s<=n;s++){c=nx[c];len++;if(c<0)break;if(c==i){ok=true;break;}}
        if(ok&&len>=2)best=max(best,len);}
    if(best)printf("%d\n",best);else puts("No trades possible");
}
