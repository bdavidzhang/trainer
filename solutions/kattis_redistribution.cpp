#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n); vector<int> s(n), id(n); int sum=0;
    for(int i=0;i<n;i++){scanf("%d",&s[i]);sum+=s[i];id[i]=i;}
    stable_sort(id.begin(),id.end(),[&](int a,int b){return s[a]>s[b];});
    if(2*s[id[0]]>sum){puts("impossible");return 0;}
    for(int i=0;i<n;i++) printf("%d%c",id[i]+1,i+1<n?' ':'\n');
}
