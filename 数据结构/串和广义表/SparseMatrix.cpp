#include <iostream>
#include <initializer_list>
const int DEFAULT_SIZE = 100;
template <typename T>
struct Triple
{
    int row, col;
    T value;
    Triple(int r = 0, int c = 0, T v = T()) : row(r), col(c), value(v) {}
    Triple<T> &operator=(const Triple<T> &t)
    {
        row = t.row;
        col = t.col;
        value = t.value;
        return *this;
    }
};
template <typename T>
class SparseMatrix
{
private:
    int rows, cols, terms;
    Triple<T> *elem;
    int maxTerms;

public:
    SparseMatrix(int maxSize = DEFAULT_SIZE);
    SparseMatrix(int r, int c, int t, std::initializer_list<Triple<T>> list, int maxSize = DEFAULT_SIZE);
    ~SparseMatrix();
    SparseMatrix<T> &operator=(const SparseMatrix<T> &sm);
    void Transpose(SparseMatrix<T> &sm) const;
    void Add(const SparseMatrix<T> &sm1, const SparseMatrix<T> &sm2);
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const SparseMatrix<U> &sm);
};

template <typename T>
SparseMatrix<T>::SparseMatrix(int maxSize) : rows(0), cols(0), terms(0), maxTerms(maxSize)
{
    elem = new Triple<T>[maxTerms];
}

template <typename T>
SparseMatrix<T>::SparseMatrix(int r, int c, int t, std::initializer_list<Triple<T>> list, int maxSize)
    : rows(r), cols(c), terms(t), maxTerms(maxSize)
{
    elem = new Triple<T>[maxTerms];
    int i = 0;
    for (const auto &triple : list)
    {
        if (i < maxTerms)
        {
            elem[i++] = triple;
        }
        else
        {
            break;
        }
    }
}

template <typename T>
SparseMatrix<T>::~SparseMatrix()
{
    delete[] elem;
}

template <typename T>
SparseMatrix<T> &SparseMatrix<T>::operator=(const SparseMatrix<T> &sm)
{
    if (this != &sm)
    {
        delete[] elem;
        rows = sm.rows;
        cols = sm.cols;
        terms = sm.terms;
        maxTerms = sm.maxTerms;
        elem = new Triple<T>[maxTerms];
        for (int i = 0; i < terms; ++i)
        {
            elem[i] = sm.elem[i];
        }
    }
    return *this;
}

template <typename T>
void SparseMatrix<T>::Transpose(SparseMatrix<T> &sm) const
{
    int *rowSize = new int[cols]();
    int *rowStart = new int[cols]();
    sm.rows = cols;
    sm.cols = rows;
    sm.terms = terms;
    for (int i = 0; i < terms; ++i)
    {
        rowSize[elem[i].col]++;
    }
    for (int i = 1; i < cols; ++i)
    {
        rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
    }
    for (int i = 0; i < terms; ++i)
    {
        int col = elem[i].col;
        int pos = rowStart[col]++;
        sm.elem[pos].row = col;
        sm.elem[pos].col = elem[i].row;
        sm.elem[pos].value = elem[i].value;
    }
    delete[] rowSize;
    delete[] rowStart;
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const SparseMatrix<U> &sm)
{
    if (sm.terms == 0)
    {
        os << "Empty Sparse Matrix" << std::endl;
        return os;
    }
    os << "Rows: " << sm.rows << ", Columns: " << sm.cols << ", Non-zero terms: " << sm.terms << std::endl;
    for (int i = 0; i < sm.terms; ++i)
    {
        os << "(" << sm.elem[i].row << ", " << sm.elem[i].col << ") = " << sm.elem[i].value << std::endl;
    }
    return os;
}

