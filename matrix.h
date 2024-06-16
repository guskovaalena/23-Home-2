#include <iostream>
#include <fstream>
#include <cmath>

#ifndef HW2MATRIX_MATRIX_H
#define HW2MATRIX_MATRIX_H

template <typename T>
class matrix {

private:
    int row;
    int col;
    T ** mat;

public:

    //получение значеня поля row
    int getRow() const {
        return row;
    }

    //получение значеня поля col
    int getCol() const {
        return col;
    }

    //получение значеня поля mat
    T **getMat() const {
        return mat;
    }

//private сеттеры, чтобы нельзя было изменять матрицу во время работы с ней
private:
    //изменение значеня поля row
    void setRow(int rowV) {
        row = rowV;
    }

    //изменение значеня поля col
    void setCol(int colV){
        col = colV;
    }

    //изменение значеня поля mat
    void setMat(T** matV) {
        mat = matV;
    }

public:
    //конструктор пустой матрицы заданного размера
    matrix(int rowValue, int colValue){
        row = rowValue;
        col = colValue;
        mat = new T* [row];
        for (int i = 0; i < row; i++){
            mat[i] = new T [col];
        }
    }

    //конструктор для считывания матрицы с консоли
    matrix(){
        std::cout<<"Введите размеры матрицы"<<std::endl;
        int rowV;
        int colV;
        std::cin>>rowV;
        std::cin>>colV;
        row = rowV;
        col = colV;
        mat = new T* [row];
        for (int i = 0; i < row; i++){
            mat[i] = new T [col];
        }
         T value;
        std::cout<<"Введите элементы матрицы"<<std::endl;
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                std::cin>>value;
                mat[i][j] = value;
            }
        }
    }

    //конструктор для считывния матрицы из файла
    explicit matrix(const std::string& path) {

        std::ifstream fin;
        fin.open(path);
        int rowValue, colValue;
        fin>>rowValue;
        fin>>colValue;
        row = rowValue;
        col = colValue;
        mat = new T* [row];
        for (int i = 0; i < row; i++){
            mat[i] = new T [col];
        }
        for (int i = 0; i < row; ++i){
            for (int j = 0; j < col; ++j){
                T value;
                fin>>value;
                mat[i][j] = value;
            }
        }
        fin.close();
    }

    //считывание элементов матрицы из консоли
    void set(){
        std::cout<<"Введите элементы матрицы"<<std::endl;
        T value;
        for (int i = 0; i < row; ++i){
            for (int j = 0; j < col; ++j){
                std::cin>>value;
                mat[i][j] = value;
            }
        }
    }

    //конструктор копирования
    matrix(const matrix &other){
        row = other.getRow();
        col = other.getCol();
        mat = new T *[other.getRow()];
        for (int i = 0; i < other.getRow(); i++){
            mat[i] = new T [other.getCol()];
        }
        for (int i = 0; i < other.row; ++i){
            for (int j = 0; j < other.col; ++j){
                mat[i][j] = other.getMat()[i][j];
            }
        }
    }

//вспомогательный метод для перегрузки оператора присваивания
private:
    void swap(matrix& m){

        int tmpRow = row;
        row = m.getRow();
        m.setRow(tmpRow);

        int tmpCol = col;
        col = m.getCol();
        m.setCol(tmpCol);

        T ** tmpMat = mat;
        mat = m.getMat();
        m.setMat(tmpMat);
    }

