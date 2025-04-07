#include "s21_matrix_oop.h"
#include "gtest/gtest.h"

// Тестовый класс для удобства
class S21MatrixTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Инициализация тестовой матрицы 2x2
    matrix_2x2 = S21Matrix(2, 2);
    matrix_2x2(0, 0) = 1.0;
    matrix_2x2(0, 1) = 2.0;
    matrix_2x2(1, 0) = 3.0;
    matrix_2x2(1, 1) = 4.0;
  }

  S21Matrix matrix_2x2;
};

// Тест Determinant для матрицы 3x3
TEST_F(S21MatrixTest, Determinant3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 4.0;
  m(1, 1) = 5.0;
  m(1, 2) = 6.0;
  m(2, 0) = 7.0;
  m(2, 1) = 8.0;
  m(2, 2) = 9.0;
  double det = m.Determinant();
  EXPECT_NEAR(det, 0.0, 1e-7); // Определитель равен 0
}

// Тест Determinant для матрицы 4x4
TEST_F(S21MatrixTest, Determinant4x4) {
  S21Matrix m(4, 4);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(0, 3) = 4.0;
  m(1, 0) = 5.0;
  m(1, 1) = 6.0;
  m(1, 2) = 7.0;
  m(1, 3) = 8.0;
  m(2, 0) = 9.0;
  m(2, 1) = 10.0;
  m(2, 2) = 11.0;
  m(2, 3) = 12.0;
  m(3, 0) = 13.0;
  m(3, 1) = 14.0;
  m(3, 2) = 15.0;
  m(3, 3) = 16.0;
  double det = m.Determinant();
  EXPECT_NEAR(det, 0.0, 1e-7); // Определитель равен 0
}

// Тест конструктора по умолчанию
TEST(S21MatrixTestDefault, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
}

// Тест параметризированного конструктора
TEST(S21MatrixTestParam, ParamConstructor) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 4);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_EQ(m(i, j), 0.0); // Проверка инициализации нулями
    }
  }
}

// Тест исключения при некорректных размерах
TEST(S21MatrixTestParam, InvalidSize) {
  EXPECT_THROW(S21Matrix m(0, 1), std::invalid_argument);
  EXPECT_THROW(S21Matrix m(1, -1), std::invalid_argument);
}

// Тест конструктора копирования
TEST(S21MatrixTestCopy, CopyConstructor) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 4.0;
  S21Matrix m2(m1);
  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 2);
}

// Тест конструктора перемещения
TEST(S21MatrixTestMove, MoveConstructor) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 2);
  EXPECT_EQ(m2(0, 0), 1.0);
  EXPECT_EQ(m1.GetRows(), 0); // Проверка, что m1 обнулился
  EXPECT_EQ(m1.GetCols(), 0);
}

// Тест EqMatrix
TEST_F(S21MatrixTest, EqMatrix) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2 = matrix_2x2;
  EXPECT_TRUE(m1.EqMatrix(m2));
  m2(0, 0) = 5.0;
  EXPECT_FALSE(m1.EqMatrix(m2));
}

// Тест SumMatrix
TEST_F(S21MatrixTest, SumMatrix) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2 = matrix_2x2;
  m1.SumMatrix(m2);
  EXPECT_EQ(m1(0, 0), 2.0);
  EXPECT_EQ(m1(0, 1), 4.0);
  EXPECT_EQ(m1(1, 0), 6.0);
  EXPECT_EQ(m1(1, 1), 8.0);
}

TEST_F(S21MatrixTest, SumMatrixException) {
  S21Matrix m1(2, 3);
  EXPECT_THROW(matrix_2x2.SumMatrix(m1), std::logic_error);
}

