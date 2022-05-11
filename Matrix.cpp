//BOOLEAN VERSION OF MY MATRIX CLASS
#include "Matrix.h"

int Matrix::counter = 0;

bool Matrix::operator()(int i, int j) const{
    return matrix[i][j];
}
bool& Matrix::operator()(int i, int j){
    return matrix[i][j];
}

Matrix Matrix::operator+(const Matrix &other) const{
    Matrix temp;
    if(rows == other.rows && cols == other.cols){
        temp.reAllocate(rows,cols);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                temp.set(matrix[i][j] + other.matrix[i][j], i, j);
            }
            
            
        }return temp;
    }
    //if some kind of sum is still possible (same number of elements) returns a sum matrix shaped as the first
    if(rows == other.cols && cols == other.rows){
        temp.reAllocate(rows,cols);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                temp.set(matrix[i][j] + other.matrix[j][i], i, j);
            }
        }
        
    }//no possible sum formula (unless you "decide" one)
        return temp;
}

Matrix Matrix::operator*(const Matrix& other) const{
    Matrix temp;
    if (cols != other.rows) return temp;
    std::cout << "Matrix crime! check your matrices" << std::endl;
    temp.reAllocate(rows, other.cols);
    temp.zero();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            for (int k = 0; k < other.rows; k++) {
                temp.add(matrix[i][k] * other.matrix[k][j], i, j);
            }
        }
    }return temp;

}

Matrix& Matrix::operator=(const Matrix &other){
    if(this == &other) return *this;
    cols = other.cols;
    rows = other.rows;
    free();
    matrix = new bool*[rows];
    for (int k = 0; k < rows; k++){
        matrix[k] = new bool[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
    Matrix::counter++;
    return *this;

}

//copy constructor
Matrix::Matrix(const Matrix &other) {
    
    cols = other.cols;
    rows = other.rows;
    free();
    matrix = new bool*[rows];
    for (int k = 0; k < rows; k++) {
        matrix[k] = new bool[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
    Matrix::counter++;
}
//void constructor
Matrix::Matrix(){
    matrix = nullptr;
};
//default constructor
Matrix::Matrix(int r, int c){
        cols = c, rows = r;
        matrix = new bool*[rows];
        for(int k = 0; k < rows; k++){
            matrix[k] = new bool[cols];
        }
        Matrix::counter++;
}
//destructor
Matrix::~Matrix(){
        //std::cout << "\n\nEnd of scope" << std::endl;
        if(matrix != nullptr) {
            //std::cout << "Cleaning memory ./." << std::endl;
            std::cout << "destructor" << std::endl;
            for(int k = 0; k < rows; k++){
                std::cout << "destroyed " << k << std::endl;
                if (matrix[k] != nullptr){
                    delete[] matrix[k];
                    matrix[k] = nullptr;
                }
            } delete[] matrix;
            matrix = nullptr;
            std::cout << "Done..." << std::endl;
            Matrix::counter--;
       }//else std::cout << "Already cleaned at RunTime!" << std::endl;
}

//static
Matrix Matrix::create(){
    int temp_rows, temp_cols;
    std::cout << "Matrix rows: ";
    std::cin >> temp_rows;
    std::cout << "Matrix cols: ";
    std::cin >> temp_cols;
    std::cout << std::endl;
    Matrix temp(temp_rows, temp_cols);
    bool tempval;
    for(int i = 0; i < temp.col(); i ++){
        for(int j = 0; j < temp.row(); j++){
            std::cout << "M[" << i << "][" << j << "]: ";
            std::cin >> tempval;
            temp.set(tempval, i,j);
        }
    }
    return temp;
}

void Matrix::zero() const{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }return;
}
void Matrix::eye() const{
    if(cols != rows){ return; }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            i == j ? matrix[i][j] = true : matrix[i][j] = false;
        }
    }return;
}
int Matrix::row() const{
        return rows;
}
int Matrix::col() const{
        return cols;
}
void Matrix::set(bool temp, int i, int j) const{
        if(i < rows && j < cols && i >= 0 && j >= 0 && matrix != nullptr){
            matrix[i][j] = temp;
        }else if(matrix == nullptr){
            std::cout << "Matrix deleted..." << std::endl;
            return;
        }else{
            std::cout << "Out of range" << std::endl;
            return;
        }
}
void Matrix::add(bool temp, int i, int j) const{
    matrix[i][j] += temp;
}
float Matrix::get(int i, int j) const{
        if(i < rows && j < cols && i >= 0 && j >= 0 && matrix != nullptr){
            return matrix[i][j];
        }else if(matrix == nullptr){
            std::cout << "Matrix deleted..." << std::endl;
            return 0;
        }else{
            std::cout << "Out of range" << std::endl;
            return 0;
        }
}
void Matrix::compile() const{
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                bool temp;
                std::cout << "Add new element[" << i << "][" << j << "]: ";
                std::cin >> temp;
                set(temp,i,j);
                std::cout << std::endl;
            }
        }
}
void Matrix::show() const{
        if(matrix == nullptr) return;
        std::cout << std::endl;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                std::cout << "Matrix[" << i << "][" << j << "]: " << matrix[i][j] << "\t";
            }std::cout << std::endl << std::endl;     
        }
}
void Matrix::random() const{
        srand(int(time(0)));
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                set(bool(rand()%2),i,j);
            }
        }
}
//non-const object methods
void Matrix::free(){
        if(matrix != nullptr){
            std::cout << "free" << std::endl;
            for(int k = 0; k < rows; k++){
                std::cout << "freed" << k << std::endl;
                if (matrix[k] != nullptr){
                    delete[] matrix[k];
                    matrix[k] = nullptr;
                }
            }delete[] matrix;
            matrix = nullptr;
            std::cout << "Memory area cleaned!" << std::endl;
            Matrix::counter--;
        }else{
            return;
        }
}
void Matrix::reAllocate(int r, int c){
        free();
        Matrix::counter++;
        rows = r;
        cols = c;
        
        matrix = new bool*[rows]();
        for(int k = 0; k < rows; k++){
            matrix[k] = new bool[cols];
        }
}
