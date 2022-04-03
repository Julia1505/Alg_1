//  Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
//  Формат входных данных.
//  В первой строке количество команд n. n ≤ 1000000.
//  Каждая команда задаётся как 2 целых числа: a b.
//        a = 1 - push front
//        a = 2 - pop front
//        a = 3 - push back
//        a = 4 - pop back
//        Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
//  Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
//  Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
//  Формат выходных данных.
//  Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
//
//  3_2. Реализовать дек с динамическим зацикленным буфером.
//  Требования: Дек должен быть реализован в виде класса.


#include <iostream>
#include <cassert>
#include <sstream>

class Deque {
private:
    int *array;
    int head;
    int tail;
    int size;
    int capacity;

    void IncCapacity();

    void DecCapacity();

public:
    Deque();
    Deque(const Deque&) = delete;
    ~Deque();

    void PushFront(int elem);
    int PopFront();
    void PushBack(int elem);
    int PopBack();
    bool isEmpty() {return size == 0;}
    void Print();

};

Deque::Deque() {
    array = new int[3];
    head = 0;
    tail = 0;
    size = 0;
    capacity = 3;
}

Deque::~Deque() {
    delete[] array;
}

void Deque::PushFront(int elem) {
    if (size == 0) {
        array[head] = elem;
    } else {
        if (size == capacity) {
            IncCapacity();
        }

        if (head != 0) {
            array[--head] = elem;
        } else {
            head = capacity - 1;
            array[head] = elem;
        }
    }
    size++;
}

int Deque::PopFront() {

    int tempElem = array[head];
    if (head != tail) {
        if (head != capacity - 1) {
            ++head;
        } else {
            head = 0;
        }
    }

    --size;

    if (size < (capacity / 4)) {
        DecCapacity();
    }
    return tempElem;
}

void Deque::PushBack(int elem) {
    if (size == 0) {
        array[tail] = elem;
    } else {
        if (size == capacity) {
            IncCapacity();
        }

        if (tail != capacity - 1) {
            array[++tail] = elem;
        } else {
            tail = 0;
            array[tail] = elem;
        };
    }
    size++;
}

int Deque::PopBack() {

    int tempElem = array[tail];
    if (tail != head) {
        if (tail != 0) {
            --tail;
        } else {
            tail = capacity - 1;
        }
    }

    --size;

    if (size < (capacity / 4)) {
        DecCapacity();
    }
    return tempElem;
}

void Deque::IncCapacity() {
    int *temp_array = new int[capacity];
    if (temp_array == NULL) {
        assert(true);
    }

    for (int i = 0; i < size; ++i) {
        temp_array[i] = array[(i + head) % size];
    }
    delete[] array;
    array = new int[capacity * 2];
    if (array == NULL) {
        assert(true);
    }

    for (int i = 0; i < size; ++i) {
        array[i] = temp_array[i];
    }
    delete[] temp_array;
    head = 0;
    tail = size - 1;
    capacity *= 2;
}

void Deque::DecCapacity() {
    if (size == 0) {
        delete[] array;
        array = new int[3];
        capacity = 3;
        head = 0;
        tail = 0;
    } else {
        int *temp_array = new int[size];
        if (temp_array == NULL) {
            assert(true);
        }

        for (int i = 0; i < size; ++i) {
            temp_array[i] = array[(i + head) % capacity];
        }
        delete[] array;
        array = new int[capacity / 2];
        if (array == NULL) {
            assert(true);
        }

        for (int i = 0; i < size; ++i) {
            array[i] = temp_array[i];
        }
        delete[] temp_array;
        head = 0;
        tail = size - 1;
        capacity /= 2;
    }
}
//int run(std::istream& input, std::ostream& output);
//
//int testQueue() {
//    {
//        std::stringstream input;
//        std::stringstream output;
//        input << "0";
//        run(input, output);
//        assert(output.str() == "YES");
//    }
//
//    {
//        std::stringstream input;
//        std::stringstream output;
//        input << "8 2 -1 2 -1 4 -1 4 -1 1 1 1 1 2 1 2 1";
//        run(input, output);
//        assert(output.str() == "YES");
//    }
//
//    {
//        std::stringstream input;
//        std::stringstream output;
//        input << "7 1 1 3 1 2 1 4 1 4 -1 1 3 2 -1";
//        run(input, output);
//        assert(output.str() == "NO");
//    }
//
//    {
//        std::stringstream input;
//        std::stringstream output;
//        input << "17 1 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 4 1 4 2 4 3 4 4 4 5 4 6 4 7 4 8 2 -1";
//        run(input, output);
//        assert(output.str() == "YES");
//    }
//
//    {
//        std::stringstream input;
//        std::stringstream output;
//        input << "32 3 1 3 2 3 3 3 4 3 5 3 6 3 7 3 8 1 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 2 8 4 8 2 7 4 7 4 6 2 6 2 5 4 5 4 4 2 4 4 3 2 3 4 2 2 2 2 1 4 1 2 -1";
//        run(input, output);
//        assert(output.str() == "YES");
//    }
//
//    {
//        std::stringstream input;
//        std::stringstream output;
//        input << "8 1 1 4 1 1 2 4 2 1 3 4 3 1 4 4 4";
//        run(input, output);
//        assert(output.str() == "YES");
//    }
//    return 0;
//
//}

//void Deque::Print() {
//    for (int i = 0; i < size; ++i) {
//        std::cout << array[(head + i) % capacity] << " ";
//    }
//    std::cout << std::endl;
//}

int main() {
    int n = 0;
    std::cin >> n;
    Deque deq1;
    int a;
    int b;
    bool isTrue = true;

    for (int i = 0; i < n; ++i) {

        std::cin >> a >> b;
        switch (a) {
            case 1:
                deq1.PushFront(b);
                break;
            case 2:
                if (!deq1.isEmpty()) {
                    isTrue = isTrue && (deq1.PopFront() == b);
                } else {
                    isTrue = isTrue && b == -1;
                }
                break;
            case 3:
                deq1.PushBack(b);
                break;
            case 4:
                if (!deq1.isEmpty()) {
                    isTrue = isTrue && (deq1.PopBack() == b);
                } else {
                    isTrue = isTrue && b == -1;
                }
                break;
            default:
                assert(true);
        }
    }

    if (isTrue) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}