// Тест SubMatrix
TEST_F(S21MatrixTest, SubMatrix) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2(2, 2);
  m2(0, 0) = 1.0;
  m1.SubMatrix(m2);
  EXPECT_EQ(m1(0, 0), 0.0);
  EXPECT_EQ(m1(0, 1), 2.0);
  EXPECT_EQ(m1(1, 0), 3.0);
  EXPECT_EQ(m1(1, 1), 4.0);
}

TEST_F(S21MatrixTest, SubMatrixException) {
  S21Matrix m1(3, 2);
  EXPECT_THROW(matrix_2x2.SubMatrix(m1), std::logic_error);
}

// Тест MulNumber
TEST_F(S21MatrixTest, MulNumber) {
  S21Matrix m1 = matrix_2x2;
  m1.MulNumber(2.0);
  EXPECT_EQ(m1(0, 0), 2.0);
  EXPECT_EQ(m1(0, 1), 4.0);
  EXPECT_EQ(m1(1, 0), 6.0);
  EXPECT_EQ(m1(1, 1), 8.0);
}

// Тест MulMatrix
TEST_F(S21MatrixTest, MulMatrix) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2 = matrix_2x2;
  m1.MulMatrix(m2);
  EXPECT_EQ(m1(0, 0), 7.0);  // 1*1 + 2*3
  EXPECT_EQ(m1(0, 1), 10.0); // 1*2 + 2*4
  EXPECT_EQ(m1(1, 0), 15.0); // 3*1 + 4*3
  EXPECT_EQ(m1(1, 1), 22.0); // 3*2 + 4*4
}

TEST_F(S21MatrixTest, MulMatrixException) {
  S21Matrix m1(3, 2);
  EXPECT_THROW(matrix_2x2.MulMatrix(m1), std::logic_error);
}

// Тест Transpose
TEST_F(S21MatrixTest, Transpose) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2 = m1.Transpose();
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 2);
  EXPECT_EQ(m2(0, 0), 1.0);
  EXPECT_EQ(m2(0, 1), 3.0);
  EXPECT_EQ(m2(1, 0), 2.0);
  EXPECT_EQ(m2(1, 1), 4.0);
}

// Тест Determinant
TEST_F(S21MatrixTest, Determinant) {
  S21Matrix m1 = matrix_2x2;
  double det = m1.Determinant();
  EXPECT_NEAR(det, -2.0, 1e-7); // 1*4 - 2*3 = -2
}

TEST_F(S21MatrixTest, DeterminantException) {
  S21Matrix m1(2, 3);
  EXPECT_THROW(m1.Determinant(), std::logic_error);
}

// Тест CalcComplements
TEST_F(S21MatrixTest, CalcComplements) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix comp = m1.CalcComplements();
  EXPECT_EQ(comp(0, 0), 4.0);
  EXPECT_EQ(comp(0, 1), -3.0);
  EXPECT_EQ(comp(1, 0), -2.0);
  EXPECT_EQ(comp(1, 1), 1.0);
}

TEST_F(S21MatrixTest, CalcComplementsException) {
  S21Matrix m1(2, 3);
  EXPECT_THROW(m1.CalcComplements(), std::logic_error);
}

// Тест InverseMatrix
TEST_F(S21MatrixTest, InverseMatrix) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix inv = m1.InverseMatrix();
  EXPECT_NEAR(inv(0, 0), -2.0, 1e-7);
  EXPECT_NEAR(inv(0, 1), 1.0, 1e-7);
  EXPECT_NEAR(inv(1, 0), 1.5, 1e-7);
  EXPECT_NEAR(inv(1, 1), -0.5, 1e-7);
}

TEST_F(S21MatrixTest, InverseMatrixException) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 1.0;
  m1(1, 0) = 1.0;
  m1(1, 1) = 1.0; // det = 0
  EXPECT_THROW(m1.InverseMatrix(), std::logic_error);
}

