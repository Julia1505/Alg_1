/*4.2 Топ K пользователей из лога
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт,
и выводит их в порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
Требования: время работы O(N * logK), где N - кол-во пользователей. Ограничение на размер кучи O(K).
Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости*/

#include <iostream>
#include <sstream>

template <class T>
bool compDefault(const T& l, const T& r) {
    return l > r;
}

template<class T, class Compare>
class Heap {
public:
    Heap(Compare cmp);
    Heap(const Heap&) = delete;
    ~Heap();

    Heap<T,Compare>& operator=(const Heap& l);

    Heap(T *arr, int size, Compare cmp);

    T PopMin();

    const T &PeekMin() const;

    void Insert(const T &el);

    void Print();

private:
    T *buffer;
    int size;
    int bufferSize;
    Compare cmp;

    void siftDown(int i);
};

template<class T, class Compare>
Heap<T, Compare>::Heap(Compare cmp): size(0), bufferSize(0), cmp(cmp) {}

template<class T, class Compare>
Heap<T, Compare>::Heap(T *arr, int size, Compare cmp): cmp(cmp), size(size), bufferSize(size){
    buffer = new T[size];
    for (int i = 0; i < size; i++) {
        buffer[i] = arr[i];
    }
    for (int i = size / 2 - 1; i >= 0; --i) {
        siftDown(i);
    }
}

template <class T>
void swap(T& l, T& r) {
    T temp = l;
    l = r;
    r = temp;
}

template<class T, class Compare>
void Heap<T, Compare>::siftDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    while (left < size || right < size) {
        int min = i;
        if (left < size && cmp(buffer[left], buffer[i])) {
            min = left;
        }
        if (right < size && cmp(buffer[right], buffer[min])) {
            min = right;
        }
        if (min == i ) {
            return;
        }
        swap(buffer[i], buffer[min]);
        i = min;
        left = 2 * i + 1;
        right = 2 * i + 2;
    }
}

template<class T, class Compare>
const T &Heap<T, Compare>::PeekMin() const {
    return buffer[0];
}

template<class T, class Compare>
void Heap<T, Compare>::Print() {
    for (int i = 0; i < size; ++i) {
        std::cout << buffer[i] << "\n";
    }
}

template<class T, class Compare>
void Heap<T, Compare>::Insert(const T &el) {
    buffer[0] = el;
    siftDown(0);
}

template<class T, class Compare>
T Heap<T, Compare>::PopMin() {
    T temp = buffer[0];
    swap(buffer[0], buffer[size - 1]);
    size--;
    siftDown(0);
    return temp;
}

template<class T, class Compare>
Heap<T, Compare>::~Heap() {
    delete[] buffer;
}

template<class T, class Compare>
Heap<T,Compare>& Heap<T, Compare>::operator=(const Heap& l) {
    if (bufferSize != 0) {
        delete[] buffer;
    }
    bufferSize = l.bufferSize;
    size = l.size;
    for (int i = 0; i < size; ++i) {
        buffer[i] = l.buffer[i];
    }
    return *this;
}

struct User {
    int Id;
    int Count;
};

std::ostream& operator <<(std::ostream &out, const User &user) {
    return out << user.Id;
}

bool CompUser(const User& l, const User& r) {
    return l.Count < r.Count;
}

int run(std::istream &input, std::ostream &output) {
    int N = 0;
    int K = 0;
    input >> N >> K;
    User *logFile = new User[N];
    for (int i = 0; i < N; ++i) {
        input >> logFile[i].Id >> logFile[i].Count;
    }
    Heap<User, bool (*) (const User&, const User&)> HeapTop(logFile, K, CompUser);
//    HeapTop.Print();
    for (int i = K; i < N; ++i) {
        if (CompUser(HeapTop.PeekMin(), logFile[i])) {
            HeapTop.Insert(logFile[i]);
        }
    }

//    HeapTop.Print();
//    output << "\n";
    for (int i = 0; i < K; ++i) {
        output << HeapTop.PopMin() << " ";
    }

    delete[] logFile;
    return 0;
}

int main() {
    run(std::cin, std::cout);
    return 0;
}