#include <bits/stdc++.h>
using namespace std;
int main(){int n;static char buf[300005];scanf("%d %s",&n,buf);string s(buf);
 long long po=0,pc=0,P=0,M=0;string let,nz,zs;
 for(char c:s){if(c=='(')po++;else if(c==')')pc++;else if(c=='+')P++;else if(c=='*')M++;else if(c=='0')zs+=c;else if(isdigit(c))nz+=c;else let+=c;}
 long long tot=let.size()+nz.size()+zs.size(),k=P+M+1,p=po;
 bool ok=po==pc&&k<=tot;
 if(ok&&p>=1)ok=P>=p&&M>=(p+1)/2;
 if(ok&&k<tot&&let.empty()&&nz.empty())ok=false;
 if(!ok){puts("impossible");return 0;}
 // template, '#' = atom
 string t;long long up=0,um=0;
 if(p==0)t="#";
 else if(p==1){t="(#+#)*#";up=1;um=1;}
 else{long long j=p/2;t=string(j-1,'(')+"(#+#)*(#+#)";for(long long i=1;i<j;i++)t+="+#)*(#+#)";up=2*j;um=j;if(p&1){t+="*(#+#)";up++;um++;}}
 for(long long i=um;i<M;i++)t+="*#";
 for(long long i=up;i<P;i++)t+="+#";
 // atoms: k-1 single chars and one big atom
 string head,pool;
 if(k==tot){pool=let+nz+zs;}
 else if(!let.empty()){head=let.substr(0,1);pool=let.substr(1)+nz+zs;}
 else{head=nz.substr(0,1);pool=nz.substr(1)+zs;}
 string big;size_t singles;
 if(k==tot){singles=k;}else{singles=k-1;big=head+pool.substr(singles);}
 string out;out.reserve(n+1);size_t idx=0;bool bigdone=(k==tot);
 for(char c:t){if(c!='#'){out+=c;continue;}
  if(!bigdone){out+=big;bigdone=true;}else out+=pool[idx++];}
 printf("possible\n%s\n",out.c_str());}
