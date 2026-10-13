#include <bits/stdc++.h>
using namespace std;
int main(){int n;if(scanf("%d",&n)!=1)n=0;
 // piece classes by flat sides: 0, 1, 2 adjacent, 2 opposite, 3, 4
 long long c0=0,c1=0,c2a=0,c2o=0,c3=0,c4=0,zeros=0,twos=0;
 for(int i=0;i<n;i++){char s[16];scanf("%15s",s);string t=s;while(t.size()<4)t="0"+t;
  int f=0;for(int j=0;j<4;j++){if(t[j]=='1')f++;else if(t[j]=='0')zeros++;else twos++;}
  if(f==0)c0++;else if(f==1)c1++;else if(f==3)c3++;else if(f==4)c4++;
  else{ if((t[0]=='1'&&t[2]=='1')||(t[1]=='1'&&t[3]=='1'))c2o++;else c2a++; }}
 if(n<1){puts("No\nUnsolved\nUnsolved");return 0;}
 puts("Yes");
 bool ok2=false;
 for(long long r=1;r*r<=n;r++){if(n%r)continue;long long c=n/r;bool ok;
  if(r==1&&c==1)ok=(c4==1);
  else if(r==1)ok=(c3==2&&c2o==c-2&&c0==0&&c1==0&&c2a==0&&c4==0);
  else ok=(c2a==4&&c1==2*(r-2)+2*(c-2)&&c0==(r-2)*(c-2)&&c2o==0&&c3==0&&c4==0);
  if(ok)ok2=true;}
 if(!ok2){puts("No\nUnsolved");return 0;}
 puts("Yes");
 puts(zeros==twos?"Yes":"No");}
