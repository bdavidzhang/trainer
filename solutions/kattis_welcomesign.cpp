#include <bits/stdc++.h>
using namespace std;
int main(){int r,c;cin>>r>>c;int odd=0;while(r--){string w;cin>>w;int b=c-w.size();int l=b/2;if(b%2){odd++;if(odd%2==0)l=b/2+1;}cout<<string(l,'.')<<w<<string(b-l,'.')<<"\n";}}
