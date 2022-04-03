/*5_2. Современники.
Группа людей называется современниками если был такой момент, когда они могли собраться вместе.
Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников.
 В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
Замечание.
 Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.*/

#include <iostream>
#include <sstream>
#include <cassert>

struct Date {
    int year;
    int month;
    int day;
    bool isAlive;
    Date& operator=(const Date&);
};

Date& Date::operator=(const Date &r) {
    day = r.day;
    month = r.month;
    year = r.year;
    isAlive = r.isAlive;
    return *this;
}

bool operator==(const Date& l, const Date& r) {
    return (l.year == r.year && l.month == r.month && l.day == r.day);
}

template <class T>
void swap(T &firstElem, T &secondElem) {
    T temp = firstElem;
    firstElem = secondElem;
    secondElem = temp;
}

bool compDates(const Date& l, const Date& r) {
    if ((l.year > r.year) || (l.year == r.year && l.month > r.month) ||
    (l.year == r.year && l.month == r.month && l.day > r.day) || (l == r && l.isAlive > r.isAlive)) {
        return true;
    }
    return false;
}

template <class T>
bool compDefault(const T& l, const T& r) {
    return l > r;
}

template <class T>
void merge(T array[], int l1, int r1, int l2, int r2, bool (*comp)(const T&, const T&) = compDefault) {
    T *temp = new T[r2 - l1 + 1];
    int i = 0;
    int start = l1;
    while (l1 <= r1 && l2 <= r2) {
        if (comp(array[l2], array[l1])) {
            temp[i] = array[l1];
            ++l1;
        } else {
            temp[i] = array[l2];
            ++l2;
        }
        ++i;
    }
    while (l1 <= r1) {
        temp[i] = array[l1];
        ++l1;
        ++i;
    }
    while (l2 <= r2) {
        temp[i] = array[l2];
        ++l2;
        ++i;
    }
    for (int i = start, j = 0; i < r2 + 1; ++i, ++j) {
        array[i] = temp[j];
    }
    delete[] temp;
}

template <class T>
void MergeSort(T array[], int l, int r, bool (*comp)(const T&, const T&) = compDefault) {
    for (int i = l; i < r; i += 2) {
        if (comp(array[i], array[i + 1])) {
            swap(array[i], array[i + 1]);
        }
    }
    int part = 2;
    while (part < r - l + 1) {
        for (int i = l; i < r; i += part * 2) {
            int right = i + part * 2 - 1;
            if (right > r - l) {
                right = r - l;
            }
            merge(array, i, i + part - 1, i + part, right, comp);
        }
        part *= 2;
    }
}

void printDate(Date date) {
    std::cout << date.day << " " << date.month << " " << date.year << " " << date.isAlive << "\n";
}

bool isDeadBefore(Date &bornDate, Date &deadDate) {
    if (deadDate.year - bornDate.year >= 80) {
        deadDate.year = bornDate.year + 80;
        deadDate.month = bornDate.month;
        deadDate.day = bornDate.day;
    }
    bornDate.year += 18;
    if (deadDate.year - bornDate.year < 0) {
        return true;
    } else if (deadDate == bornDate) {
        return true;
    }
    return false;
}

void readDate(Date *arrayDate, std::istream& input) {
    input >> arrayDate->day >> arrayDate->month >> arrayDate->year;
    arrayDate->isAlive = true;
    input >> (arrayDate + 1)->day >> (arrayDate + 1)->month >> (arrayDate + 1)->year;
    (arrayDate + 1)->isAlive = false;
}

int run(std::istream& input, std::ostream& output);

int test() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 1 1 1920 2 2 1930  2 12 1930 2 9 1945 3 3 1925 2 3 1930";
        run(input, output);
        assert(output.str() == "0");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "4  2 12 2000 2 9 2030 3 3 1950 2 3 1970 1 1 1920 2 2 1950 4 5 2031 5 5 2060";
        run(input, output);
        assert(output.str() == "1");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "3 1 1 1900 2 2 2000 2 2 1980 2 3 2020 2 12 1850 1 1 1918";
        run(input, output);
        assert(output.str() == "1");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "3 2 1 1920 2 1 2000 2 5 1980 13 11 2055 1 1 1982 1 1 2030 ";
        run(input, output);
        assert(output.str() == "3");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "8  1 1 1900 1 1 1917 1 1 1910 1 1 1970 2 1 1870 2 1 1890 1 1 1810 1 1 1820 1 1 1800 1 1 1850 1 1 1900 1 1 2000 1 1 1920 1 1 2000  1 1 1810 1 1 1860";
        run(input, output);
        assert(output.str() == "3");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "9 14 03 1911\n"
                 "17 08 1851\n"
                 "04 10 1948\n"
                 "01 11 1989\n"
                 "13 12 1901\n"
                 "06 07 1859\n"
                 "07 10 1878\n"
                 "04 02 1801\n"
                 "09 12 1807\n"
                 "01 06 1941\n"
                 "28 01 1826\n"
                 "03 09 2022\n"
                 "06 03 1988\n"
                 "30 09 1883\n"
                 "09 08 2029\n"
                 "10 12 1972\n"
                 "21 08 2014\n"
                 "18 01 1998";
        run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input <<
                 "10 04 1920\n"
                 "11 16 04 1962\n"
                 "22 01 1865\n"
                 "23 09 1964\n"
                 "19 03 1965\n"
                 "29 09 2019\n"
                 "04 09 1959\n"
                 "03 12 2000\n"
                 "21 06 1846\n"
                 "28 05 1997\n"
                 "13 05 1814\n"
                 "28 10 1984\n"
                 "24 08 1902\n"
                 "20 06 1994\n"
                 "21 12 1842\n"
                 "23 06 1994\n"
                 "15 10 1880\n"
                 "25 02 2012\n"
                 "22 12 1995\n"
                 "02 02 2042\n"
                 "12 05 1860\n"
                 "03 02 1965";
        run(input, output);
        assert(output.str() == "5");
    }

    return 0;
}

int run(std::istream& input, std::ostream& output) {
    int N = 0;
    input >> N;
    assert(N > 0);
    Date *arrayDate = new Date[N * 2];
    Date *tempDate = new Date[2];
    for (int i = 0; i < N * 2; i += 2) {
        readDate(tempDate, input);
        if (isDeadBefore(tempDate[0], tempDate[1])) {
            N--;
            i -= 2;
        } else {
            arrayDate[i] = tempDate[0];
            arrayDate[i + 1] = tempDate[1];
        }
    }
    delete[] tempDate;
//    for (int i = 0; i < N * 2; ++i) {
//        printDate(arrayDate[i]);
//    }
    if (N > 1) {
        MergeSort(arrayDate, 0, N * 2 - 1, compDates);
    } else {
        delete[] arrayDate;
        output << N;
        return 0;
    }
    int count = 0;
    int maxCount = 0;
    for (int i = 0; i < N * 2; ++i) {
        if (arrayDate[i].isAlive) {
            count++;
        } else {
            count--;
        }
        if (count > maxCount) {
            maxCount = count;
        }
    }
    output << maxCount;
//    for (int i = 0; i < N * 2; ++i) {
//        printDate(arrayDate[i]);
//    }
    delete[] arrayDate;
    return 0;
}

int main() {
//    test();
    run(std::cin, std::cout);
//    int N;
//    std::cin >> N;
//    int *arr = new int[N];
//    for ( int i = 0; i < N; ++i) {
//        std::cin >> arr[i];
//    }
//    MergeSort(arr, 0, N - 1);
//    for ( int i = 0; i < N; ++i) {
//        std::cout << arr[i] << " ";
//    }

    return 0;
}