public:

    //перегрузка оператора присваивания
    matrix& operator = (const matrix& A){
        matrix tmp(A);
        swap(tmp);
        return *this;
    }

    //перегрузка оператора << для вывода матрицы в консоль
    friend std::ostream& operator<<(std::ostream &out, const matrix<T> matrix){

        for (int i = 0; i < matrix.row; i++){
            for (int j = 0; j < matrix.col; j++){
                out<<matrix.mat[i][j]<<' ';
            }
            out<<std::endl;
        }
        return out;
    }

    //вывод матрицы в файл
    static void printToFile (matrix& A, const std::string& path){
        std::ofstream fout;
        fout.open(path);
        for (int i = 0; i < A.row; i++){
            for (int j = 0; j < A.col; ++j){
                fout<<A.mat[i][j]<<' ';
            }
            fout<<std::endl;
        }
        fout.close();
    }

    //перегрузка оператора + для сложения матриц
    friend matrix operator + (matrix& A, matrix& B){

        if (A.getRow() == B.getRow() && A.getCol() == B.getCol()){
            int rowC = A.getRow();
            int colC = B.getCol();
            matrix C(rowC, colC);
            for (int i = 0; i < rowC; ++i){
                for (int j = 0; j < colC; ++j){
                    C.mat[i][j] = A.mat[i][j] + B.mat[i][j];
                }
            }
            return C;
        }
        else{
            throw "Невозможно вычислить сумму. Размер матриц не совпадает";
        }
    }

    //перегрузка оператора - для вычитания матриц
    friend matrix operator - (matrix& A, matrix& B){
        if (A.getRow() == B.getRow() && A.getCol() == B.getCol()){
            int rowC = A.getRow();
            int colC = B.getCol();
            matrix C(rowC, colC);
            for (int i = 0; i < rowC; ++i){
                for (int j = 0; j < colC; ++j){
                    C.mat[i][j] = A.mat[i][j] - B.mat[i][j];
                }
            }
            return C;
        }
        else{
           throw "Невозможно вычислить разность. Размер матриц не совпадает";
        }
    }

    //перегрузка оператора * для умножения матриц
    friend matrix operator * (matrix& A, matrix& B){
        if (A.col != B.row){
            throw "Данные матрицы нельзя перемножить";
        }
        else{
            int rowC = A.getRow();
            int colC = B.getCol();
            matrix C(rowC, colC);
            for (int i = 0; i < rowC; ++i){
                for (int j = 0; j < colC; ++j){
                    C.mat[i][j] = 0;
                    for (int k = 0; k < A.getCol(); ++k){
                        C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
                    }
                }
            }
            return C;
        }
    }

    //перегрузка оператора * для умножения матрицы на число
    friend matrix operator * (matrix& A, double x){
        int rowC = A.getRow();
        int colC = A.getCol();
        matrix C(rowC, colC);
        for (int i = 0; i < rowC; ++i){
            for (int j = 0; j < colC; ++j){
                C.mat[i][j] = A.mat[i][j] * x;
            }
        }
        return C;
    }

    //перегрузка оператора == для сравнения матриц
    friend bool operator == (matrix& A, matrix& B){
        if (A.getCol() != B.getCol() || A.getRow() != B.getRow()){
            return false;
        }
        for (int i = 0; i < A.getRow(); ++i){
            for (int j = 0; j < A.getCol(); ++j){
                if (A.mat[i][j] != B.mat[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    //перегрузка оператора != для сравнения матриц
    friend bool operator != (matrix& A, matrix& B){
        if (A.getCol() != B.getCol() || A.getRow() != B.getRow()){
            return true;
        }
        for (int i = 0; i < A.getRow(); ++i){
            for (int j = 0; j < A.getCol(); ++j){
                if (A.mat[i][j] != B.mat[i][j]){
                    return true;
                }
            }
        }
        return false;
    }

    //перегрузка оператора == для сравнения матрицы и скаляра
    friend bool operator == (matrix& A, T x){
        bool flag = true;
        for (int i = 0; i < A.getRow(); ++i){
            for (int j = 0; j < A.getCol(); ++j){
                if (i == j){
                    if (A.mat[i][j] != x){
                        flag = false;
                    }
                }
                else{
                    if (A.mat[i][j] != 0){
                        flag = false;
                    }
                }
            }
        }
        return flag;
    }

    //перегрузка оператора != для сравнения матрицы и скаляра
    friend bool operator != (matrix& A, T x){
        bool flag = true;
        for (int i = 0; i < A.getRow(); ++i){
            for (int j = 0; j < A.getCol(); ++j){
                if (i == j){
                    if (A.mat[i][j] != x){
                        flag = false;
                    }
                }
                else{
                    if (A.mat[i][j] != 0){
                        flag = false;
                    }
                }
            }
        }
        return !flag;
    }

    //функция транспонирования матрицы
    static matrix transpose(matrix& A){
        matrix transposedA(A.getCol(), A.getRow());
        for (int i = 0; i < A.getRow(); i++){
            for (int j = 0; j < A.getCol(); j++){
                transposedA.getMat()[j][i] = A.getMat()[i][j];
            }
        }
        return transposedA;
    }

private:
    //функция получения матрицы без i-ой строки и j-ого столбца
    static matrix getMatrixWithoutRowCol(matrix& A, int size, int i_row, int j_col){
        matrix newMat(size-1, size-1);
        int rowShift = 0;
        int colShift;
        for (int i = 0; i < size-1; ++i){
            if (i == i_row){
                rowShift = 1;
            }
            colShift = 0;
            for (int j = 0; j < size-1; ++j){
                if (j == j_col){
                    colShift = 1;
                }
                newMat.getMat()[i][j] = A.getMat()[i+rowShift][j+colShift];
            }
        }
        return newMat;
    }

public:

    //функция вычисления определителя матрицы
    static T determinant (matrix& A){
        if (A.getCol() != A.getRow()){
            throw "Определитель не существует";
        }
        else {
            int size = A.getRow();
            T det = 0;

            if (size == 1){
                return A.getMat()[0][0];
            }
            else if (size == 2){
                return A.getMat()[0][0] * A.getMat()[1][1] - A.getMat()[0][1] * A.getMat()[1][0];
            }
            else {
                for (int i = 0; i < size; ++i){
                    for (int j = 0; j < size; ++j){
                        if (i == 0){
                            matrix newA(matrix::getMatrixWithoutRowCol(A, A.getRow(), 0, j));
                            det = det + (pow(-1, (i + j)) * A.getMat()[i][j] * determinant(newA));
                        }
                    }
                }
                return det;
            }
        }
    }

    //перегрузка оператора ! для нахождения обратной матрицы
    friend matrix operator ! (matrix& A){
        T det = matrix<T>::determinant(A);
        if (det == 0){
            throw "Обратная матрица не существует";
        }
        else {
            T x = 1/det;
            matrix transposedA(matrix<T>::transpose(A));
            matrix inverseA(A.getRow(), A.getCol());
            for (int i = 0; i < A.getRow(); ++i){
                for (int j = 0; j < A.getCol(); ++j){
                    matrix Mij(matrix::getMatrixWithoutRowCol(transposedA, transposedA.getRow(), i, j));
                    inverseA.mat[i][j] = pow(-1, (i+j)) * matrix::determinant(Mij) * x;
                }
            }
            return inverseA;
        }
    }

    //метод для создания нулевой матрицы заданного размера
    static matrix createZeroMatrix(int rowV, int colV){
        matrix O(rowV, colV);
        T** matV;
        matV = new T* [rowV];
        for (int i = 0; i < rowV; i++){
            matV[i] = new T [colV];
        }
        for (int i = 0; i < rowV; i++){
            for (int j = 0; j < colV; j++){
                matV[i][j] = 0;
            }
        }
        O.setMat(matV);
        return O;
    }

    //метод для создания единичной матрицы заданного размера
    static matrix createIdentityMatrix(int rowV, int colV){
        matrix E(rowV, colV);
        T ** matV;
        matV = new T* [rowV];
        for (int i = 0; i < rowV; i++){
            matV[i] = new T [colV];
        }
        for (int i = 0; i < rowV; i++){
            for (int j = 0; j < colV; j++){
                if (i == j){
                    matV[i][j] = 1;
                } else{
                    matV[i][j] = 0;
                }
            }
        }
        E.setMat(matV);
        return E;
    }

    //деструктор
    ~matrix(){
        delete[] mat;
    }
};


#endif //HW2MATRIX_MATRIX_H
