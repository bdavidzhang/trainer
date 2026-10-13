#include <bits/stdc++.h>
using namespace std;
int main(){int R=30,C=21;printf("%d %d\n",R,C);fflush(stdout);int r,c;if(scanf("%d %d",&r,&c)!=2||(!r&&!c))return 0;
int DR=0,DC=0;
for(int dr=-1;dr<=1&&!DR&&!DC;dr++)for(int dc=-1;dc<=1;dc++){if(!dr&&!dc)continue;bool ok=true;
  for(int t=-1;t<=2;t++)if(R+t*dr==r&&C+t*dc==c)ok=false;
  if(ok){DR=dr;DC=dc;break;}}
printf("%d %d\n",R+DR,C+DC);fflush(stdout);int r2,c2;if(scanf("%d %d",&r2,&c2)!=2||(!r2&&!c2))return 0;
if(r2==R-DR&&c2==C-DC)printf("%d %d\n",R+2*DR,C+2*DC);else printf("%d %d\n",R-DR,C-DC);
fflush(stdout);scanf("%d %d",&r,&c);return 0;}
