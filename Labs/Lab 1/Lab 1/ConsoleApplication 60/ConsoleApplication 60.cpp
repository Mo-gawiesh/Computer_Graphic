#include <iostream> 
#include <math.h> 
void input(double& a, double& b, double& c)
{
    std::cout << "a = ";  std::cin >> a;
    std::cout << "b = ";  std::cin >> b;
    std::cout << "c = ";  std::cin >> c;
}
double delta(double a, double b, double c)
{
    return (b * b) - (4 * a * c);
}
double calculate(double a, double b, double d)
{
    return (-b + d) / (2 * a);
}
void print(double a, double b, double c)
{
    double d = delta(a, b, c);
    std::cout << "Delta = " << d << std::endl;
    if (d > 0)
    {
        std::cout << "x1 = " << calculate(a, b, sqrt(d)) << std::endl;
        std::cout << "x2 = " << calculate(a, b, -sqrt(d)) << std::endl;
    }
    else if (d == 0)
        std::cout << "x1 = x2 = " << calculate(a, b, 0) << std::endl;
    else std::cout << "No real solution!" << std::endl;
}
int main()
{
    double a, b, c;
    input(a, b, c);
    print(a, b, c);

    return 0;
}