#include <bits/stdc++.h>
using namespace std;
int main(){long long L,num[3],den[3];cin>>L;for(int i=0;i<3;i++)cin>>num[i]>>den[i];
 bool fr[3]={false,false,false};
 // a coordinate that lands exactly on a grid plane can always be assigned to a non-middle slab from then on
 for(long long l=0;l<L;l++){int mid=0;bool allfree=true;
  for(int i=0;i<3;i++){if(fr[i])continue;
   num[i]*=3;long long d=num[i]/den[i];num[i]%=den[i];
   if(num[i]==0){fr[i]=true;continue;}
   allfree=false;
   if(d==1)mid++;}
  if(mid>=2){puts("0");return 0;}
  if(allfree)break;}
 puts("1");}
