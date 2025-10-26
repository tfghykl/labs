#include <iostream>
#include <cstdint>
#include <random>
#include <ctime>
void allocate_matrix(int32_t**&, int32_t);
void clear_matrix(int32_t, int32_t**&);
void input_sqare_matrix(int32_t**&, int32_t);
void check_size(int32_t&);
void is_number(int32_t&);
void create_sqare_matrix(int32_t**&, int32_t&);
void allocate_array(int32_t*&, int32_t);
void input(int32_t**&, int32_t);
void input_borders(int32_t&, int32_t&);
void input_sqare_matrix_at_random_old(int32_t**&, int32_t);
void input_sqare_matrix_at_random_new(int32_t**&, int32_t);
void find_first_positive_column(int32_t**, int32_t);
void output_matix_in_spyral(int32_t**, int32_t);
int main()
{
    try
    {
        int32_t size_of_side{};
        int32_t** matrix{};
        int32_t* array{};
        create_sqare_matrix(matrix, size_of_side);
        find_first_positive_column(matrix, size_of_side);
        output_matix_in_spyral(matrix, size_of_side);

    }
    catch (const char* msg)
    {
        std::cout << msg;
    };
    return 0;
}
void is_number(int32_t& number)
{
    if (!(std::cin >> number))
    {
        throw "ERROR: not a number";
    }
}
void allocate_sqare_matrix(int32_t**& matrix, int32_t size)
{
    matrix = new int32_t* [size]{};
    for (int32_t i{}; i < size; i++)
    {
        matrix[i] = new int32_t[size]{};
    }
}
void clear_matrix(int32_t size, int32_t** matrix)
    {
        for (int32_t i{}; i < size; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
void check_size(int32_t& number)
    {
        is_number(number);
        if (number < 0)
        {
            throw "ERROR: negative matrix size";
        } else if (number < 3)
        {
            throw "ERROR: matrix is too small";
        } else if (number > 101)
        {
            throw "ERROR: matrix is too large";
        }
    }
void is_odd(int32_t size)
    {
        if ((size % 2) == 0)
        {
            throw "ERROR: odd size of side";
        }
    }
void input_sqare_matrix_manualy(int32_t**& matrix, int32_t size)
    {
        std::cout << "input matrix elements\n";
        for (int32_t i = 0; i < size; ++i)
        {
            for (int32_t j = 0; j < size; ++j)
            {
                is_number(matrix[i][j]);
            }
        }
    }
void allocate_array(int32_t*& array, int32_t lenght)
    {
        array = new int32_t[lenght * lenght];
    }
void create_sqare_matrix(int32_t**& matrix, int32_t& size_of_side)
    {
        std::cout << "input sqare matrix size of side (odd number)\n";
        check_size(size_of_side);
        is_odd(size_of_side);
        allocate_sqare_matrix(matrix, size_of_side);
        input(matrix, size_of_side);
    }
void input(int32_t**& matrix, int32_t size_of_side)
    {
        int32_t variant{};
        std::cout << "how do you want to input matrix: \n1) manualy\n2) at random (old way)\n3) at random(new way)\n";
        is_number(variant);
        switch (variant)
        {
        case 1:
        {
            input_sqare_matrix_manualy(matrix ,size_of_side);
            break;
        }
        case 2:
        {
            input_sqare_matrix_at_random_old(matrix, size_of_side);
            break;
        }
        case 3:
        {
            input_sqare_matrix_at_random_new(matrix, size_of_side);
            break;
        }
        default:
            throw "ERROR: invalid variant";
            break;
        }

    }
void input_sqare_matrix_at_random_old(int32_t**& matrix, int32_t size_of_side)
    {
        int32_t max{};
        int32_t min{};
        input_borders(min, max);
        for (int32_t i = 0; i < size_of_side; ++i)
        {
            for (int32_t j = 0; j < size_of_side; ++j)
            {
                matrix[i][j] = (min + rand() % (max - min + 1));
            }
        }
    }
void input_sqare_matrix_at_random_new(int32_t**& matrix, int32_t size_of_side)
    {
        int32_t max{};
        int32_t min{};
        input_borders(min, max);
        std::mt19937 gen(time(0));
        std::uniform_int_distribution<> distrib(min, max);
        for (int32_t i = 0; i < size_of_side; ++i)
        {
            for (int32_t j = 0; j < size_of_side; ++j)
            {
                matrix[i][j] = distrib(gen);
            }
        }
    }
void input_borders(int32_t& min, int32_t& max)
    {
        std::cout << "input minimum and maximum value\n";
        is_number(min);
        is_number(max);
        if (min > max)
        {
            std::swap(min, max);
        }  
    }
void find_first_positive_column(int32_t** matrix, int32_t size_of_side)
{
    for (int i{}; i < size_of_side; ++i)
    {
        for (int j{}; j < size_of_side; ++j)
        {
            if (matrix[i][j] >= 0)
            {
                if (j == size_of_side - 1)
                {
                    std::cout << "first positive column index is " << i << '\n';
                    return;
                }
            }   
            else
            {
                break;
            }
        }
    }
    std::cout << "there are no positive columns\n";

}
void output_matix_in_spyral(int32_t** matrix, int32_t size_of_side)
{
    int32_t speed{ 1 };
    int32_t start_pos{ (size_of_side -1)  / 2 };
    int32_t i{ start_pos };
    int32_t j{ start_pos };
    std::cout << matrix[i][j] << ' ';
    while (i >= 0 && j >= 0 && i < size_of_side && j < size_of_side)
    {
        for (int32_t k = 0; k < speed; ++k)
        {
            if (i > 0)
            {
                std::cout << matrix[--i][j] << ' ';
            }
            else return;
        }
        for (int32_t k = 0; k < speed; ++k)
        {
            if (j > 0)
            {
                std::cout << matrix[i][--j] << ' ';
            }
            else return;
        }
        speed++;
        for (int32_t k = 0; k < speed; ++k)
        {
            if (i + 1 < size_of_side)
            {
                std::cout << matrix[++i][j] << ' ';
            }
            else return;
        }
        for (int32_t k = 0; k < speed; ++k)
        {
            if (j + 1 < size_of_side)
            {
                std::cout << matrix[i][++j] << ' ';
            }
            else return;
        }
        speed++;
    }
}
// Тестовый пример ввода:
/*
    13 12 11 10 25
    14 03 02 09 24
    15 04 01 08 23
    16 05 06 07 22
    17 18 19 20 21 
*/
    