#include <bits/stdc++.h>
using namespace std;
typedef unsigned __int128 u128;
int main(){int n;cin>>n;vector<int>a(n);int best=0;for(auto&e:a){string s;cin>>s;u128 v=0;for(char c:s)v=v*10+(c-'0');e=0;while(v>1){v>>=1;e++;}best=max(best,e);}
 for(int e=0;e<=125&&!a.empty();e++){vector<int>b;size_t i=0;while(i<a.size()){if(a[i]==e){size_t j=i;while(j<a.size()&&a[j]==e)j++;for(size_t t=0;t<(j-i)/2;t++){b.push_back(e+1);best=max(best,e+1);}i=j;}else b.push_back(a[i++]);}a=b;}
 u128 v=(u128)1<<best;string s;while(v>0){s+=char('0'+(int)(v%10));v/=10;}reverse(s.begin(),s.end());cout<<s<<endl;}
