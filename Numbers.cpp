//
// Created by leonardo on 09/04/21.
//

#include "Numbers.h"
#include <iostream>

int getCommonDivider(int a, int b) {
    /* Details can be found in the following link
     * https://ocw.mit.edu/courses/mathematics-for-computer-science/resources/mit6_042js15_textbook/
     * Contribution by Habib Kirollos */
    int tmp;
    while(b){
        tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

void Fraction::simplify() {
    if(den == 0)
        return;
    int common = getCommonDivider(std::abs(num), std::abs(den));
    num = num/common;
    den = den/common;
    if (den < 0) {
        num = -num;
        den = -den;
    }
}

void Fraction::input() {
    bool isFloat = false;
    std::cout << "Insert num/den (int) or num (int or float):";
    std::string input;
    std::string first, second;
    std::stringstream ss1, ss2;
    std::cin >> input;
    int j = 0;
    while (input[j] != '/' && j != input.length()){
        j++;
    }

    if (j != input.length()) {
        for (int i = 0; i < j; i++){
            first += input[i];
        }
        for (int k = j+1; k < input.length(); k++){
            if (input[k] != ' '){
                second += input[k];
            }
        }
        ss1 << second;
        ss1 >> den;
        ss2 << first;
        ss2 >> num;
    }
    else {
        for (int i = 0; i < input.length(); i++){
            first += input[i];
            if (!isFloat && input[i] == '.')
                isFloat = true;
        }
        if (isFloat) {
            makeFraction(first);
        }
        else {
            ss1 << first;
            ss1 >> num;
            den = 1;
        }
    }
    simplify();
}

std::string Fraction::toString() const {
    std::stringstream output;
    if (den > 1)
        output << num << "/" << den;
    else if (den == 1){
        output << num;
    }
    else if (den == 0){
        output << "nan";
    }
    else if (den < 0 && den != -1) {
        output << -num << "/" << -den;
    } else {
        output << -num;
    }
    std::string out;
    output >> out;
    return out;
}

float Fraction::toFloat() const {
    return (float)num/(float)den;
}

Fraction Fraction::operator+(const Fraction& right) const{
    Fraction Result;
    int new_den;
    new_den = den * right.den;
    if(den != 0 && right.den != 0) {
        Result.num = num * (new_den / den) + right.num * (new_den / right.den);
        Result.den = new_den;
    }
    Result.simplify();
    return Result;
}

Fraction Fraction::operator-(const Fraction& right) const{
    Fraction Result;
    int new_den;
    new_den = den * right.den;
    if(den != 0 && right.den != 0) {
        Result.num = num * (new_den / den) - right.num * (new_den / right.den);
        Result.den = new_den;
    }
    Result.simplify();
    return Result;
}

Fraction Fraction::operator*(const Fraction &right) const{
    Fraction Result;
    Result.num = num * right.num;
    Result.den = den * right.den;
    Result.simplify();
    return Result;
}

Fraction Fraction::operator/(const Fraction& right) const{
    Fraction Result;
    Result.num = num * right.den;
    Result.den = den * right.num;
    Result.simplify();
    return Result;
}

Fraction& Fraction::operator=(const Fraction& right){
    num = right.num;
    den = right.den;
    return *this;
}

bool Fraction::operator>(const Fraction &right) const{
    bool isMajor = false;
    if ((double)num/den > (double)right.num/right.den){
        isMajor = true;
    }
    return isMajor;
}

bool Fraction::operator>=(const Fraction &right) const{
    bool isMajor = false;
    if ((double)num/den >= (double)right.num/right.den){
        isMajor = true;
    }
    return isMajor;
}

bool Fraction::operator<(const Fraction &right) const{
    bool isMinor = false;
    if ((double)num/den < (double)right.num/right.den){
        isMinor = true;
    }
    return isMinor;
}

bool Fraction::operator<=(const Fraction &right) const{
    bool isMinor = false;
    if ((double)num/den <= (double)right.num/right.den){
        isMinor = true;
    }
    return isMinor;
}

bool Fraction::operator==(const double& right) const{
    double fraction;
    fraction = (float)num/(float)den;
    if(fraction == right)
        return true;
    else
        return false;
}

bool Fraction::operator!=(const double& right) const{
    double fraction;
    fraction = (float)num/(float)den;
    if(fraction != right)
        return true;
    else
        return false;
}

bool Fraction::operator==(const Fraction &right) const {
    if (num == right.num && den == right.den)
        return true;
    return false;
}

bool Fraction::operator!=(const Fraction &right) const {
    if (num != right.num || den != right.den)
        return true;
    return false;
}

Fraction Fraction::abs() const{
    Fraction output;
    if (num<0) {
        output.num = -num;
    }
    else output.num = num;
    if (den<0) {
        output.den = -den;
    }
    else output.den = den;
    return output;
}

void Fraction::makeFraction(std::string input) {
    std::string s_num;
    std::string s_den;
    bool dot_found = false;
    int pos_dot = -1;

    for (int i = 0; i < input.length() && !dot_found; i++) {
        if (input[i] == '.') {
            dot_found = true;
        }
        pos_dot++;
    }

    if (dot_found) {
        s_den = '1';
        for (int k = 0; k < pos_dot; k++) {
            s_num += input[k];
        }
        for (int i = pos_dot+1; i < input.length(); i++) {
            s_num += input[i];
            s_den += '0';
        }
        num = std::stoi(s_num);
        den = std::stoi(s_den);
        simplify();
    }
}

void Fraction::fromString(std::string const input){
    bool isFloat = false;
    std::string first, second;
    std::stringstream ss1, ss2;
    int j = 0;
    while (input[j] != '/' && j != input.length()){
        j++;
    }

    if (j != input.length()) {
        for (int i = 0; i < j; i++){
            first += input[i];
        }
        for (int k = j+1; k < input.length(); k++){
            if (input[k] != ' '){
                second += input[k];
            }
        }
        ss1 << second;
        ss1 >> den;
        ss2 << first;
        ss2 >> num;
    }
    else {
        for (int i = 0; i < input.length(); i++){
            first += input[i];
            if (isFloat == false && input[i] == '.')
                isFloat = true;
        }
        if (isFloat) {
            makeFraction(first);
        }
        else {
            ss1 << first;
            ss1 >> num;
            den = 1;
        }
    }
    simplify();
}