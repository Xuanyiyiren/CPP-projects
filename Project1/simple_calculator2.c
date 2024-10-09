// simple_calculator2.c failed because
// https://en.cppreference.com/w/c/language/operator_other#Conditional_operator
// https://stackoverflow.com/questions/79036800/what-will-happen-if-running-this-following-c-code/79036831#79036831
// can do calculations between simple integers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum _DataType
{
    INT,
    DOUBLE
} DataType;

typedef union _Data
{
    int int_;
    double dou_;
} Data;

typedef struct _Number
{
    DataType datatype;
    Data data;
} Number;

Number convert_to_num(const char *str)
{
    Number num;
    _Bool is_integer = (strchr(str, '.') == NULL);
    if (is_integer)
    {
        // printf("Is integ");
        num.datatype = INT;
        num.data.int_ = atoi(str);
    }
    else
    {
        // printf("Is float");
        num.datatype = DOUBLE;
        num.data.dou_ = atof(str);
    }
    return num;
}

void show_input_example()
{
    printf("2 + 3 # the input\n");
    printf("2 + 3 = 5 # the output\n");
    printf("2 x 3 #input another expression\n");
    printf("2 x 3 = 6 #the output\n");
    // printf("quit #the command to quit\n");
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
        printf("%d / %d = %lf\n", param1, param2, (double)param1 / param2);
        break;
    }
}

void double_calculate(double param1, double param2, char operator_sign)
{
    switch (operator_sign)
    {
    case '+':
        printf("%lf + %lf = %lf\n", param1, param2, param1 + param2);
        break;

    case '-':
        printf("%lf - %lf = %lf\n", param1, param2, param1 - param2);
        break;

    case 'x':
        printf("%lf x %lf = %lf\n", param1, param2, param1 * param2);
        break;

    case '/':
        printf("%lf / %lf = %lf\n", param1, param2, (double)param1 / param2);
        break;
    }
}
#define GETVAL(param) (((param).datatype == INT) ? (param).data.int_ : (param).data.dou_)

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

    Number param1 = convert_to_num(argv[1]);
    Number param2 = convert_to_num(argv[3]);

    char operator_sign = convert_to_oper(argv[2]);
    printf("%d\n", param1.datatype);
    printf("%d\n", GETVAL(param1));

    printf("%lf\n", GETVAL(param1));

    printf("%d\n", (0 ? (int)1 : (double)1.1));
    // _Bool float_mode = 0;
    // float_mode = (param1.datatype == DOUBLE) || (param2.datatype == DOUBLE);
    // if (float_mode)
    //     double_calculate(param1.data, param2, operator_sign);
}
