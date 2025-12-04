#include <iostream>
#include <cmath>
#include <iomanip>
#include <array>
using function = long double(*)(long double);
using method = long double(*)(long double, long double, long double(*)(long double));
long double count_integral(double, double, long double, function, method);
void check_if_positive(long double);
long double function_1(long double);
long double function_2(long double);
long double function_3(long double);
long double count_trap_area(long double, long double, function);
long double count_left_rectangle_area(long double, long double, function);
long double count_right_rectangle_area(long double, long double, function);
long double count_mid_rectangle_area(long double, long double, function);
long double count_simpson_area(long double, long double, function);
void input_number(int32_t&);
void input_number(long double&);
void input_borders(long double&,long double&);
long double eps_to_num(int32_t); 
long double input_eps(int32_t);
void choice_of_function(int32_t&);
void choice_of_method(int32_t&);
int main()
{
    try
    {
        int32_t eps_power{};
        long double left{};
        long double right{};
        std::array<function, 3> functions{ function_1, function_2, function_3 };
        std::array<method, 5> methods{ count_trap_area, count_left_rectangle_area, count_mid_rectangle_area, count_right_rectangle_area , count_simpson_area };
        long double eps = input_eps(eps_power);
        input_borders(left, right);
        int32_t function{};
        int32_t method{};
        choice_of_function(function);
        choice_of_method(method);
        std::cout << count_integral(left, right, eps, functions[function - 1], methods[method - 1]);
    }
    catch (const char* message)
    {
        std::cout << message;
    }
}
long double count_integral(double left, double right, long double eps, function function, method method)
{
    long double sum{};
    long double prev_sum{};
    size_t parts{ 4 };
    while (true)
    {
        for (size_t i{}; i < parts; ++i)
        {
            sum += method((left + ((right - left) / parts) * i), left + ((right - left) / parts) * (i + 1), function);
        }
        if (abs(prev_sum - sum) <= eps)
        {
            return sum;
        }
        else
        {
            parts *= 2;
            prev_sum = sum;
            sum = 0;
        }
    }
}
long double input_eps(int eps)
{
    std::cout << "input how many digits you want to count\n";
    input_number(eps);
    check_if_positive(eps);
    return eps_to_num(eps);
}
void input_number(int32_t& number)
{
    if (!(std::cin >> number))
    {
        throw "ERROR: not a number";
    }
}
void input_number(long double& number)
{
    if (!(std::cin >> number))
    {
        throw "ERROR: not a number";
    }
}
void check_if_positive(long double number)
{
    if (number < 0)
    {
        throw "ERROR: not positive";
    }
}
long double eps_to_num(int32_t eps_power)
{
    if (eps_power > 13)
    {
        throw "epsilon too large";
    }
    std::cout.precision(eps_power);
    return pow(10, -eps_power);
}
void input_borders(long double& left, long double& right)
{
    std::cout << "input integral borders\n";
    input_number(left);
    input_number(right);
    if (left > right)
    {
        std::swap(left, right);
    }
}
long double function_1(long double x)
{
    return (1 / (1 + x * x * x));
}
long double function_2(long double x)
{
    return (x * log(x));
}
long double function_3(long double x)
{
    return (log(x) / x);
}
long double count_trap_area(long double left, long double right, function function)
{
    return ((right - left) * (function(right) + function(left)) / 2);
}
long double count_left_rectangle_area(long double left, long double right, function function)
{
    return ((right - left) * function(left));
}
long double count_right_rectangle_area(long double left, long double right, function function)
{
    return ((right - left) * function(right));
}
long double count_mid_rectangle_area(long double left, long double right, function function)
{
    return ((right - left) * (function((right + left) / 2)));
}
long double count_simpson_area(long double left, long double right, function function)
{
    return (((right - left) / 6) * ((function(left) + 4 * function((right + left)/2) + function(right))));
}
void choice_of_function(int32_t& function)
{
    std::cout << "input function, integral of which you want tot count\n1) 1/x^3\n2)xlogx\n3)(logx)/x\n";
    if (!((std::cin >> function) && (function >= 1) && (function <= 3)))
    {
        throw "invalid function";
    }
}
void choice_of_method(int32_t& method)
{
    std::cout << "input function, integral of which you want tot count\n1) 1/x^3\n2)xlogx\n3)(logx)/x\n";
    if (!((std::cin >> method) && (method >= 1) && (method <= 5)))
    {
        throw "invalid method";
    }
}