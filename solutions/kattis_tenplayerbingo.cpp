#include <bits/stdc++.h>
using namespace std;
int main() {
    int x = 0, last = 0;
    while (scanf("%d", &x) == 1) last = x;
    int p = last % 10; if (p == 0) p = 10;
    printf("%d\n", p);
}
