#include <bits/stdc++.h>
using namespace std;
int main(){int c;cin>>c;vector<long long>v(c);long long T=0;for(auto&x:v){cin>>x;T+=x;}
sort(v.begin(),v.end());long long F=v[c-1],S=v[c-2];
if(2*F>T){puts("IMPOSSIBLE TO WIN");return 0;}
// best case: every eliminated candidate's ballots all transfer to the 2nd place candidate
int r=0;for(int i=0;i<c-2;i++){S+=v[i];r++;if(2*S>T){printf("%d\n",r);return 0;}}
puts("IMPOSSIBLE TO WIN");}
