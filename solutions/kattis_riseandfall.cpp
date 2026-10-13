#include <bits/stdc++.h>
using namespace std;
int main(){int t;scanf("%d",&t);static char buf[100005];while(t--){scanf("%s",buf);string s=buf;int n=s.size();bool fall=false;
 for(int i=1;i<n;i++){if(s[i]<s[i-1])fall=true;else if(s[i]>s[i-1]&&fall){for(int j=i;j<n;j++)s[j]=s[i-1];break;}}
 puts(s.c_str());}}
