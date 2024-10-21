#include <stdio.h>

int val;

int main() {
    scanf("%d", &val);
    int x = val / 50, 
        y = (val - 50 * x) / 20,
        z = (val - 50 * x - 20 * y) / 10,
        t = (val - 50 * x - 20 * y - 10 * z) / 5,
        w = (val - 50 * x - 20 * y - 10 * z - 5 * t);
        
    printf("%d\n%d\n%d\n%d\n%d", x, y, z, t, w);
    return 0;
}