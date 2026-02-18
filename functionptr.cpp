#include <iostream>

template <typename T>
using PrintOp = void(*)(const T&);

template <typename T>
using CompareOp = bool(*)(const T&, const T&);

struct Point {
    int x = 0;
    int y = 0;
};

// ----------- ПРОТОТИПЫ -----------
// печать одного значения (шаблон + перегрузка для Point)
template <typename T>
void print_value(const T& v);

template <>
void print_value(const Point& p);

// печать массива
template <typename T>
void print_array(const T* arr, std::size_t size, PrintOp<T> printer);

// "нужно ли менять местами?" (шаблон + перегрузка для Point)
template <typename T>
bool compare_greater(const T& a, const T& b);

template <>
bool compare_greater(const Point& a, const Point& b);

/*

template <typename T>
bool compare_less (const T& a, const T& b);

template <>
bool compare_less (const Point& a, const Point& b);

*/


// сортировка пузырьком
template <typename T>
void bubble_sort(T* arr, std::size_t size, CompareOp<T> need_swap);


int main() {

    int arr[10]{1,2,3,4,5,6,7,9,8,10};
    print_array(arr, 10, &print_value<int>);

    double arrD[10]{1.67,2.89,3.11,4,5,6,7,8,9,10};
    print_array(arrD, 10, &print_value<double>);

    Point points[10]{
        {100,200}, {3,4}, {5,6}, {7,8}, {9,10},
        {11,12}, {13,14}, {15,16}, {17,18}, {19,20}
    };

    print_array(points, 10, &print_value<Point>);

    bubble_sort(arr, 10, &compare_greater<int>);
    print_array(arr, 10, &print_value<int>);

    bubble_sort(arrD, 10, &compare_greater<double>);
    print_array(arrD, 10, &print_value<double>);

    bubble_sort(points, 10, &compare_greater<Point>);
    print_array(points, 10, &print_value<Point>);

    return 0;
}

// ----------- ОПРЕДЕЛЕНИЯ -----------
// печать одного значения
template <typename T>
void print_value(const T& v) {
    std::cout << v << ' ';
}

// перегрузка для Point
template <>
void print_value(const Point& p) {
    std::cout << '(' << p.x << ", " << p.y << ") ";
}

// печать массива
template <typename T>
void print_array(const T* arr, std::size_t size, PrintOp<T> printer) {
    for (std::size_t i = 0; i < size; ++i) {
        printer(arr[i]);
    }
    std::cout << '\n';
}

// сравнение: "нужно ли менять местами?"
template <typename T>
bool compare_greater(const T& a, const T& b) {
    return a > b;
}

// перегрузка для Point (сортируем по x)
template <>
bool compare_greater(const Point& a, const Point& b) {
    return a.x > b.x;
}

// пузырьковая сортировка
template <typename T>
void bubble_sort(T* arr, std::size_t size, CompareOp<T> need_swap) {
    for (std::size_t i = 0; i + 1 < size; ++i) {
        bool swapped = false;

        for (std::size_t j = 0; j + 1 < size - i; ++j) {
            if (need_swap(arr[j], arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

