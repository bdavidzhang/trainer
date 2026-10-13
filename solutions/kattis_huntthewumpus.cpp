#include <bits/stdc++.h>
using namespace std;
int main(){long long s;cin>>s;vector<int>w;
 while(w.size()<4){s=s+s/13+15;int v=s%100;if(find(w.begin(),w.end(),v)==w.end())w.push_back(v);}
 string g;int moves=0;
 while(!w.empty()&&cin>>g){moves++;int v=stoi(g);
  auto it=find(w.begin(),w.end(),v);
  if(it!=w.end()){puts("You hit a wumpus!");w.erase(it);}
  if(!w.empty()){int d=INT_MAX;for(int u:w)d=min(d,abs(u/10-v/10)+abs(u%10-v%10));printf("%d\n",d);}
 }
 printf("Your score is %d moves.\n",moves);}
