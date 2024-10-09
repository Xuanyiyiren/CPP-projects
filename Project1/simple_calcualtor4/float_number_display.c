// float_number_display.c
#include "float_number_display.h"
#include <stdio.h>
#include <math.h>

int _get_decimal_places(double num)
{
    // Convert negative numbers to positive
    if (num < 0)
        num *= -1;
    int decimal_places = 0;
    double fractional_part = num - (int)num;
    // Loop until the fractional part is negligible
    printf("Begin: %lf\n", fractional_part);
    while ((fractional_part > FLOAT_PRECISION) && (decimal_places < FLOAT_DECIMAL_PRECISION))
    {
        printf("%lf\n", fractional_part);
        fractional_part *= 10;
        fractional_part -= (int)fractional_part;
        decimal_places++;
    }
    printf("\n");
    return decimal_places;
}

void print_fnum(double num)
{
    if (num > SCI_LIMIT)
        printf("%e", num);
    else
    {
        int decimal_places = _get_decimal_places(num);
        printf("%.*f", decimal_places, num);
    }
}
