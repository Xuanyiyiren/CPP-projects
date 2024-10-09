// simple_calculator4.c
// can do calculations between simple integers and float numbers.
// Hard to deal big integers because range overflow
// Hard to deal big float numbers because the output formatting for C is too awkward!

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h> // using fabs()

#define SCI_UPPER_LIMIT 1e4
#define SCI_LOWWER_LIMIT 1e-4
void print_fnum(double num)
{
    double num_abs = fabs(num);
    char output[50];
    if ((num_abs > SCI_UPPER_LIMIT) || (num_abs < SCI_LOWWER_LIMIT))
    {
        int length = sprintf(output, "%le", num);
        int non_zero = 7; // 'e' must be at index 8
        for (int i = 8 - 1; i >= 0; i--)
        {
            if (output[i] != '0')
            {
                non_zero = i;
                break;
            }
        }
        if (output[non_zero] == '.')
            non_zero--;
        output[non_zero + 1] = 0;
        printf("%se%s", output, output + 9);
    }
    else
    {
        int length = sprintf(output, "%lf", num);
        int non_zero = length - 1;
        for (int i = length - 1; i >= 0; i--)
        {
            if (output[i] != '0')
            {
                non_zero = i;
                break;
            }
        }
        if (output[non_zero] == '.')
            non_zero--;
        output[non_zero + 1] = 0;
        printf("%s", output);
    }
}

void print_lfnum(long double num)
{
    long double num_abs = fabs(num);
    char output[50];
    if ((num_abs > SCI_UPPER_LIMIT) || (num_abs < SCI_LOWWER_LIMIT))
    {
        int length = sprintf(output, "%Le", num);
        int non_zero = 7; // 'e' must be at index 8
        for (int i = 8 - 1; i >= 0; i--)
        {
            if (output[i] != '0')
            {
                non_zero = i;
                break;
            }
        }
        if (output[non_zero] == '.')
            non_zero--;
        output[non_zero + 1] = 0;
        printf("%se%s", output, output + 9);
    }
    else
    {
        int length = sprintf(output, "%Lf", num);
        int non_zero = length - 1;
        for (int i = length - 1; i >= 0; i--)
        {
            if (output[i] != '0')
            {
                non_zero = i;
                break;
            }
        }
        if (output[non_zero] == '.')
            non_zero--;
        output[non_zero + 1] = 0;
        printf("%s", output);
    }
}

int estimate_log2(int n)
{
    if (n < 0)
        n *= -1;
    int count = 0;
    while (n >>= 1)
    {
        count++;
    }

    return count;
}

int float_exp(double num)
{
    int exponent;
    double mantissa = frexp(num, &exponent);
    return exponent;
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
        if (estimate_log2(param1) + estimate_log2(param2) < 8 * sizeof(int))
            printf("%d x %d = %d\n", param1, param2, param1 * param2);
        else
        {
            printf("%d x %d = %lld\n", param1, param2, (long long)param1 * (long long)param2);
        }
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
        if (abs(float_exp(param1) + float_exp(param2)) < DBL_MAX_EXP)
        {
            print_fnum(param1);
            printf(" x ");
            print_fnum(param2);
            printf(" = ");
            print_fnum(param1 * param2);
            printf("\n");
        }
        else
        {
            print_fnum(param1);
            printf(" x ");
            print_fnum(param2);
            printf(" = ");
            print_lfnum((long double)param1 * (long double)param2);
            printf("\n");
        }
        break;

    case '/':
        if (fabs(param2) > __DBL_EPSILON__)
        {
            if (abs(float_exp(param1) - float_exp(param2)) < DBL_MAX_EXP)
            {
                print_fnum(param1);
                printf(" / ");
                print_fnum(param2);
                printf(" = ");
                print_fnum(param1 / param2);
                printf("\n");
            }
            else
            {
                print_fnum(param1);
                printf(" / ");
                print_fnum(param2);
                printf(" = ");
                print_lfnum((long double)param1 / (long double)param2);
                printf("\n");
            }
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
    _Bool is_integer1 = 1;
    _Bool is_num1 = 1;
    for (char *ptr = argv[1]; *ptr != 0; ptr++)
    {
        if ((*ptr <= '9' && *ptr >= '0') || *ptr == '+' || *ptr == '-')
            ;
        else if (*ptr == '.' || *ptr == 'e' || *ptr == 'E')
            is_integer1 = 0;
        else
        {
            is_num1 = 0;
            break;
        }
    }
    _Bool is_integer2 = 1;
    _Bool is_num2 = 1;
    for (char *ptr = argv[3]; *ptr != 0; ptr++)
    {
        if ((*ptr <= '9' && *ptr >= '0') || *ptr == '+' || *ptr == '-')
            ;
        else if (*ptr == '.' || *ptr == 'e' || *ptr == 'E')
            is_integer2 = 0;
        else
        {
            is_num2 = 0;
            break;
        }
    }
    // _Bool is_integer1 = (strchr(argv[1], '.') == NULL) && (strchr(argv[1], 'e') == NULL) && (strchr(argv[1], 'E') == NULL);
    // _Bool is_integer2 = (strchr(argv[3], '.') == NULL) && (strchr(argv[3], 'e') == NULL) && (strchr(argv[3], 'E') == NULL);
    char operator_sign = convert_to_oper(argv[2]);

    if (!(is_num1 && is_num2))
    {
        fprintf(stderr, "The input cannot be interpret as numbers!\n");
        return -1;
    }
    if (is_integer1 && is_integer2)
    {
        // printf("Integer Mode: \n");
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