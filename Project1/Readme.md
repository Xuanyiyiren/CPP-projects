# A simple calculator

This project is to finish a simple calculator in terminal. Like this : 

```bash
$./calculator 2 + 3
2 + 3 = 5
$./calculator 2 - 3
2 - 3 = -1
$./calculator 2 * 3
2 * 3 = 6
$./calculator 2 / 3
2 / 3 = 0.66666667
```

For more details, look [here](https://github.com/ShiqiYu/CPP/blob/main/projects/2024Spring/project1.md).

I have totally 5 versions.

## Version1 : simple_calculator1.c

I just finish the simplest calculation between integers.

## Version2 : simple_calculator2.c

This is a failed version.

I wish to extend this calculator to float numbers. But Prof.Yu requires us to complete it using only C. So I tried to realize somehow dynamic type in C between `int` and `double`.
My thought is here:

```c
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
```

I try to use the macro function below to get numbers, but failed because [the reason here](https://stackoverflow.com/a/79039485/23644201).

```c
#define GETVAL(param) (((param).datatype == INT) ? (param).data.int_ : (param).data.dou_)
``` 

## Version3 : simple_calculator3.c

So I decided to use the following brute force approach:

- If all inputs are integers, receive them as integers.
- If there are floating-point numbers among the inputs, receive them all as floating-point numbers.

Now things is much simpler.

## Version4 simple_calculator4/

This is a failed version too.

Now, I've successfully completed the third version, which can perform operations on both integers and floating-point numbers.

The next issue is that the output format for floating-point numbers in C is very mechanical. It would be great if I could automatically adjust the rendering precision and whether to use scientific notation based on the input data's precision and size; otherwise, the output looks really ugly.

C++'s standard output stream does this very well, but the instructor only allows using C. So I tried to write an adaptive floating-point output function in C, which automatically finds the minimum number of decimal places (since all input numbers are finite decimals) by repeatedly taking the decimal part and multiplying by ten.

Some readers may have noticed that even though you're inputting finite decimals, computers can't actually store real numbers; they all use floating-point models. For example, [this issue](https://stackoverflow.com/questions/7545015/can-someone-explain-this-0-2-0-1-0-30000000000000004). And the problems we will face.

When I input 3.3 into the function I wrote (don't ask why), the result was `50`. Does `3.3` have 50 decimal places? My friend and I searched for a long time and discovered that the reason was that 3.3, when output with sufficient precision, turned out to be `3.299999...`. No wonder!

## Version5 simple_calculator5.c

It seemes that the best way is not to treat them as numbers. I decide to use some method based on strings. And I successfully get the result I wanted.

I use `sprintf()` to extract the output from `printf()`, and remove all the zeros in the last indexes.

Further more, I write some functions to simply estimate how big the calculation result will be. If the result range over `int` or `double`, I will use `long long` and `long double` as the result's type.

```c
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
```