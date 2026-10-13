#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;string line;getline(cin,line);n=stoi(line);
    vector<vector<int>>M(n,vector<int>(n));
    for(int i=0;i<n;i++){getline(cin,line);istringstream ss(line);for(int j=0;j<n;j++)ss>>M[i][j];}
    string t;getline(cin,t);
    while(!t.empty()&&(t.back()=='\r'||t.back()=='\n'))t.pop_back();
    while(t.size()%n)t+=' ';
    auto enc=[](char c){return c==' '?36:(isdigit((unsigned char)c)?26+c-'0':c-'A');};
    auto dec=[](int v){return v==36?' ':(v>=26?char('0'+v-26):char('A'+v));};
    string o;
    for(size_t b=0;b<t.size();b+=n)for(int i=0;i<n;i++){int s=0;for(int j=0;j<n;j++)s+=M[i][j]*enc(t[b+j]);o+=dec(s%37);}
    puts(o.c_str());
}