// Тест оператора +
TEST_F(S21MatrixTest, OperatorPlus) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2 = matrix_2x2;
  S21Matrix res = m1 + m2;
  EXPECT_EQ(res(0, 0), 2.0);
  EXPECT_EQ(res(0, 1), 4.0);
  EXPECT_EQ(res(1, 0), 6.0);
  EXPECT_EQ(res(1, 1), 8.0);
}

// Тест оператора -
TEST_F(S21MatrixTest, OperatorMinus) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2(2, 2);
  m2(0, 0) = 1.0;
  S21Matrix res = m1 - m2;
  EXPECT_EQ(res(0, 0), 0.0);
  EXPECT_EQ(res(0, 1), 2.0);
  EXPECT_EQ(res(1, 0), 3.0);
  EXPECT_EQ(res(1, 1), 4.0);
}

// Тест оператора * (матрица)
TEST_F(S21MatrixTest, OperatorMulMatrix) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2 = matrix_2x2;
  S21Matrix res = m1 * m2;
  EXPECT_EQ(res(0, 0), 7.0);
  EXPECT_EQ(res(0, 1), 10.0);
  EXPECT_EQ(res(1, 0), 15.0);
  EXPECT_EQ(res(1, 1), 22.0);
}

// Тест оператора * (число)
TEST_F(S21MatrixTest, OperatorMulNumber) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix res = m1 * 2.0;
  EXPECT_EQ(res(0, 0), 2.0);
  EXPECT_EQ(res(0, 1), 4.0);
  EXPECT_EQ(res(1, 0), 6.0);
  EXPECT_EQ(res(1, 1), 8.0);
}

// Тест оператора +=
TEST_F(S21MatrixTest, OperatorPlusEq) {
  S21Matrix m1 = matrix_2x2;
  m1 += matrix_2x2;
  EXPECT_EQ(m1(0, 0), 2.0);
  EXPECT_EQ(m1(0, 1), 4.0);
  EXPECT_EQ(m1(1, 0), 6.0);
  EXPECT_EQ(m1(1, 1), 8.0);
}

// Тест оператора -=
TEST_F(S21MatrixTest, OperatorMinusEq) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2(2, 2);
  m2(0, 0) = 1.0;
  m1 -= m2;
  EXPECT_EQ(m1(0, 0), 0.0);
  EXPECT_EQ(m1(0, 1), 2.0);
  EXPECT_EQ(m1(1, 0), 3.0);
  EXPECT_EQ(m1(1, 1), 4.0);
}

// Тест оператора *= (матрица)
TEST_F(S21MatrixTest, OperatorMulEqMatrix) {
  S21Matrix m1 = matrix_2x2;
  m1 *= matrix_2x2;
  EXPECT_EQ(m1(0, 0), 7.0);
  EXPECT_EQ(m1(0, 1), 10.0);
  EXPECT_EQ(m1(1, 0), 15.0);
  EXPECT_EQ(m1(1, 1), 22.0);
}

// Тест оператора *= (число)
TEST_F(S21MatrixTest, OperatorMulEqNumber) {
  S21Matrix m1 = matrix_2x2;
  m1 *= 2.0;
  EXPECT_EQ(m1(0, 0), 2.0);
  EXPECT_EQ(m1(0, 1), 4.0);
  EXPECT_EQ(m1(1, 0), 6.0);
  EXPECT_EQ(m1(1, 1), 8.0);
}

// Тест оператора =
TEST_F(S21MatrixTest, OperatorAssign) {
  S21Matrix m1 = matrix_2x2;
  S21Matrix m2;
  m2 = m1;
  EXPECT_TRUE(m1.EqMatrix(m2));
}

// Тест оператора ()
TEST_F(S21MatrixTest, OperatorIndex) {
  EXPECT_EQ(matrix_2x2(0, 0), 1.0);
  EXPECT_EQ(matrix_2x2(0, 1), 2.0);
  matrix_2x2(1, 1) = 5.0;
  EXPECT_EQ(matrix_2x2(1, 1), 5.0);
}

