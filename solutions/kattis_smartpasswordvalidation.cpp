#include <bits/stdc++.h>
using namespace std;
int LSm[256],RSm[256];
string cl(string s){for(char&c:s){if(islower((unsigned char)c))c=toupper(c);else if(isupper((unsigned char)c))c=tolower(c);}return s;}
bool oneExtra(const string&lng,const string&sht){ // lng = sht with one inserted char
 if(lng.size()!=sht.size()+1)return false;
 size_t i=0;while(i<sht.size()&&lng[i]==sht[i])i++;
 return lng.compare(i+1,string::npos,sht,i,string::npos)==0;}
int main(){
 const char* lo[4]={"`1234567890-=","qwertyuiop[]\\","asdfghjkl;'","zxcvbnm,./"};
 const char* up[4]={"~!@#$%^&*()_+","QWERTYUIOP{}|","ASDFGHJKL:\"","ZXCVBNM<>?"};
 int lc[4]={6,5,5,5};
 for(int i=0;i<256;i++)LSm[i]=RSm[i]=i;
 for(int r=0;r<4;r++){int L=strlen(lo[r]);for(int j=0;j<L;j++)for(int k=0;k<2;k++){const char*row=k?up[r]:lo[r];unsigned char c=row[j];
   if(j<lc[r])LSm[c]=(unsigned char)row[j+1];else RSm[c]=(unsigned char)row[j-1];}}
 string p;getline(cin,p);while(!p.empty()&&(p.back()=='\r'||p.back()=='\n'))p.pop_back();
 string line;getline(cin,line);int n=atoi(line.c_str());
 string a=p,b=p;for(char&c:a)c=LSm[(unsigned char)c];for(char&c:b)c=RSm[(unsigned char)c];
 for(int q=0;q<n;q++){string t;getline(cin,t);while(!t.empty()&&(t.back()=='\r'||t.back()=='\n'))t.pop_back();
  bool ok=false;
  for(int k=0;k<2&&!ok;k++){string u=k?cl(t):t;
   if(u==p||u==a||u==b||oneExtra(u,p)||oneExtra(p,u))ok=true;}
  puts(ok?"YES":"NO");}
}
