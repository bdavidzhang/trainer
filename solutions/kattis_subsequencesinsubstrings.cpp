#include <bits/stdc++.h>
using namespace std;
int main(){
    string s,t; cin>>s>>t;
    int n=s.size();
    vector<array<int,26>> nx(n+2);
    nx[n].fill(n); nx[n+1].fill(n);
    for(int i=n-1;i>=0;i--){ nx[i]=nx[i+1]; nx[i][s[i]-'a']=i; }
    long long ans=0;
    for(int i=0;i<n;i++){
        int p=i; bool ok=true;
        for(char c:t){
            int q=nx[p][c-'a'];
            if(q>=n){ok=false;break;}
            p=q+1;
        }
        if(!ok) break;
        ans+=n-p+1;
    }
    printf("%lld\n",ans);
}
