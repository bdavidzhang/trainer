#include <bits/stdc++.h>
using namespace std;
int main(){static char buf[1100000];scanf("%s",buf);int L=strlen(buf);
 if(L<=10){long long v=atoll(buf),f=1;for(int n=1;;n++){f*=n;if(f==v){printf("%d\n",n);return 0;}}}
 long double s=0;for(int n=1;;n++){s+=log10l((long double)n);if((long long)floorl(s)+1>=L){printf("%d\n",n);return 0;}}}
