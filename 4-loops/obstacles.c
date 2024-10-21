#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int xa, ya, xb, yb, xc, yc;

int main() {
    scanf("%d %d %d %d %d %d", &xa, &ya, &xb, &yb, &xc, &yc);

    if (xa == xb && xb == xc) {
        if (ya <= yc && yc <= yb) {
            printf("%d\n", yb - ya + 2);
            printf("L");
            for (int i = 0; i < yb - ya; ++i) {
                printf("U");
            }
            printf("R");
        } else if (ya >= yc && yc >= yb) {
            printf("%d\n", ya - yb + 2);
            printf("L");
            for (int i = 0; i < ya - yb; ++i) {
                printf("D");
            }
            printf("R");
        } else {
            printf("%d\n", abs(yb - ya));
            if (ya <= yb) {
                for (int i = 0; i < abs(yb - ya); ++i) {
                    printf("U");
                }
            } else {
                for (int i = 0; i < abs(yb - ya); ++i) {
                    printf("D");
                }                
            }
        }
        return 0;
    } else if (ya == yb && yb == yc) {
        if (xa <= xc && xc <= xb) {
            printf("%d\n", xb - xa + 2);
            printf("U");
            for (int i = 0; i < xb - xa; ++i) {
                printf("R");
            }
            printf("D");
        } else if (xa >= xc && xc >= xb) {
            printf("%d\n", xa - xb + 2);
            printf("U");
            for (int i = 0; i < xa - xb; ++i) {
                printf("L");
            }
            printf("D");            
        } else {
            printf("%d\n", abs(xb - xa));
            if (xa <= xb) {
                for (int i = 0; i < abs(xb - xa); ++i) {
                    printf("R");
                }
            } else {
                for (int i = 0; i < abs(xb - xa); ++i) {
                    printf("L");
                }
            }
        }
        return 0;
    }

    printf("%d\n", abs(xa - xb) + abs(ya - yb));
    int f = 1;
    if (xa <= xb) {
        if (ya <= yb) {
            if (xa == xc && ya <= yc && yc <= yb) {
                printf("R");
                ++xa;
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("U");
                }
            } else if (yb == yc && xa <= xc && xc <= xb) {
                f = 0;
                for (int i = 0; i < abs(xa - xb); ++i) {
                    printf("R");
                }
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("U");
                }
            } else {
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("U");
                }
            }
        } else {
            if (xa == xc && ya >= yc && yc >= yb) {
                printf("R");
                ++xa;
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("D");
                }
            } else if (yb == yc && xa <= xc && xc <= xb) {
                f = 0;
                for (int i = 0; i < abs(xa - xb); ++i) {
                    printf("R");
                }
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("D");
                }
            } else {
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("D");
                }
            }            
        }
        if (f) {
            for (int i = 0; i < xb - xa; ++i) {
                printf("R");
            }
        }
    } else {
        if (ya <= yb) {
            if (xa == xc && ya <= yc && yc <= yb) {
                printf("L");
                --xa;
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("U");
                }
            } else if (yb == yc && xb <= xc && xc <= xa) {
                f = 0;
                for (int i = 0; i < abs(xa - xb); ++i) {
                    printf("L");
                }
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("U");
                }
            } else {
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("U");
                }
            }
        } else {
            if (xa == xc && ya >= yc && yc >= yb) {
                printf("L");
                --xa;
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("D");
                }
            } else if (yb == yc && xb <= xc && xc <= xa) {
                f = 0;
                for (int i = 0; i < abs(xa - xb); ++i) {
                    printf("L");
                }
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("D");
                }
            } else {
                for (int i = 0; i < abs(ya - yb); ++i) {
                    printf("D");
                }
            }            
        }
        if (f) {
            for (int i = 0; i < xa - xb; ++i) {
                printf("L");
            }
        }
    }
    return 0;
}