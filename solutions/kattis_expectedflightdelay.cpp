#include <bits/stdc++.h>
using namespace std;
int main(){int d,pw,pe,imp;cin>>d>>pw>>pe>>imp;const char*nm[]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
int m=d-1;long double fail=1;int cur=m;
for(int i=1;;i++){cur=(cur+6)%7;int p=(cur==0||cur==6)?pe:pw;fail*=(100-p)/100.0L;
 if((1-fail)*100>=imp){printf("Try to leave on %s, %d %s before the %s meeting.\n",nm[cur],i,i==1?"day":"days",nm[m]);return 0;}}
}
