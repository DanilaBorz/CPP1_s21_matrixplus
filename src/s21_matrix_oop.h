#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <iostream>
#include <utility>
#include <cmath>

class S21Matrix {
private:
    int rows_;
    int cols_;
    double** matrix_;

public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();
    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose() const;
    S21Matrix CreateMinorMatrix(int miss_rows, int miss_cols) const;
    double Determinant() const;
    S21Matrix CalcComplements() const;
    S21Matrix InverseMatrix() const;
    S21Matrix operator+(const S21Matrix& other) const;
    S21Matrix operator-(const S21Matrix& other) const;
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*(const double num);
    S21Matrix &operator+=(const S21Matrix& other);
    S21Matrix &operator-=(const S21Matrix& other);
    S21Matrix &operator*=(const S21Matrix& other);
    S21Matrix &operator*=(const double num);
};
#endif