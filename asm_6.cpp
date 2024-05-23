// ctg((x + 5) ^ (x^2 + pi))
// ~-4.035 <= x <= ~-3.963 
#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.1415926535897931;

double func(double x) {
    const double c5 = 5;
    double res = 0;
    __asm {
        finit              ; FPU initialization
        fld qword ptr[x]   ; st(0) = x
        fld qword ptr[x]   ; st(1) = x, st(0) = x
        fmul               ; st(0) = x ^ 2
        fldpi              ; st(1) = x ^ 2, st(0) = pi
        fadd               ; st(0) = x ^ 2 + pi
        fld qword ptr[x]   ; st(1) = x ^ 2 + pi, st(0) = x
        fld qword ptr[c5]  ; st(2) = x ^ 2 + pi, st(1) = x, st(0) = 5
        fadd               ; st(1) = x ^ 2 + pi, st(0) = x + 5
        fyl2x              ; st(0) = (x ^ 2 + pi) * log_2(x + 5)
        f2xm1              ; st(0) = (x + 5) ^ (x ^ 2 + pi) - 1
        fld1               ; st(1) = (x + 5) ^ (x ^ 2 + pi) - 1, st(0) = 1
        fadd               ; st(0) = (x + 5) ^ (x ^ 2 + pi)
        fptan              ; st(1) = tg((x + 5) ^ (x ^ 2 + pi)), st(0) = 1
        fdiv st, st(1)     ; st(0) = ctg((x + 5) ^ (x ^ 2 + pi))
        fstp res           ; res = ctg((x + 5) ^ (x ^ 2 + pi))
    }
    return res;
}

int main() {
    cout << "ctg((x + 5) ^ (x^2 + pi))\n";
    cout << "x = ";
    double x;
    cin >> x;
    cout << "ASM Result: " << func(x) << '\n';
	cout << "C++ Result: " << 1 / tan(pow(x + 5, pow(x, 2) + PI)) << '\n';
	return 0;
}
