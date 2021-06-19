//
// Created by leonardo on 08/04/21.
//

#ifndef MATRIX_CALC_VECTOR_H
#define MATRIX_CALC_VECTOR_H

#include <iostream>
#include "Numbers.h"

class Vector {
public:

    explicit Vector(int size) : size(size){};

    explicit Vector(int size, Fraction value) : size(size){
        for (int i=0; i<size; i++){
            values[i] = value;
        }
    };

    explicit Vector(Fraction const V[], int size) : size(size){
        for (int i=0; i<size; i++){
            values[i] = V[i];
        }
    }

    virtual ~Vector() {
        delete[] values;
    }

    void init_Vector(int x){
        size = x;
        for (int i=0; i<size; i++){
            std::cout << "Insert " << i << "value:\t";
            values[i].input();
        }
        std::cout << std::endl;
    };

    bool isLegalValue(int pos) const{
        if (pos >= 0 && pos < size)
            return true;
        return false;
    }

    bool getValue(int pos, Fraction& value) const{
        if (isLegalValue(pos)) {
            value = values[pos];
            return true;
        }
        std::cout << "Invalid position!" << std::endl;
        return false;
    }

    bool setValue(int pos, Fraction value){
        if (isLegalValue(pos)){
            values[pos] = value;
            return true;
        }
        std::cout << "Invalid position!" << std::endl;
        return false;
    }

    Fraction findMax() const;

    void print();

protected:
    int size;
    Fraction* values = new Fraction[size];
};

#endif //MATRIX_CALC_VECTOR_H