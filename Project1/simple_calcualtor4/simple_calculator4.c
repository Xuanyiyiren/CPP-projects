// simple_calculator4.c
// can do calculations between simple integers and float numbers.
// Hard to deal big integers because range overflow
// Hard to deal big float numbers because the output formatting for C is too awkward!

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// failed, becasue 3.3 - 3 = 0.2999999999999999, the reason why my theoritical method to get decimal places failed.
// You can check the method in float_number_display.c
// You can check the catastrophic result in plaground_4.c
#include "float_number_display.h"

int convert_to_inte(const char *str)
{
    return atoi(str);
}
char convert_to_oper(const char *str)
{
    if (strlen(str) == 1)
        return str[0];
    else
    {
        fprintf(stderr, "The operator can only be '+','-','x','/'. \n");
        return '+';
    }
}

void show_input_example()
{
    printf("2 + 3 # the input\n");
    printf("2 + 3 = 5 # the output\n");
    printf("2 x 3 #input another expression\n");
    printf("2 x 3 = 6 #the output\n");
    // printf("quit #the command to quit\n");
}

void integer_calculate(int param1, int param2, char operator_sign)
{
    switch (operator_sign)
    {
    case '+':
        printf("%d + %d = %d\n", param1, param2, param1 + param2);
        break;

    case '-':
        printf("%d - %d = %d\n", param1, param2, param1 - param2);
        break;

    case 'x':
        printf("%d x %d = %d\n", param1, param2, param1 * param2);
        break;

    case '/':
        if (param2 != 0)
            printf("%d / %d = %lf\n", param1, param2, (double)param1 / param2);
        else
            fprintf(stderr, "A number cannot be divied by zero.\n");
        break;
    }
}

void double_calculate(double param1, double param2, char operator_sign)
{
    switch (operator_sign)
    {
    case '+':
        print_fnum(param1);
        printf(" + ");
        print_fnum(param2);
        printf(" = ");
        print_fnum(param1 + param2);
        printf("\n");
        break;

    case '-':
        print_fnum(param1);
        printf(" - ");
        print_fnum(param2);
        printf(" = ");
        print_fnum(param1 - param2);
        printf("\n");
        break;

    case 'x':
        print_fnum(param1);
        printf(" x ");
        print_fnum(param2);
        printf(" = ");
        print_fnum(param1 * param2);
        printf("\n");
        break;

    case '/':
        if (fabs(param2) > __DBL_EPSILON__)
        {
            print_fnum(param1);
            printf(" / ");
            print_fnum(param2);
            printf(" = ");
            print_fnum(param1 / param2);
            printf("\n");
        }
        else
            fprintf(stderr, "A number cannot be divied by zero.\n");
        break;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        show_input_example();
        return 0;
    }
    if (argc > 4)
    {
        fprintf(stderr, "Wops, '*' will be translate to wildcard by the terminal. You should use 'x' which is the letter x to instead it.\n");
        show_input_example();
        return 0;
    }
    _Bool is_integer1 = (strchr(argv[1], '.') == NULL) && (strchr(argv[1], 'e') == NULL) && (strchr(argv[1], 'E') == NULL);
    _Bool is_integer2 = (strchr(argv[3], '.') == NULL) && (strchr(argv[3], 'e') == NULL) && (strchr(argv[3], 'E') == NULL);
    char operator_sign = convert_to_oper(argv[2]);

    _Bool int_mode = is_integer1 && is_integer2;
    if (int_mode)
    {
        int param1 = atoi(argv[1]);
        int param2 = atoi(argv[3]);
        integer_calculate(param1, param2, operator_sign);
    }
    else
    {
        double param1 = atof(argv[1]);
        double param2 = atof(argv[3]);
        double_calculate(param1, param2, operator_sign);
    }
}