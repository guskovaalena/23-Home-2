#include <iostream>
#include "matrix.h"

int main() {

    setlocale(LC_ALL, "ru");

    std::cout<<"Для матрицы A: "<<std::endl;
    matrix<int> A;
    std::cout<<"Матрица А:"<<std::endl;
    std::cout<<A;

    std::cout<<"Для матрицы B: "<<std::endl;
    matrix<int> B;
    std::cout<<"Матрица B:"<<std::endl;
    std::cout<<B;

    std::cout<<std::endl;

    std::string path = "input.txt";
    matrix<int> F(path);
    std::cout<<"Матрица F из файла input.txt"<<std::endl;
    std::cout<<F;

    //вывод матрицы F в файл output.txt
    matrix<int>::printToFile(F, "output.txt");

    std::cout<<std::endl;

    //сумма матриц
    try {
        matrix<int> C = A + B;
        std::cout<<"Матрица C=A+B:"<<std::endl;
        std::cout << C;
    }
    catch (const char* errorMessage){
        std::cout<<errorMessage<<std::endl;
    }

    std::cout<<std::endl;

    //разность матриц
    try {
        matrix<int> C = A - B;
        std::cout<<"Матрица C=A-B:"<<std::endl;
        std::cout << C;
    }
    catch (const char* errorMessage){
        std::cout<<errorMessage<<std::endl;
    }

    std::cout<<std::endl;

    //произведение матриц
    try {
        matrix<int> C = A * B;
        std::cout<<"Матрица C=A*B:"<<std::endl;
        std::cout << C;
    }
    catch (const char* errorMessage){
        std::cout<<errorMessage<<std::endl;
    }

    std::cout<<std::endl;

    //умножение матрицы на число
    matrix<int> C = A * 10;
    std::cout<<"Матрица C=A*10:"<<std::endl;
    std::cout << C;

    std::cout<<std::endl;

    //нулевая матрица
    std::cout<<"Нулевая матрица:"<<std::endl;
    matrix<int> O = matrix<int>::createZeroMatrix(3, 3);
    std::cout<<O;

    std::cout<<std::endl;

    //едииничная матрица
    std::cout<<"Единичная матрица:"<<std::endl;
    matrix<int> E = matrix<int>::createIdentityMatrix(3, 3);
    std::cout << E;

    std::cout<<std::endl;

    //сравнение матриц
    std::cout<<"Сравнение матриц A и B:"<<std::endl;
    if (A == B){
        std::cout<<"Матрицы A и B равны"<<std::endl;
    }
    if (A != B){
        std::cout<<"Матрицы A и B не равны"<<std::endl;
    }

    std::cout<<std::endl;

    std::cout<<"Транспонированная матрица A:"<<std::endl;
    //транспонирование матрицы
    std::cout<<matrix<int>::transpose(A);

    std::cout<<std::endl;

    matrix<double> M(3, 3);
    M.set();

    std::cout<<std::endl;

    try {
        //пример работы функции вычисления определителя матрицы
        std::cout << "Определитель матрицы M:" << std::endl;
        std::cout << matrix<double>::determinant(M) << std::endl << std::endl;
    } catch (const char* errorMessage){
        std::cout<<errorMessage<<std::endl;
    }

    try {
        //пример работы нахождения обратной матрицы
        std::cout<<"Обратная матрица к матрице M:"<<std::endl;
        std::cout<<!M;
    } catch (const char* errorMessage){
        std::cout<<errorMessage<<std::endl;
    }

    return 0;
}
