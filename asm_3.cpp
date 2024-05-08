#include <iostream>

using namespace std;

int main() {
    cout << "Find the product of cubes of all positive elements of the array.\n";
    int sz, of = 0, result = 0;
    cout << "Enter the size of the array: ";
    while (!(cin >> sz) || (cin.peek() != '\n') || (sz <= 0)) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Invalid value! Try again!" << '\n';
        cout << "Enter the size of the array: ";
    }
  
    int* array = new int[sz];
    for (int i = 0; i < sz; ++i) {
        cout << "Enter the " << i << " element of array: ";
        cin >> array[i];
    }
  
    _asm {
        mov ecx, sz                ; ecx = sz
        mov esi, array             ; esi = array - идентификатор (переменная) массива является указателем на его первый элемент
        xor eax, eax               ; eax = 0

        process_loop:
        mov ebx, [esi]             ; ebx = array[i]
        test ebx, ebx              ; ebx == 0
        jle skip_multiply
        mov edx, ebx               ; edx = [esi]
        imul edx, ebx              ; edx = [esi] * [esi]
        jo overflow
        imul edx, ebx              ; edx = [esi] * [esi] * [esi]
        jo overflow
        add eax, edx               ; eax += [esi] * [esi] * [esi]
        jo overflow

        skip_multiply:
            add esi, 4             ; Сдвиг указателя(увеличение указателя на размер элемента; т.к. int, то на 4 байта)
            loop process_loop

        jmp done

        overflow:
            mov of, 1              ; of = 1
            jmp done

        done:
            mov result, eax        ; res = eax
    }

    if (of) {
        cout << "Error! Overflow!\n";
    }
    else {
        cout << "Array: ";
        for (int i = 0; i < sz; ++i) {
            cout << array[i] << " ";
        }
        cout << "\nResult of calculations: " << result << '\n';
    }

    return 0;
}
