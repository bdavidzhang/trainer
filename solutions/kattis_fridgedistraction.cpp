#include <bits/stdc++.h>
using namespace std;
int main(){int n,t;cin>>n>>t;int k=(t+n-1)/n;
// positions: k values in [1,n] summing to t
vector<int> pos(k,t/k);for(int i=0;i<t%k;i++)pos[i]++;
vector<char> f(n);for(int i=0;i<n;i++)f[i]='a'+i;
printf("%d\n",k);
for(int i=0;i<k;i++){int p=pos[i]-1;char c=f[p];f.erase(f.begin()+p);f.insert(f.begin(),c);printf("%c%c",c,i+1<k?' ':'\n');}
}
