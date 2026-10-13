#include <bits/stdc++.h>
using namespace std;
// x_i = 2023^(2023^L_i), L_i = sum of 2023^(L_j) over ops applied to i. With <=1000 terms there are no
// carries, so comparing L's = lexicographic comparison of the descending multisets of exponent ranks.
vector<vector<int>> ver; // ver[id] = term ids sorted by rank descending
vector<int> rk, ord;     // ord: ids ascending by value
int cmp(const vector<int>&u,const vector<int>&v){
    size_t k=min(u.size(),v.size());
    for(size_t i=0;i<k;i++){if(rk[u[i]]!=rk[v[i]])return rk[u[i]]<rk[v[i]]?-1:1;}
    if(u.size()==v.size())return 0;return u.size()<v.size()?-1:1;
}
int main(){
    int n,m;scanf("%d %d",&n,&m);
    ver.push_back({});rk.push_back(0);ord.push_back(0);
    vector<int> cur(n+1,0);
    while(m--){
        char c[4];int i,j;scanf("%s %d %d",c,&i,&j);
        if(c[0]=='?'){
            int a=rk[cur[i]],b=rk[cur[j]];
            puts(a>b?">":a<b?"<":"=");
        } else {
            vector<int> v=ver[cur[i]];int t=cur[j];
            size_t p=0;while(p<v.size()&&rk[v[p]]>=rk[t])p++;
            v.insert(v.begin()+p,t);
            int lo=0,hi=ord.size();int found=-1;
            while(lo<hi){int mid=(lo+hi)/2;int r=cmp(ver[ord[mid]],v);if(r==0){found=ord[mid];break;}if(r<0)lo=mid+1;else hi=mid;}
            if(found>=0){cur[i]=found;continue;}
            int id=ver.size();ver.push_back(v);rk.push_back(0);
            ord.insert(ord.begin()+lo,id);
            for(size_t k=0;k<ord.size();k++)rk[ord[k]]=k;
            cur[i]=id;
        }
    }
}
