#include <bits/stdc++.h>
using namespace std;
int main(){vector<string> h;string c;
 while(cin>>c){h.push_back(c);
  while(true){int n=h.size();int f=-1;
   for(int i=n-1;i>=3;i--)if(h[i][0]==h[i-3][0]){f=i;break;}
   if(f>=0){h.erase(h.begin()+f-3,h.begin()+f+1);continue;}
   for(int i=n-1;i>=3;i--)if(h[i][1]==h[i-3][1]){f=i;break;}
   if(f>=0){h.erase(h.begin()+f);h.erase(h.begin()+f-3);continue;}
   break;}}
 printf("%d",(int)h.size());for(auto&x:h)printf(" %s",x.c_str());puts("");}
