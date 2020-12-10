#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

template<class T>
using vector_t = std::vector<T>;

template<class T>
using matrix_t = std::vector<vector_t<T>>;

template<class T>
bool is_more(const T& first, const T& second)
{
    return first > second;
}

template<class T>
bool is_less(const T& first, const T& second)
{
    return first < second;
}

template<class T>
bool is_sorted(const vector_t<T>& vector, const bool& asc)
{
    const auto sort = asc ? is_more<T> : is_less<T>;

    for (size_t i = 1; i < vector.size(); ++i)
    {
        if (sort(vector[i - 1], vector[i]))
        {
            return false;
        }
    }

    return true;
}

template<class T>
vector_t<T> BozoSort(const vector_t<T>& vector, const bool& asc)
{
    vector_t<T> result = vector;
    if (vector.size() < 2)
    {
        return result;
    }

    const size_t size = result.size();
    while (!is_sorted(result, asc))
    {
        std::swap(result[std::rand() % size], result[std::rand() % size]);
    }
    return result;
}

template<class T>
vector_t<T> BozoSort(const matrix_t<T>& matrix, const bool& asc)
{
    vector_t<T> result;
    for (const vector_t<T>& row : matrix)
    {
        for (const T& item : row)
        {
            result.push_back(item);
        }
    }

    return BozoSort(result, asc);
}

template<class T>
vector_t<T> BozoSort(const T& a, const T& b, const T& c, const bool& asc)
{
    vector_t<T> vector = { a, b, c };
    return BozoSort(vector, asc);
}

template<class T>
void print(const vector_t<T>& vector)
{
    for (size_t i = 0; i < vector.size() - 1; ++i)
    {
        std::cout << vector[i] << " ";
    }

    std::cout << vector[vector.size() - 1] << std::endl;
}

template<class T>
void execute()
{
    unsigned int n;
    std::cin >> n;

    matrix_t<T> matrix;
    vector_t<T> vector;
    vector_t<T> buffer;

    for (unsigned int i = 1; i <= n; ++i)
    {
        T value;
        std::cin >> value;

        buffer.push_back(value);
        vector.push_back(value);

        if (i % static_cast<unsigned int>(sqrt(n)) == 0)
        {
            matrix.push_back(buffer);
            buffer.clear();
        }
    }

    print(BozoSort(vector, true));
    print(BozoSort(vector, false));
    print(BozoSort(matrix, true));
    print(BozoSort(matrix, false));
    print(BozoSort(vector[0], vector[1], vector[2], true));
    print(BozoSort(vector[0], vector[1], vector[2], false));
}

int main()
{
    std::srand(time(nullptr));

    execute<double>();
    execute<std::string>();
}
