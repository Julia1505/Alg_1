//  1.2 Вернуть значение бита в числе N по его номеру K.
//  Формат входных данных. Число N, номер бита K

#include <iostream>
#include <cassert>

bool getBit(unsigned int number, short bitNumber) {
    assert(number >= 0 && bitNumber >= 0);
    return (number & ( 1 << bitNumber));
}

int main() {
    unsigned int N = 0;
    short K = 0;
    std::cin >> N >> K;
    std::cout << getBit(N, K);
    return 0;
}
