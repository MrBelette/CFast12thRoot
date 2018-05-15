/*
* Copyright (c) 2018 Mike Parker. All rights reserved.
* Licensed under the MIT (Expat) License.
* See accompanying LICENSE file in project root for full license information.
*/

#include "fast12throot.h"

double fast12throot(double x) {

    static const double PP0 = -0.35405850406413902;
    static const double PP1 = -9.7833971892115805;
    static const double PP2 = -42.631025673407322;
    static const double PP3 = -18.537498496277639;
    static const double PP4 = 47.865188330720699;
    static const double PP5 = 22.716858532042611;
    static const double PP6 = 0.74348566716915454;
    static const double PP7 = -0.019552666971785069;

    //static const double QQ0 = 1.0;
    static const double QQ1 = 45.670990855589217;
    static const double QQ2 = 369.28185751904067;
    static const double QQ3 = 834.07884364001461;
    static const double QQ4 = 563.7758264531883;
    static const double QQ5 = 90.726249041583387;

    static const double scale12thrthi[12] = {1.0,0.94387431268169353,0.89089871814033927,0.8408964152537145,0.79370052598409979,0.74915353843834076,0.70710678118654757,0.66741992708501718,0.6299605249474366,0.59460355750136051,0.56123102415468651,0.52973154717964765};
    static const double scale12thrtlo[12] = {0.0,-3.1406841003741325e-17,3.0632750829804785e-17,4.0995050102907483e-17,-5.4345040970989115e-17,-1.0908524678974539e-17,-4.8336466567264567e-17,-1.4832693484307519e-18,-1.2949666876502535e-17,1.9910076157328231e-17,-1.7892535584267786e-17,-2.2640640009996703e-17};

    double m=0.0, fhi;

    int64_t idx=0, k, r, ex2, me;
    u_int64_t ex;

    union {
        double value;
        u_int64_t bits;
    } u, poly;

    // should throw a domain error on -ve values of x
    if (x<=0.0) return 0.0;


    u.value = x;

    ex = (u.bits & ~0x8000000000000000);
    if (ex >= 0x7ff0000000000000) return x; //NaN or Inf
    k = (int64_t)(ex>>52);

    if (k == 0) { // x is subnormal
        if (ex == 0) return x;
        me = __builtin_clzl(ex) - 11; //leading_zeros(xs) - 11
        ex <<= (u_int64_t)me;
        u.bits = ex | (u.bits & 0x8000000000000000);
        k = 1 - me;
    }

    k -= 1022;
    u.bits = (u.bits & 0x800fffffffffffff) | 0x3fe0000000000000;
    m = u.value;

    r = k%12;
    if (r>0) r-=12;

    ex2 = (k-r)/12;

    idx = -r;

    poly.value = ((m*(PP1+m*(PP2+m*(PP3+m*(PP4+m*(PP5+m*(PP6+m*PP7)))))) ) + PP0) / ((m*(QQ1+m*(QQ2+m*(QQ3+m*(QQ4+m*(QQ5))))) ) + 1.0);

    fhi = scale12thrthi[idx];
    poly.value = ((poly.value*fhi) + scale12thrtlo[idx]) + fhi;

    ex = poly.bits & 0x7fffffffffffffff;
    k = (int64_t)(ex >> 52);
    k += ex2;
    poly.bits = (poly.bits & ~0x7ff0000000000000) | (k << 52);

    return poly.value;
}
