#include <bits/stdc++.h>
using namespace std;
int main(){string line;getline(cin,line);int n=stoi(line);
 auto val=[](char c){return c==' '?0:c-'a'+1;};
 auto sym=[](int v){return v==0?' ':char('a'+v-1);};
 while(n--){getline(cin,line);while(!line.empty()&&(line.back()=='\r'||line.back()=='\n'))line.pop_back();
  char t=line[0];string m=line.size()>2?line.substr(2):"";string r;
  if(t=='e'){int u=0;for(char c:m){u=(u+val(c))%27;r+=sym(u);}}
  else{int p=0;for(char c:m){int v=val(c);r+=sym(((v-p)%27+27)%27);p=v;}}
  cout<<r<<"\n";}
}
