#include <iostream>

using namespace std;

double func(double a, double b) {
    double result;
    const double c50 = 50, c3 = -3, c2 = 2;
    
    _asm {
        finit                   ; FPU initialization
    
        fld qword ptr[a]        ; st(0)	= a
        fldz                    ; st(1) = a, st(0) = 0
        fucompp                 ; st(0) ? st(1)
        fstsw ax                ; swr -> ax
        sahf                    ; c3, c2, c0 (ah) -> zf, pf, cf (flags)
        jz division_by_zero
    
        fld qword ptr[a]        ; st(0) = a
        fld qword ptr[b]        ; st(1) = b, st(0) = a
        fadd                    ; st(0) = a + b
        fldz                    ; st(1) = a + b, st(0) = 0
        fucompp                 ; st(0) ? st(1)
        fstsw ax                ; swr -> ax
        sahf                    ; c3, c2, c0 (ah) -> zf, pf, cf (flags)
        jz division_by_zero
    
        fld qword ptr[b]        ; st(0) = b
        fld qword ptr[a]        ; st(1) = b, st(0) = a
        fucompp                 ; st(0) ? st(1)
        fstsw ax                ; swr -> ax
        sahf                    ; c3, c2, c0 (ah) -> zf, pf, cf (flags)

        ja a_bigger_b           ; a > b
        jb a_smaller_b          ; a < b

        fld qword ptr[a]        ; st(0) = a
        fld c3                  ; st(1) = a, st(0) = -3
        fmul                    ; st(0) = -3 * a
        fstp result             ; result = st(0) = -3 * a
        jmp done

        a_bigger_b:
            fld qword ptr[a]    ; st(0) = a
            fld qword ptr[a]    ; st(1) = a, st(0) = a
            fmul                ; st(0) = a * a
            fld c50             ; st(1) = a * a, st(0) = 50
            fsub                ; st(0) = a * a - 50
            fld qword ptr[a]    ; st(1) = a * a - 50, st(0) = a
            fld qword ptr[b]    ; st(2) = a * a - 50, st(1) = a, st(0) = b
            fadd                ; st(1) = a * a - 50, st(0) = a + b
            fdiv                ; st(0) = (a * a - 50) / (a + b)
            fstp result         ; result = st(0) = (a * a - 50) / (a + b)
            jmp done

        a_smaller_b:
            fld qword ptr[b]    ; st(0) = b
            fld qword ptr[b]    ; st(1) = b, st(0) = b
            fmul                ; st(0) = b * b
            fld c2              ; st(1) = b * b, st(0) = 2
            fsub                ; st(0) = b * b - 2
            fld qword ptr[a]    ; st(1) = b * b - 2, st(0) = a
            fdiv                ; st(0) = (b * b - 2) / a
            fstp result         ; result = st(0) = (b * b - 2) / a
            jmp done

        division_by_zero:
            fldz                ; st(0) = 0
            fstp result         ; result = st(0)

        done:
    }

    return result;
}

int main() {
    cout << "     { (a * a - 50) / (a + b) , a > b\n";
    cout << "X =  { -3a , a = b\n";
    cout << "     { (b * b - 2) / a , a < b\n";
    double a, b;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "Result of calculations: " << func(a, b) << endl;
    return 0;
}
