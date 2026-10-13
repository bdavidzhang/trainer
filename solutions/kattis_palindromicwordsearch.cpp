#include <bits/stdc++.h>
using namespace std;
// for string s, out[c] = longest palindromic substring covering position c
static void cover(const string&s,vector<int>&out){int n=s.size();vector<int>mb(n);for(int i=0;i<n;i++)mb[i]=i;
 for(int c=0;c<n;c++){int l=c,r=c;while(l>=0&&r<n&&s[l]==s[r]){mb[l]=max(mb[l],r);l--;r++;}
  l=c;r=c+1;while(l>=0&&r<n&&s[l]==s[r]){mb[l]=max(mb[l],r);l--;r++;}}
 out.assign(n,1);
 // palindromes starting at a with max end mb[a]; inner palindromes are also covered via their own starts
 vector<int>diff;for(int a=0;a<n;a++){int len=mb[a]-a+1;for(int c=a;c<=mb[a];c++)if(out[c]<len)out[c]=len;}}
int main(){int R,C;cin>>R>>C;vector<string>g(R);for(auto&s:g)cin>>s;
 vector<vector<int>>H(R),V(C);for(int r=0;r<R;r++)cover(g[r],H[r]);
 for(int c=0;c<C;c++){string s(R,' ');for(int r=0;r<R;r++)s[r]=g[r][c];cover(s,V[c]);}
 long long best=0;for(int r=0;r<R;r++)for(int c=0;c<C;c++)best=max(best,(long long)H[r][c]*V[c][r]);
 printf("%lld\n",best);}
