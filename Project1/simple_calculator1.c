// simple_calculator1.c
// can do calculations between simple integers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    int param1 = 0;
    int param2 = 0;
    char operator_sign = '+';
    for (int i = 1; i < argc; i++)
    {
        switch (i)
        {
        case 1:
            param1 = convert_to_inte(argv[i]);
            break;
        case 3:
            param2 = convert_to_inte(argv[i]);
            break;
        case 2:
            operator_sign = convert_to_oper(argv[i]);
        default:
            break;
        }
    }
    // printf("The frist parameter is : %d \n", param1);
    // printf("The operator is : %c \n", operator_sign);
    // printf("The frist parameter is : %d \n", param2);
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

    return 0;
}