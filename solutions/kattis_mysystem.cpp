#include <bits/stdc++.h>
using namespace std;
int main(){random_device rd;mt19937_64 rng(rd()^(uint64_t)chrono::steady_clock::now().time_since_epoch().count());
int t;if(scanf("%d",&t)!=1)return 0;
while(t--){char prev='F';for(int i=0;i<200;i++){char g;if(i%2==0)g=(rng()&1)?'T':'F';else g=(prev=='T')?'F':'T';
printf("%c\n",g);fflush(stdout);char s[16];if(scanf("%15s",s)!=1)return 0;if(s[0]!='T'&&s[0]!='F')return 0;prev=s[0];}}
}
