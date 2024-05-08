#include <iostream>

using namespace std;

double func(double a, double b, double c) {
    double result = 0;
    const double c2 = 2, c4 = 4, c10 = 10;
    _asm {
        finit                ; FPU initialization

        fld qword ptr[a]     ; st(0) = a
        fldz                 ; st(1) = a, st(0) = 0
        fucompp              ; st(0) ? st(1) 
        fstsw ax             ; swr -> ax
        sahf                 ; c3, c2, c0 (ah) -> zf, pf, cf (flags)
        jz division_by_zero

        fld qword ptr[b]     ; st(0) = b
        fld qword ptr[c4]    ; st(1) = b, st(0) = c4
        fld qword ptr[a]     ; st(2) = b, st(1) = c4, st(0) = a
        fmul                 ; st(1) = b, st(0) = c4 * a
        fadd                 ; st(0) = b + c4 * a
        fld qword ptr[c10]   ; st(1) = b + c4 * a, st(0) = c10
        fsub                 ; st(0) = b + c4 * a - c10
        fldz                 ; st(1) = b + c4 * a - c10, st(0) = 0
        fucompp              ; st(0) ? st(1)
        fstsw ax             ; swr->ax
        sahf                 ; c3, c2, c0 (ah) -> zf, pf, cf (flags)
        jz division_by_zero

        fld qword ptr[c]     ; st(0) = c
        fld qword ptr[c2]    ; st(1) = c2, st(0) = c
        fmul                 ; st(0) = c2 * c
        fld qword ptr[a]     ; st(1) = c2 * c, st(0) = a
        fdiv                 ; st(0) = c2 * c / a
        fld qword ptr[b]     ; st(1) = c2 * c / a, st(0) = b
        fld qword ptr[c]     ; st(2) = c2 * c / a, st(1) = b, st(0) = c
        fld qword ptr[c2]    ; st(3) = c2 * c / a, st(2) = b, st(1) = c, st(0) = c2
        fmul                 ; st(2) = c2 * c / a, st(1) = b, st(0) = c * c2
        fmul                 ; st(1) = c2 * c / a, st(0) = b * c * c2
        fsub                 ; st(0) = c2 * c / a - b * c * c2
        fld qword ptr[b]     ; st(1) = c2 * c / a - b * c * c2, st(0) = b
        fld qword ptr[c4]    ; st(2) = c2 * c / a - b * c * c2, st(1) = b, st(0) = c4
        fld qword ptr[a]     ; st(3) = c2 * c / a - b * c * c2, st(2) = b, st(1) = c4, st(0) = a
        fmul                 ; st(2) = c2 * c / a - b * c * c2, st(1) = b, st(0) = c4 * a
        fadd                 ; st(1) = c2 * c / a - b * c * c2, st(0) = b + c4 * a
        fld qword ptr[c10]   ; st(2) = c2 * c / a - b * c * c2, st(1) = b + c4 * a, st(0) = c10
        fsub                 ; st(1) = c2 * c / a - b * c * c2, st(0) = b + c4 * a - c10
        fdiv                 ; st(0) = (c2 * c / a - b * c * c2) / b + c4 * a - c10
        fstp result          ; result = st(0)
        jmp done

        division_by_zero:
            fldz             ; st(0) = 0
            fstp result      ; result = st(0)

        done:
    }
    return result;
}

int main() {
    cout << "(2 * c / a - 2 * c * b) / (b + 4 * a - 10)\n";
    double a, b, c;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;
    cout << "Result of calculations: " << func(a, b, c) << endl;
    return 0;
}
