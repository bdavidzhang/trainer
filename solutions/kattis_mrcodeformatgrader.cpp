#include <bits/stdc++.h>
using namespace std;
static void out(const char*h,const vector<int>&v){
    vector<string> items;
    for(size_t i=0;i<v.size();){size_t j=i;while(j+1<v.size()&&v[j+1]==v[j]+1)j++;
        items.push_back(i==j?to_string(v[i]):to_string(v[i])+"-"+to_string(v[j]));i=j+1;}
    string s=h;
    for(size_t i=0;i<items.size();i++){
        if(i>0) s+= (i+1==items.size()?" and ":", ");
        s+=items[i];
    }
    puts(s.c_str());
}
int main(){int c,n;scanf("%d %d",&c,&n);vector<char> bad(c+1,0);vector<int>e,g;for(int i=0;i<n;i++){int x;scanf("%d",&x);bad[x]=1;}
    for(int i=1;i<=c;i++)(bad[i]?e:g).push_back(i);
    out("Errors: ",e);out("Correct: ",g);}
