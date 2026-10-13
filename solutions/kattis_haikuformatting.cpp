#include <bits/stdc++.h>
using namespace std;
static bool isv(char c){return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';}
int syl(const string&tok){string w;for(char c:tok){if(isalpha((unsigned char)c))w+=tolower(c);else break;}
 int n=w.size();if(n==0)return 1;vector<int>v(n,0);
 for(int i=0;i<n;i++){char c=w[i];
  if(c=='y')v[i]=!(i+1<n&&isv(w[i+1]));
  else if(c=='u')v[i]=!(i>0&&w[i-1]=='q');
  else v[i]=isv(c);}
 vector<int>cnt=v; // cnt: vowels that count
 if(w[n-1]=='e'){bool keep=(n>=3&&w[n-2]=='l'&&!v[n-3]);if(!keep)cnt[n-1]=0;}
 if(n>=2&&w[n-2]=='e'&&w[n-1]=='s'){bool keep=(n>=4&&!v[n-3]&&!v[n-4]);if(!keep)cnt[n-2]=0;}
 int s=0;for(int i=0;i<n;i++)if(cnt[i]&&(i==0||!cnt[i-1]))s++;
 return max(s,1);}
int main(){string line;while(getline(cin,line)){while(!line.empty()&&(line.back()=='\r'||line.back()=='\n'))line.pop_back();if(!line.empty())break;}
 vector<string>t;{stringstream ss(line);string x;while(ss>>x)t.push_back(x);}
 int need[3]={5,7,5};size_t i=0;vector<string>out;bool ok=true;
 for(int l=0;l<3&&ok;l++){int c=0;string cur;while(i<t.size()&&c<need[l]){c+=syl(t[i]);if(!cur.empty())cur+=' ';cur+=t[i];i++;}
  if(c!=need[l])ok=false;out.push_back(cur);}
 if(i!=t.size())ok=false;
 if(ok)for(auto&s:out)cout<<s<<"\n";else cout<<line<<"\n";}
