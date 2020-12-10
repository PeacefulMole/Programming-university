#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <cmath>

using vector_t = std::vector<int>;
using matrix_t = std::vector<vector_t>;

bool is_more(const int& first, const int& second)
{
    return first > second;
}

bool is_less(const int& first, const int& second)
{
    return first < second;
}

bool is_sorted(const vector_t& vector, const bool& asc)
{
    const auto sort = asc ? is_more : is_less;

    for (size_t i = 1; i < vector.size(); ++i)
    {
        if (sort(vector[i - 1], vector[i]))
        {
            return false;
        }
    }

    return true;
}

vector_t BozoSort(const vector_t& vector, const bool& asc)
{
    vector_t result = vector;
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

vector_t BozoSort(const matrix_t& matrix, const bool& asc)
{
    vector_t result;
    for (const vector_t& row : matrix)
    {
        for (int item : row)
        {
            result.push_back(item);
        }
    }

    return BozoSort(result, asc);
}

vector_t BozoSort(const int& a, const int& b, const int& c, const bool& asc)
{
    return BozoSort({ a, b, c }, asc);
}

void print(const vector_t& vector)
{
    for (size_t i = 0; i < vector.size() - 1; ++i)
    {
        std::cout << vector[i] << " ";
    }

    std::cout << vector[vector.size() - 1] << std::endl;
}

int main()
{
    std::srand(time(nullptr));

    int n;
    std::cin >> n;
    matrix_t matrix;
    vector_t vector;
    vector_t buffer;
    for (int i = 1; i <= n; ++i)
    {
        int num;
        std::cin >> num;
        buffer.push_back(num);
        vector.push_back(num);
        if (i % static_cast<int>(sqrt(n)) == 0)
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
