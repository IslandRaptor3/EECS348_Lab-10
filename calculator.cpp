#include "calculator.hpp"


bool validate_number(const std::string &num) {
    int len = num.length();
    int i = 0;

    if (len == 0) return false; //Makes sure the num has a length greater than 0 (it's actual content)
    if (num[i] == '+' || num[i] == '-') i++;
    bool has_digits = false, has_dot = false, has_decimal_digits = false;

    for (;i < len; i++) {
        if(isdigit(num[i])) {
            if (!has_dot) {
                has_digits = true;
            } else {
                has_decimal_digits = true;
            }
        } else if (num[i] == '.') {
            if (has_dot) return false;
            has_dot = true;
        } else {
            return false;
        }
    }

    if(has_dot && !has_decimal_digits) return false;
    if(!has_dot && !has_digits) return false;

    return true;
}

std::string add_doubles(const std::string &a, const std::string &b) {
    size_t dot_a = a.find('.'), dot_b = b.find('.'); //Variables for the decimal location in each double a and b.
    size_t int_len_a = dot_a == std::string::npos ? a.length() : dot_a; //Gets the integer length for a up to the dot
    size_t int_len_b = dot_b == std::string::npos ? b.length() : dot_b; //Gets the integer length for b up to the dot

    std::string int_a = a.substr(0, int_len_a); //actual integer part of a
    std::string int_b = b.substr(0, int_len_b); //actual integer part of b

    //These get the part of the double past their dots.
    std::string frac_a = dot_a == std::string::npos ? "" : a.substr(dot_a + 1);
    std::string frac_b = dot_b == std::string::npos ? "" : b.substr(dot_b + 1);

    // Pad fractional parts (to make sure their lengths are the same)
    while (frac_a.length() < frac_b.length()) frac_a += '0';
    while (frac_b.length() < frac_a.length()) frac_b += '0';

    // Pad integer parts
    while (int_a.length() < int_b.length()) int_a = '0' + int_a;
    while (int_b.length() < int_a.length()) int_b = '0' + int_b;

    //Subttract fractional part
    std::string frac_diff = "";
    int borrow = 0;
    for (int i = frac_a.length() - 1; i >= 0; --i) {
        int diff = (frac_a[i] - '0') - (frac_b[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else borrow = 0;
        frac_diff = char(diff + '0') + frac_diff;
    }
    //Subtract integer part
    std::string int_diff = "";
    for (int i = int_a.length() - 1; i >= 0; --i) {
        int diff = (int_a[i] - '0') - (int_b[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else borrow = 0;
    int_diff = char(diff + '0') + int_diff;
    }

    //Trim the leading 0's
    int_diff.erase(0, int_diff.find_first_not_of('0'));
    if (int_diff.empty()) int_diff = "0";

    //Trim trailing 0's in fractional part
    while (!frac_diff.empty() && frac_diff.back() == '0') frac_diff.pop_back();

    return frac_diff.empty() ? int_diff : int_diff + "." + frac_diff;

}

//Compares two pos doubles to decide which is larger before doing any subtraction.
int compare_positive(const std::string &a, const std::string &b) {
    //Split each number into their fractional parts
    size_t dot_a = a.find('.'), dot_b = b.find('.');
    std::string int_a = dot_a == std::string::npos ? a : a.substr(0, dot_a);
    std::string int_b = dot_b == std::string::npos ? b : b.substr(0, dot_b);

    //Compare int.
    if (int_a.length() != int_b.length()) return int_a.length() < int_b.length() ? -1 : 1;
    if (int_a != int_b) return int_a < int_b ? -1 : 1;

    //If int parts are equal, compare fractional parts and pad
    std::string frac_a = dot_a == std::string::npos ? "" : a.substr(dot_a + 1);
    std::string frac_b = dot_b == std::string::npos ? "" : a.substr(dot_a + 1);
    while (frac_a.length() < frac_b.length()) frac_a += '0';
    while (frac_b.length() < frac_a.length()) frac_b += '0';

    if (frac_a != frac_b) return frac_a < frac_b ? -1 : 1;
    //If after everything both are exactly the same string
    return 0;
}

double parse_number(const std::string &expression) {
    std::string other_double = "-123.456";
    bool neg_expression = expression[0] == '-'; //Checks if the expression number is negative.
    std::string expr_abs = neg_expression ? expression.substr(1) : expression;

    std::string result;
    if (neg_expression) {
        result = add_doubles(expr_abs, other_double.substr(1));
        result = "-" + result;
    } else {
        int cmp = compare_positive(expr_abs, other_double.substr(1));
        if (cmp >= 0) {
            result = add_doubles(expr_abs, other_double.substr(1));
        } else {
            result = add_doubles(other_double.substr(1), expr_abs);
            if (result[0] != '-') result = "-" + result;
        }
    }

    std::cout << expression << " + (-123.456) = " << result << "\n";
}