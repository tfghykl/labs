#include <iostream>
bool is_correct(int&);
void input_random_array(int*, int);
void input_manualy(int*, int);
void input(int*, int);
void check_lenght(int&, int);
int find_max_abs_index(int*, int);
bool has_two_positives(int*, int);
bool has_positives_near(int*, int);
int count_sum_between_positives(int*, int);
void sort_by_trait(int*, int, int, int);
int count_same_in_array(int*, int, int);
int partition_by_trait(int*, int, int, int);
void sort_by_trait(int*, int, int, int);
bool sort_trait(int*, int, int, int);
void output_array(int*, int);
void normalize_array(int*, int);
void output_sum_between_first_two_positives(int*, int);

int main()
{
    const int MAX_SIZE = 100;
    try
    {
        int lenght{};
        int arr[MAX_SIZE]{};
        std::cout << "input size of an array\n";
        check_lenght(lenght, MAX_SIZE);
        input(arr, lenght);
        std::cout << "element with maximum absolute value is: " << arr[find_max_abs_index(arr, lenght)] << '\n';
        output_sum_between_first_two_positives(arr, lenght);
        sort_by_trait(arr, 0, lenght, lenght);
        normalize_array(arr, lenght);
        std::cout << "array sorted by rarity:\n";
        output_array(arr, lenght);
    }
    catch (const char* msg)
    {
        std::cout << msg;
    };
    return 0;
}
bool is_correct(int& number)
{
    return (std::cin >> number) ? true : false;
}
void check_boarders(int min, int max)
{
    if ((min > max) && (is_correct(min) && (is_correct(max))))
    {
        std::swap(min, max);
    }
}
void input_boarders(int& min, int& max)
{
    std::cout << "input maximum and minimum value:\n";
    std::cin >> min >> max;
    check_boarders(min, max);
}
void input_random_array(int* arr, int lenght)
{
    srand(time(NULL));
    int min, max;
    input_boarders(min, max);
    for (int i = 0; i != lenght; i++)
    {
        arr[i] = rand() % (max - min + 1) + min;
    }
}
void input_manualy(int* array, int lenght)
{
    std::cout << "input numbers manualy\n";
    for (int i = 0; i < lenght; ++i)
    {
        if (!is_correct(array[i])) std::cout << "invalid input";
    }
}
void input(int* arr, int lenght)
{
    std::cout << "how do you want to input numbers?\n1)manualy\n2)at random\n";
    int variant{};
    std::cin >> variant;
    if (variant == 1)
    {
        input_manualy(arr, lenght);
    }
    else if (variant == 2)
    {
        input_random_array(arr, lenght);
    }
    else
    { 
        throw "variant error\n";
    }
}
void check_lenght(int& lenght, int MAX_SIZE)
{
    if (!is_correct(lenght) || (lenght > MAX_SIZE || lenght < 1))
    {
        throw "invalid size\n";
    }
}
int find_max_abs_index(int* array, int lenght)
{
    int max_abs_index{};
    for (int i = 0; i != lenght; ++i)
    {
        if (abs(array[i]) > abs(array[max_abs_index]))
        {
            max_abs_index = i;
        }
    }
    return max_abs_index;
}
bool has_two_positives(int* array, int lenght)
{
    int counter{};
    for (int i = 0; i < lenght; ++i)
    {
        if (array[i] > 0)
        {
            counter++;
        }
    }
    return (counter > 1);
}
bool has_positives_near(int* array, int lenght)
{
    for (int i = 0; i < lenght; ++i)
    {
        if ((array[i] > 0) && (array[i + 1] > 0))
        {
            return 0;
            break;
        }
    }
    return 1;
}
int count_sum_between_positives(int* array, int lenght)
{
    int i{};
    int summ{};
    for (; i < lenght; ++i)
    {
        if (array[i] > 0)
        {
            ++i;
            break;
        }
    }
    while (array[i] < 0)
    {
        summ += array[i++];
    }
    return summ;
}
int count_same_in_array(int* array, int lenght, int number)
{
    int counter{};
    for (int i = 0; i < lenght; ++i)
    {
        if (number == array[i])
        {
            counter++;
        }
    }
    return counter;
}
int partition_by_trait(int* array, int low, int high, int lenght)
{
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (sort_trait(array, array[j], pivot, lenght))
        {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return (i + 1);
}
void sort_by_trait(int* array, int left, int right, int lenght)
{
    if (left < right)
    {
        int current_element = partition_by_trait(array, left, right, lenght);
        sort_by_trait(array, left, current_element - 1, lenght);
        sort_by_trait(array, current_element + 1, right, lenght);
    }
}
bool sort_trait(int* array, int a, int b, int lenght)
{
    return (count_same_in_array(array, lenght, a) >= count_same_in_array(array, lenght, b));
}
void output_array(int* array, int lenght)
{
    for (int i = 0; i != lenght; ++i)
    {
        std::cout << array[i] << ' ';
    }
}
void normalize_array(int* array, int lenght)
{
    int j{};
    for (int i = 0; i < lenght - 1; ++i)
    {
        j = i + 1;
        while (j < lenght)
        {
            if (array[j] == array[i])
            {
                std::swap(array[i + 1], array[j]);
                ++i;
            }
            ++j;
        }
    }
}
void output_sum_between_first_two_positives(int* array,int lenght)
{
    if (has_two_positives(array, lenght))
    {
        if (has_positives_near(array, lenght))
        {
            std::cout << "summ of elements between first two positives is " << count_sum_between_positives(array, lenght) << '\n';
        }
        else
        {
            std::cout << "there are no elements between first two positives\n";
        }
    }
    else
    {
        std::cout << "not enough positive elements\n";
    }
}