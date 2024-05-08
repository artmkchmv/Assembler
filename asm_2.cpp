#include <iostream>

using namespace std;

int main() {

	cout << "     { (a * a - 50) / (a + b) , a > b\n";
	cout << "X =  { -3a , a = b\n";
	cout << "     { (b * b - 2) / a , a < b\n";
	int a, b;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	int zf = 0, of = 0;
	int x;

	_asm {
		mov eax, a              ; eax = a
		test eax, eax           ; a == 0
		jz division_by_zero
		mov ebx, b              ; ebx = b
		mov ecx, -1             ; ecx = -1
		imul ecx                ; eax = -1 * a
		jo overflow
		cmp ebx, eax            ; ebx ? eax
		jz division_by_zero
		mov eax, a              ; eax = a
		cmp eax, ebx            ; eax ? ebx
		jg a_bigger_b           ; a > b
		jl a_smaller_b          ; a < b
		je a_equal_b            ; a = b
	
	a_bigger_b:
		mov eax, a            ; eax = a
		imul eax              ; eax = a * a
	    jo overflow
	    mov ebx, 50           ; ebx = 50
	    sub eax, ebx          ; eax = a * a - 50
	    jo overflow
	    mov ebx, a            ; ebx = a
	    mov ecx, b            ; ecx = b
	    add ebx, ecx          ; ebx = a + b
	    jo overflow
		cdq                   ; eax->edx:eax
	    idiv ebx              ; eax = (a * a - 50) / (a + b)
	    mov x, eax            ; x = (a * a - 50) / (a + b)
	    jmp done
	
	a_equal_b:
	  	mov eax, a            ; eax = a
	  	mov ebx, -3           ; ebx = -3
	  	imul ebx              ; eax = -3 * a
	  	jo overflow
	 	mov x, eax            ; x = -3 * a
	  	jmp done
	
	a_smaller_b:
	    mov eax, b            ; eax = b
	    imul eax              ; eax = b * b
	    jo overflow
	    mov ebx, 2            ; ebx = 2
	    sub eax, ebx          ; eax = b * b - 2
	    jo overflow
	    mov ebx, a            ; ebx = a
	    cdq                   ; eax->edx:eax
	    idiv ebx              ; eax = (b * b - 2) / a
	    mov x, eax            ; x = (b * b - 2) / a
	    jmp done
	
	division_by_zero:
	    mov zf, 1             ; zf = 1
	    jmp done
	
	overflow:
	    mov of, 1             ; of = 1
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
		cout << "Result of calculations: " << x << endl;
	}

	return 0;
}
