#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; long long R;
    scanf("%d %lld",&n,&R);
    vector<long long> a(n);
    for(auto&x:a) scanf("%lld",&x);
    sort(a.begin(),a.end());
    vector<long long> p; vector<int> c;
    for(int i=0;i<n;i++){
        if(!p.empty()&&p.back()==a[i]) c.back()++;
        else {p.push_back(a[i]); c.push_back(1);}
    }
    vector<long long> res;
    while(!p.empty()){
        int m=p.size();
        long long best=-1,cur=0; int bj=-1,bl=-1;
        int l=0;
        for(int j=0;j<m;j++){
            cur+=c[j];
            while(p[l]<p[j]-2*R){cur-=c[l];l++;}
            if(cur>best){best=cur;bj=j;bl=l;}
        }
        res.push_back(p[bj]-R);
        p.erase(p.begin()+bl,p.begin()+bj+1);
        c.erase(c.begin()+bl,c.begin()+bj+1);
    }
    printf("%d\n",(int)res.size());
    for(size_t i=0;i<res.size();i++) printf("%lld%c",res[i],i+1==res.size()?'\n':' ');
}
