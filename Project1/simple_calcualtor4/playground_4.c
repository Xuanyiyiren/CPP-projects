#include <stdio.h>

#define FLOAT_DECIMAL_PRECISION 90
#define FLOAT_PRECISION 1e-4
#define SCI_LIMIT 1e4

int main()
{
    double num = 0;
    double fractional_part = 0;
    int decimal_places = 0;

    decimal_places = 0;
    num = 3.3;
    // unsafety codes here
    fractional_part = num - (int)num;
    // unsafety codes here

    // Loop until the fractional part is negligible
    printf("Test1 Begin: %.16lf\n", fractional_part);
    while (fractional_part > FLOAT_PRECISION)
    {
        printf("Current fractional part before iteration: %.16lf\n", fractional_part);
        fractional_part *= 10;
        fractional_part -= (int)fractional_part;
        printf("Current fractional part after iteration : %.16lf\n", fractional_part);
        decimal_places++;
    }
    printf("Decimal places is : %d\n", decimal_places);

    decimal_places = 0;
    fractional_part = 0.3;
    // Loop until the fractional part is negligible
    printf("Test2 Begin: %lf\n", fractional_part);
    while (fractional_part > FLOAT_PRECISION)
    {
        printf("%lf\n", fractional_part);
        fractional_part *= 10;
        fractional_part -= (int)fractional_part;
        decimal_places++;
    }
    printf("Decimal places is : %d\n", decimal_places);
    return 0;
}