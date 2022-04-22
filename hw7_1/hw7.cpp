/*7_1. MSD для строк.
Дан массив строк. Количество строк не больше 105. Отсортировать массив методом поразрядной сортировки MSD по символам.
Размер алфавита - 256 символов. Последний символ строки = ‘\0’.*/

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cstring>

using std::string;

class ArrayOfString {
private:
    int size;
    int capacity;
    string *array;
public:
    ArrayOfString():array(nullptr), size(0), capacity(5){array = new string[capacity];};
    ArrayOfString(int capacity):capacity(capacity), size(0){array = new string[capacity];}
    ArrayOfString (ArrayOfString& copy);
    ~ArrayOfString();

    string operator[](int i);
    string *get(){return array;}
    int arSize(){return size;}

    void growSize();

    friend std::istream& operator >> (std::istream &in, ArrayOfString &array);
    friend std::ostream& operator << (std::ostream &out, ArrayOfString &array);
};

string ArrayOfString::operator[](int i) {
    return array[i];
}

void ArrayOfString::growSize() {
    ArrayOfString temp(size);
    for (int i = 0; i < size; ++i) {
        temp.array[i] = array[i];
    }
    delete[] array;
    capacity *= 2;
    array = new string[capacity];
    for (int i = 0; i < size; ++i) {
        array[i] = temp[i];
    }
}

std::istream& operator >> (std::istream &in, ArrayOfString &array) {
    int i = 0;
    while (in >> array.array[i]) {
        ++i;
        ++array.size;
        if (array.size == array.capacity) {
            array.growSize();
        }

    }

    return in;
}

std::ostream& operator << (std::ostream &out, ArrayOfString &array) {
    for (int i = 0; i < array.size; ++i) {
        out << array[i] << "\n";
    }
    return out;
}

ArrayOfString::~ArrayOfString() {
    delete[] array;
}

ArrayOfString::ArrayOfString(ArrayOfString &copy) {
    size = copy.size;
    capacity = copy.capacity;
    array = new string[capacity];
    for (int i = 0; i < copy.size; ++i) {
        array[i] = copy[i];
    }
}

void MSD(string *array, int j, int l, int r) {
    int size = r - l + 1;

    auto *alfavit = new int[256];

    memset(alfavit, 0, 256 * 4);

    for (int i = l; i <= r; ++i) {
        if (array[i][j] == '\0' ) {
            alfavit[0]++;
        } else {
            ++alfavit[(int) array[i][j]];
        }
    }

    for (int i = 1; i < 256; ++i) {
        alfavit[i] += alfavit[i - 1];
    }

    auto *sort = new string[size];

    for (int  i = r; i >= l; --i) {
        sort[--alfavit[array[i][j]]] = array[i];
    }

    delete[] alfavit;

    for (int i = l; i <= r; ++i) {
        array[i] = sort[i - l];
    }

    delete[] sort;

    for (int i = l; i <= r; ++i) {
        int count = 0;
        while (i < r && array[i][j] == array[i + 1][j] && array[i][j] != '\0') {
            ++count;
            ++i;
        }
        if (count != 0) {
            MSD(array, j + 1, i - count, i);
        }
    }

}

int run(std::istream& input, std::ostream& output) {
    ArrayOfString a;
    input >> a;

    MSD(a.get(), 0, 0, a.arSize() - 1);
    std::cout << a;

    return 0;
}

int test();

int main() {
//    test();
    run(std::cin, std::cout);
    return 0;

}

int test() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "ab\n"
                 "ae\n"
                 "aaa\n"
                 "a\n"
                 "a\n"
                 "abc\n"
                 "fsdf\n"
                 "csc\n"
                 "zx\n"
                 "aa\n"
                 "as\n"
                 "sadf\n";
        run(input, output);
//        assert(output.str() == "a\n"
//                               "a\n"
//                               "aa\n"
//                               "aa\n"
//                               "aaa\n"
//                               "ab\n"
//                               "abc\n"
//                               "csc\n"
//                               "fsdf\n"
//                               "zx\n");
    }
    return 0;
}