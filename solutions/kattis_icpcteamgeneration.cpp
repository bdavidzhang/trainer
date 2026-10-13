#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<int>a(n+3),b(n+3);for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
 // a team is valid iff its min and max accept each other; greedy from the left with consecutive triples
 int i=1,c=0;while(i+2<=n){if(i+2<=b[i]&&a[i+2]<=i){c++;i+=3;}else i++;}
 cout<<c<<"\n";}
