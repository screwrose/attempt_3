#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
    private:
        double rows;
        double columns;
        vector<vector<double>> data;

    public:

    Matrix();                       //default constructor
    Matrix(int rows, int columns);  //constructor with parameters
    Matrix(const Matrix& other);    //copy constructor
    ~Matrix();                      //destructor

    friend istream& operator>>(istream& in, Matrix& matrix);        //overloaded stream extraction >>, used to get user input
    friend ostream& operator<<(ostream& out, const Matrix& matrix); //overloaded stream insertion <<, used to print matrices

    Matrix &operator=(const Matrix& other); //assignment operator overload

    //overloaded arithmetical operators:
    Matrix operator+(const Matrix& other) const; // +
    Matrix operator-(const Matrix& other) const; // -
    Matrix operator*(const Matrix& other) const; // *
    Matrix operator/(const Matrix& other) const; // /

    double determinant() const;         //determinant calculation
    void inverse(const Matrix& other);  //inverse matrix calculator


};

Matrix::Matrix() : rows(0), columns(0) {}                                                                       //default constructor
Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns), data(rows, vector<double>(columns)) {}    //constructor with parameters
Matrix::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns), data(other.data) {}             //copy constructor
Matrix::~Matrix() {}                                                                                            //destructor

//get user input
istream& operator>>(istream& in, Matrix& matrix)
{
    cout << "Enter the amount of rows: ";
    in >> matrix.rows;
    cout << "Enter the amount of columns: ";
    in >> matrix.columns;

    matrix.data.resize(matrix.rows, vector<double>(matrix.columns));

    cout << "Enter the matrix elements:" << endl;
    for (int i = 0; i < matrix.rows; i++) 
    {
        for (int j = 0; j < matrix.columns; j++) 
        {
            in >> matrix.data[i][j];
        }
    }
    return in;
}

//print matrices
ostream& operator<<(ostream& out, const Matrix& matrix) 
{
    out << "Matrix Size: " << matrix.rows << " x " << matrix.columns << endl;
    for (int i = 0; i < matrix.rows; i++) 
    {
        for (int j = 0; j < matrix.columns; j++) 
        {
            out << matrix.data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}


//assignment operator
Matrix&Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        rows = other.rows;
        columns = other.columns;
        data = other.data;
    }
    return *this;
}

//matrix sum
Matrix Matrix::operator+(const Matrix& other) const 
{
    Matrix result(rows, columns);
    if (rows != other.rows || columns != other.columns) 
    {
        cout << "Error: The dimension of the matrices do not match, therefore they cannot be summed" << endl;
        return result;
    }
    result.data.resize(rows, vector<double>(columns));
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

//matrix subtract
Matrix Matrix::operator-(const Matrix& other) const 
{
    Matrix result(rows, columns);
    if (rows != other.rows || columns != other.columns) 
    {
        cout << "Error: The dimension of the matrices do not match, therefore they cannot be subtracted" << endl;
        return result;
    }
    result.data.resize(rows, vector<double>(columns));
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

//matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const
{
    Matrix result(rows, other.columns);
    if (columns != other.rows) {
        cout << "Error: The amount of columns of matrix A is not equivalent to the amount of rows of matrix B. They cannot be multiplied." << endl;
        return result;
    }
    result.data.resize(rows, vector<double>(other.columns));
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < other.columns; j++) 
        {
            for (int k = 0; k < columns; k++) 
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

//matrix "division"
/*Matrix Matrix::operator/(const Matrix& other) const
{
    cout << "Now, there is no such thing as 'matrix division'. The closest we can get to the concept of dividing matrices,  is to get the inverse of a matrix" << endl 
    << "and then use this inverse as a participant in a multiplication operation with another matrix." << endl;

}
*/


//determinant
double Matrix::determinant() const
{
    if ( rows != columns )
    {
        cout << "The matrix is not square, therefore a determinant cannot be calculated.";
        return 0.0;
    }

    vector<vector<double>> tempData = data; //clone the vector holding the values of the matrix
    int n = rows;
    double det = 1.0;
    for (int i=0; i<n; i++) 
    {
        int maxRow = i;
        for (int j= i+1 ; j< n; j++) 
        {
            if (abs(tempData[j][i]) > abs(tempData[maxRow][i])) 
            {
                maxRow = j;
            }
        }
        if (maxRow != i) 
        {
            swap(tempData[i], tempData[maxRow]);
            det *= -1.0;
        }
        if (tempData[i][i] == 0.0) 
        {
            return 0.0;
        }
        det *= tempData[i][i];
        for (int j = i + 1; j < n; j++) 
        {
            double factor = tempData[j][i] / tempData[i][i];
            for (int k = i + 1; k < n; k++) 
            {
                tempData[j][k] -= factor * tempData[i][k];
            }
        }
    }
    return det;
}

int main()
{
    Matrix A;
    cin >> A;
    cout << "Matrix A is: ";
    cout << A << endl;

    Matrix B;
    cin >> B;
    cout << "Matrix B is: ";
    cout << B << endl;

    Matrix C = A + B;
    cout << "A + B is: ";
    cout << C << endl;

    Matrix D = A - B;
    cout << "A - B is: ";
    cout << D << endl;

    Matrix E = A * B;
    cout << "A * B is: ";
    cout << E << endl;

    cout << "The determinant of A is: " << A.determinant() << endl;

    return 0;
}