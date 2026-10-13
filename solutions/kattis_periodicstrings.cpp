#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size();
 for(int k=1;k<=n;k++){if(n%k)continue;bool ok=true;
  for(int b=k;b<n&&ok;b+=k)for(int j=0;j<k;j++)if(s[b+j]!=s[b-k+(j+k-1)%k]){ok=false;break;}
  if(ok){cout<<k<<endl;return 0;}}
}