TEST_F(S21MatrixTest, OperatorIndexException) {
  EXPECT_THROW(matrix_2x2(2, 0), std::out_of_range);
  EXPECT_THROW(matrix_2x2(-1, 1), std::out_of_range);
}

// Тест GetRows и GetCols
TEST_F(S21MatrixTest, GetRowsCols) {
  EXPECT_EQ(matrix_2x2.GetRows(), 2);
  EXPECT_EQ(matrix_2x2.GetCols(), 2);
}

// Тест SetRows
TEST_F(S21MatrixTest, SetRowsIncrease) {
  S21Matrix m1 = matrix_2x2;
  m1.SetRows(3);
  EXPECT_EQ(m1.GetRows(), 3);
  EXPECT_EQ(m1.GetCols(), 2);
  EXPECT_EQ(m1(0, 0), 1.0);
  EXPECT_EQ(m1(2, 0), 0.0); // Новые элементы заполнены нулями
}

TEST_F(S21MatrixTest, SetRowsDecrease) {
  S21Matrix m1 = matrix_2x2;
  m1.SetRows(1);
  EXPECT_EQ(m1.GetRows(), 1);
  EXPECT_EQ(m1.GetCols(), 2);
  EXPECT_EQ(m1(0, 0), 1.0);
  EXPECT_EQ(m1(0, 1), 2.0);
}

// Тест SetCols
TEST_F(S21MatrixTest, SetColsIncrease) {
  S21Matrix m1 = matrix_2x2;
  m1.SetCols(3);
  EXPECT_EQ(m1.GetRows(), 2);
  EXPECT_EQ(m1.GetCols(), 3);
  EXPECT_EQ(m1(0, 0), 1.0);
  EXPECT_EQ(m1(0, 2), 0.0); // Новые элементы заполнены нулями
}

TEST_F(S21MatrixTest, SetColsDecrease) {
  S21Matrix m1 = matrix_2x2;
  m1.SetCols(1);
  EXPECT_EQ(m1.GetRows(), 2);
  EXPECT_EQ(m1.GetCols(), 1);
  EXPECT_EQ(m1(0, 0), 1.0);
  EXPECT_EQ(m1(1, 0), 3.0);
}

TEST_F(S21MatrixTest, SetRowsColsException) {
  EXPECT_THROW(matrix_2x2.SetRows(-1), std::length_error);
  EXPECT_THROW(matrix_2x2.SetCols(0), std::length_error);
}

// Тест const оператора () - доступ к элементам константной матрицы
TEST_F(S21MatrixTest, ConstOperatorIndex) {
  const S21Matrix &const_matrix =
      matrix_2x2; // Создаем константную ссылку на матрицу

  // Проверяем чтение элементов
  EXPECT_EQ(const_matrix(0, 0), 1.0);
  EXPECT_EQ(const_matrix(0, 1), 2.0);
  EXPECT_EQ(const_matrix(1, 0), 3.0);
  EXPECT_EQ(const_matrix(1, 1), 4.0);

  // Проверяем, что нельзя изменить элементы через const оператор
  // (это проверяется на этапе компиляции, поэтому просто убедитесь, что
  // следующий код не компилируется) const_matrix(0, 0) = 5.0; // Должно
  // вызывать ошибку компиляции
}

// Тест исключений для const оператора ()
TEST_F(S21MatrixTest, ConstOperatorIndexException) {
  const S21Matrix &const_matrix = matrix_2x2;

  EXPECT_THROW(const_matrix(2, 0), std::out_of_range); // Выход за границы строк
  EXPECT_THROW(const_matrix(-1, 1),
               std::out_of_range); // Отрицательный индекс строки
  EXPECT_THROW(const_matrix(0, 2),
               std::out_of_range); // Выход за границы столбцов
  EXPECT_THROW(const_matrix(0, -1),
               std::out_of_range); // Отрицательный индекс столбца
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}