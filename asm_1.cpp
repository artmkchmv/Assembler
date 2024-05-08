#include <iostream>

using namespace std;

int main() {
	cout << "(2 * c / a - 2 * c * b) / (b + 4 * a - 10)\n";
	int a, b, c;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "c = ";
	cin >> c;
	int numerator, denominator, res = 0;
	int zf = 0, of = 0;

	_asm {
		mov eax, a				    ; eax = a
		mov ebx, 4				    ; ebx = 4
		imul ebx				      ; eax = 4 * a
		jo overflow
		mov ebx, b				    ; ebx = b
		add eax, ebx			    ; eax = 4 * a + b
		jo overflow
		sub eax, 10				    ; eax = 4 * a + b - 10
		jo overflow
		test eax, eax         ; eax == 0
		jz division_by_zero

		mov denominator, eax	; denominator = 4 * a + b - 10

		mov eax, c				    ; eax = c
		mov ebx, 2				    ; ebx = 2
		imul ebx				      ; eax = 2 * c
		jo overflow
		mov ebx, a				    ; ebx = a
		test ebx, ebx         ; ebx == 0
		jz division_by_zero
		cdq                   ; eax -> edx:eax
		idiv ebx				      ; eax = 2 * c / a
		mov ebx, eax			    ; ebx = 2 * c / a
		mov eax, b				    ; eax = b
		mov ecx, c				    ; ecx = c
		imul ecx				      ; eax = b * c
		jo overflow
		mov ecx, 2				    ; ecx = 2
		imul ecx				      ; eax = 2 * b * c
		jo overflow
		sub ebx, eax			    ; ebx = 2 * c / a - 2 * b * c
		jo overflow
		mov numerator, ebx		; numerator = 2 * c / a - 2 * b * c

		mov eax, numerator		; eax = numerator
		mov ebx, denominator	; ebx = denominator
		cdq                   ; eax -> edx:eax
		idiv ebx				      ; eax = numerator / denominator

		mov res, eax			    ; res = numerator / denominator
		jmp done

		division_by_zero:
			mov zf, 1           ; zf = 1
			jmp done

		overflow:
			mov of, 1           ; of = 1
			jmp done

		done:
	}

	if (zf) {
		cout << "Error! Division by zero!" << endl;
	}
	else if (of) {
		cout << "Error! Overflow!" << endl;
	}
	else {
		cout << "Result of calculations: " << res << endl;
	}

	return 0;
}