template <typename T>
void SparseMatrix<T>::Add(const SparseMatrix<T> &sm1, const SparseMatrix<T> &sm2)
{
    if (sm1.rows != sm2.rows || sm1.cols != sm2.cols)
    {
        throw std::invalid_argument("Matrices dimensions do not match for addition.");
    }
    rows = sm1.rows;
    cols = sm1.cols;
    terms = 0;
    int i = 0, j = 0;
    while (i < sm1.terms && j < sm2.terms)
    {
        if (sm1.elem[i].row < sm2.elem[j].row || (sm1.elem[i].row == sm2.elem[j].row && sm1.elem[i].col < sm2.elem[j].col))
        {
            elem[terms++] = sm1.elem[i++];
        }
        else if (sm1.elem[i].row > sm2.elem[j].row || (sm1.elem[i].row == sm2.elem[j].row && sm1.elem[i].col > sm2.elem[j].col))
        {
            elem[terms++] = sm2.elem[j++];
        }
        else
        {
            T summedValue = sm1.elem[i].value + sm2.elem[j].value;
            if (summedValue != T())
            {
                elem[terms++] = Triple<T>(sm1.elem[i].row, sm1.elem[i].col, summedValue);
            }
            i++;
            j++;
        }
    }
    while (i < sm1.terms)
    {
        elem[terms++] = sm1.elem[i++];
    }
    while (j < sm2.terms)
    {
        elem[terms++] = sm2.elem[j++];
    }
}

int main()
{
    std::cout << "===== Sparse Matrix Test Program =====" << std::endl
              << std::endl;

    // Test 1: Create and initialize first matrix with initializer list
    std::cout << "Test 1: Create Matrix A (3x3)" << std::endl;
    SparseMatrix<int> matrixA(3, 3, 3, {Triple<int>(0, 1, 5), Triple<int>(1, 2, 3), Triple<int>(2, 0, 7)});
    std::cout << matrixA << std::endl;

    // Test 2: Transpose matrix A
    std::cout << "Test 2: Transpose of Matrix A" << std::endl;
    SparseMatrix<int> matrixAT(100);
    matrixA.Transpose(matrixAT);
    std::cout << matrixAT << std::endl;

    // Test 3: Create second matrix
    std::cout << "Test 3: Create Matrix B (3x3)" << std::endl;
    SparseMatrix<int> matrixB(3, 3, 2, {Triple<int>(0, 1, 2), Triple<int>(2, 0, 4)});
    std::cout << matrixB << std::endl;

    // Test 4: Add matrices
    std::cout << "Test 4: Matrix A + Matrix B" << std::endl;
    SparseMatrix<int> matrixSum(100);
    matrixSum.Add(matrixA, matrixB);
    std::cout << matrixSum << std::endl;

    // Test 5: Assignment operator
    std::cout << "Test 5: Assignment (Matrix C = Matrix A)" << std::endl;
    SparseMatrix<int> matrixC(100);
    matrixC = matrixA;
    std::cout << matrixC << std::endl;

    // Test 6: Empty matrix transpose
    std::cout << "Test 6: Transpose Empty Matrix" << std::endl;
    SparseMatrix<int> emptyMatrix(2, 2, 0, {});
    SparseMatrix<int> emptyTransposed(100);
    emptyMatrix.Transpose(emptyTransposed);
    std::cout << emptyTransposed << std::endl;

    // Test 7: Large matrix transpose with double values
    std::cout << "Test 7: Large Matrix Transpose (5x4)" << std::endl;
    SparseMatrix<double> largeMatrix(5, 4, 4, {Triple<double>(0, 0, 1.5), Triple<double>(1, 2, 2.3), Triple<double>(3, 1, 4.7), Triple<double>(4, 3, 8.9)});
    std::cout << "Original:" << std::endl
              << largeMatrix << std::endl;
    SparseMatrix<double> largeTransposed(100);
    largeMatrix.Transpose(largeTransposed);
    std::cout << "Transposed:" << std::endl
              << largeTransposed << std::endl;

    // Test 8: Matrix addition with different elements
    std::cout << "Test 8: Matrix D + Matrix E" << std::endl;
    SparseMatrix<int> matrixD(3, 3, 2, {Triple<int>(0, 0, 1), Triple<int>(1, 1, 2)});
    SparseMatrix<int> matrixE(3, 3, 2, {Triple<int>(0, 0, 3), Triple<int>(2, 2, 4)});
    SparseMatrix<int> matrixDE(100);
    matrixDE.Add(matrixD, matrixE);
    std::cout << matrixDE << std::endl;

    std::cout << "===== All Tests Completed =====" << std::endl;
    return 0;
}