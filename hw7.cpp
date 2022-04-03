/*7_1. MSD для строк.
Дан массив строк. Количество строк не больше 105. Отсортировать массив методом поразрядной сортировки MSD по символам.
Размер алфавита - 256 символов. Последний символ строки = ‘\0’.*/

#include <iostream>
#include <sstream>
#include <string.h>
#include <cassert>

class ArrayOfString {
private:
    char **array;
    int size;
    int capacity;
public:
    ArrayOfString():array(NULL), size(0), capacity(0){};
    ~ArrayOfString();

    char *&operator[](int i);
    void resize(int newSize){capacity = newSize; delete[] array; array = new char*[capacity];}
    char** get(){return array;}
    int arSize(){return size;}

    void incCapacity();

    friend std::istream& operator >> (std::istream &in, ArrayOfString &array);
    friend std::ostream& operator << (std::ostream &out, ArrayOfString &array);
};

char*& ArrayOfString::operator[](int i) {
    return array[i];
}


std::istream& operator >> (std::istream &in, ArrayOfString &array) {
    array.resize(10);
    char buffer[100];
    int i = 0;
    while (in >> buffer) {
        if (array.size == array.capacity) {
            array.incCapacity();
        }

        array[i] = new char[strlen(buffer) + 1];
        memcpy(array[i], buffer, strlen(buffer) + 1);
        ++i;
        ++array.size;
    }

    return in;
}

std::ostream& operator << (std::ostream &out, ArrayOfString &array) {
    for (int i = 0; i < array.size; ++i) {
        out << array[i] << "\n";
    }
    return out;
}


void ArrayOfString::incCapacity()  {
    char **temp = new char*[size];
    for (int i = 0; i < size; ++i) {
        temp[i] = array[i];
    }
    delete[] array;
    array = new char*[size * 4];
    for (int i = 0; i < size; ++i) {
        array[i] = temp[i];
    }
    delete[] temp;
    capacity *= 4;
}

ArrayOfString::~ArrayOfString() {
    for (int i = 0; i < size; ++i) {
        delete[] array[i];
    }
    delete[] array;
}


void MSD(char **array, int j, int l,  int r) {
    int size = r - l + 1;
    char *alfavit = new char[256];

    memset(alfavit, 0, 256);

    for (int i = l; i <= r; ++i) {
        if (array[i][j] == '\0' ) {
            alfavit[0]++;
        } else {
            ++alfavit[(int) array[i][j]];
        }
    }

    for (int i = 0; i < 256; ++i) {
        alfavit[i] += alfavit[i - 1];
    }

    char **sortArray = new char*[size];
    memset(sortArray, 0, size);
    for (int  i = r; i >= l; --i) {
        sortArray[--alfavit[array[i][j]]] = new char[strlen(array[i]) + 1];
        memcpy(sortArray[(int)alfavit[array[i][j]]], array[i], strlen(array[i]) + 1);
    }
    delete[] alfavit;
    
    for (int i = 0; i < size; ++i) {
        array[i + l] = sortArray[i];
    }

//    for (int i = 0; i < size; i++){
//        delete[] sortArray[i];
//    }
    delete[] sortArray;
    int i = l;

    for (int i = l; i < r; ++i) {
        int count = 0;
        while (i < r && array[i][j] == array[i + 1][j]) {
            ++count;
            ++i;
        }
        if (count != 0) {
            MSD(array, j + 1, i - count, i );
        }
    }

}

int run(std::istream& input, std::ostream& output) {
    ArrayOfString a;
    input >> a;

    MSD(a.get(), 0, 0, a.arSize() - 1);
    output << a;


    return 0;
}

int test();

int main() {
    test();
//    run(std::cin, std::cout);
    return 0;

}

int test() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "ab\n"
                 "a\n"
                 "aaa\n"
                 "aa\n"
                 "a\n"
                 "abc\n"
                 "fsdf\n"
                 "csc\n"
                 "zx\n"
                 "aa\n";
        run(input, output);
        assert(output.str() == "a\n"
                               "a\n"
                               "aa\n"
                               "aa\n"
                               "aaa\n"
                               "ab\n"
                               "abc\n"
                               "csc\n"
                               "fsdf\n"
                               "zx\n");
    }
    return 0;
}