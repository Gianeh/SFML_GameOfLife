#pragma once
#include <iostream>
#include <random>
#include <ctime>


class Matrix{
    private:
        bool** matrix;
        int cols, rows;
        //static
        static const int Max = 1000;
    public:
        //static
        static int counter;

        //Constructors / Destructor
        Matrix(const Matrix &other);
        Matrix();
        Matrix(int r, int c);
        ~Matrix();

        //static methods
        static Matrix create();

        //methods
        void zero() const;
        void eye() const;
        int row() const;
        int col() const;
        void set(bool temp, int i, int j) const;
        void add(bool temp, int i, int j) const;
        float get(int i, int j) const;
        void show() const;
        void compile() const;
        void random() const;

        //Only work on Non-Const objects
        void free();
        void reAllocate(int c, int r);
        
        bool operator()(int i, int j) const;
        bool& operator()(int i, int j);
        Matrix operator+(const Matrix &other) const;  //matrix + matrix
        Matrix operator*(const Matrix &other) const;  //matrix * matrix
        //needs #include "Array.h", of course, mine Array.h lib
        //Matrix operator*(const Array &other); //matrix * vector
};