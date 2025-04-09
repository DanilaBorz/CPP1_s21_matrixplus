#include "s21_matrix_oop.h"
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Incorrect input");
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols_]();
  }
}
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
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

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  } else {
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

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrices are incompatible for addition");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
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

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("Matrices are incompatible for multiplication");
  }
  S21Matrix res_matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double sum = 0;
      for (int k = 0; k < cols_; k++) {
        sum += matrix_[i][k] * other.matrix_[k][j];
      }
      res_matrix.matrix_[i][j] = sum;
    }
  }
  *this = res_matrix;
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

S21Matrix S21Matrix::CreateMinorMatrix(int exclude_row, int exclude_col) const {
  if (exclude_row >= rows_ || exclude_col >= cols_) {
    throw std::out_of_range("Incorrect input");
  }
  S21Matrix res(rows_ - 1, cols_ - 1);
  int i_res = 0;
  for (int i = 0; i < rows_; i++) {
    int j_res = 0;
    for (int j = 0; j < cols_; j++) {
      int row_condition = (i != exclude_row);
      int col_condition = (j != exclude_col);
      if (row_condition && col_condition) {
        res.matrix_[i_res][j_res] = matrix_[i][j];
        j_res++;
      }
    }
    if (i != exclude_row) {
      i_res++;
    }
  }
  return res;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::logic_error("The matrix isn't square");
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    double determinant = 0;
    for (int j = 0; j < this->cols_; ++j) {
      S21Matrix minor_matrix = CreateMinorMatrix(0, j);
      double minor_determinant = minor_matrix.Determinant();
      determinant += matrix_[0][j] * pow(-1, j) * minor_determinant;
    }
    return determinant;
  }
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix isn't square");
  }
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double minor_determinant = CreateMinorMatrix(i, j).Determinant();
      res.matrix_[i][j] = pow(-1, i + j) * minor_determinant;
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant = Determinant();
  if (abs(determinant) < 1e-7) {
    throw std::logic_error("The matrix is singular");
  }
  S21Matrix res = CalcComplements().Transpose();
  return res * (1.0 / determinant);
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

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    S21Matrix temp(other);
    std::swap(rows_, temp.rows_);
    std::swap(cols_, temp.cols_);
    std::swap(matrix_, temp.matrix_);
  }
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of matrix bounds");
  }
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of matrix bounds");
  }
  return matrix_[i][j];
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int new_rows) {
  if (new_rows <= 0) {
    throw std::length_error("matrix rows must be positive");
  }
  if (new_rows != rows_) {
    S21Matrix tmp{new_rows, cols_};
    int minimum = std::min(rows_, new_rows);
    for (int i = 0; i < minimum; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols <= 0) {
    throw std::length_error("matrix cols must be positive");
  }
  if (new_cols != cols_) {
    S21Matrix tmp{rows_, new_cols};
    int minimum = std::min(cols_, new_cols);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < minimum; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}