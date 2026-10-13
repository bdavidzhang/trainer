#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n); vector<int> k(n),id(n);
    for(int i=0;i<n;i++){scanf("%d",&k[i]);id[i]=i;}
    int p=0;
    while(id.size()>1){
        int s=id.size();
        int e=(p+k[id[p]]-1)%s;
        id.erase(id.begin()+e);
        p=e%(s-1);
    }
    printf("%d\n",id[0]+1);
}
