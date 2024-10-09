// float_number_display.h
#ifndef __FLOAT_NUMBER_DISPLAY_H__
#define __FLOAT_NUMBER_DISPLAY_H__

#define FLOAT_DECIMAL_PRECISION 4
#define FLOAT_PRECISION 1e-4
#define SCI_LIMIT 1e4

/**
 * @brief Calculate the number of decimal places in a given double number.
 *
 * This function determines the number of decimal places in the fractional part
 * of a given double number. It handles both positive and negative numbers by
 * converting negative numbers to positive before processing.
 *
 * The function is designed to assist the `print_fnum()` function, which formats
 * floating-point numbers for display. Specifically, it helps `print_fnum()`
 * determine the appropriate precision to use, ensuring that the displayed
 * precision does not exceed the predefined `FLOAT_PRECISION`.
 *
 * The `FLOAT_PRECISION` constant is crucial in this context, as it prevents
 * rounding errors from affecting the precision calculation. It should not be
 * replaced with a value that could be easily influenced by floating-point
 * arithmetic inaccuracies.
 *
 * @param num The double number for which to count the decimal places.
 * @return int The number of decimal places in the fractional part of the number.
 */
int _get_decimal_places(double num);

/**
 * @brief Prints a floating-point number with adaptive notation.
 *
 * This function prints a floating-point number, choosing between scientific
 * notation and fixed-point notation based on the value of the number. If the
 * number is less than the floating-point precision (FLOAT_PRECISION), or
 * exceeds a specified scientific notation limit (SCI_LIMIT) it prints the number
 * in scientific notation. Otherwise, it prints the number in fixed-point
 * notation with adaptive decimal places.
 *
 * @param num The floating-point number to be printed.
 */
void print_fnum(double num);

#endif // __FLOAT_NUMBER_DISPLAY_H__