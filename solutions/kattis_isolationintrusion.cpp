#include <bits/stdc++.h>
using namespace std;
int main(){int n,m[3];cin>>n>>m[0]>>m[1]>>m[2];
for(int i=0;i<3;i++){bool ok=true;for(int j=0;j<3;j++)if(j!=i&&m[i]+n>=m[j])ok=false;if(ok){cout<<m[i]+n<<"\n";return 0;}}
cout<<"impossible\n";}
