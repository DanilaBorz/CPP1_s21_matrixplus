#include "s21_matrix_oop.h"
S21Matrix::S21Matrix():
  rows_(0), cols_(0), matrix_(nullptr) 
  {}
S21Matrix::S21Matrix(int rows, int cols):
  rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Incorrect input");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols_];
  }
}
S21Matrix::S21Matrix(const S21Matrix& other):
  rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
S21Matrix::S21Matrix(S21Matrix&& other):
  rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  }
  else {
    for (int i = 0; i < rows_ && res; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
          res = false;
        }
      }
    }
  }
return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrices are incompatible for addition");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrices are incompatible for subtraction");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

    void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("Matrices are incompatible for multiplication");
  }
  double** res = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    res[i] = new double[other.cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      res[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        res[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::CreateMinorMatrix(int miss_rows, int miss_cols) const {
  // доделать + детерминант + комплементы + инверсия
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}
