#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct MATRIX
{
    int rows;
	int cols;
	int ** values;
};
 
void initialize(MATRIX & matrix, int rows, int cols)
{
	matrix.rows = rows;
	matrix.cols = cols;
	matrix.values = new int * [matrix.rows];
	for (int i = 0; i < rows; i++)
	{
		matrix.values[i] = new int [matrix.cols];
	}
}


void printMatrix(const MATRIX &matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            std::cout << std::setw(3) << matrix.values[i][j] << " ";
        }
        cout << endl;
    }
}



void clear(MATRIX & matrix)
{
	// todo: free matrix memory
	for (int i = 0; i < matrix.rows; i++) {
        delete[] matrix.values[i];
    }
    delete[] matrix.values;
    matrix.values = nullptr;
}


bool addition(MATRIX const & matrixA, MATRIX const & matrixB, MATRIX & matrixC)
{
	// check matrices dimensions
	if (matrixA.rows != matrixB.rows || matrixA.cols != matrixB.cols)
	{
		return false;
	}
	initialize(matrixC, matrixA.rows, matrixA.cols);
    //todo: compute matrixC = matrixA + matrixB
	for (int i = 0; i < matrixC.rows; i++)
	{
		for (int j = 0; j < matrixC.cols; j++)
		{
			matrixC.values[i][j] = matrixA.values[i][j] + matrixB.values[i][j];
		}
	}
    return true;
}


bool multiplication(const MATRIX & matrixA, const MATRIX & matrixB, MATRIX & prodMatrix)
{
	//todo: compute matrixC = matrixA x matrixB
	if (matrixA.cols == matrixB.rows)
	{
		int value;
		initialize(prodMatrix, matrixA.rows, matrixB.cols);
		for (int i=0; i< matrixA.rows; i++){
			for (int j=0; j < matrixB.cols; j++){
				value = 0;
				for(int k=0; k<matrixA.cols; k++)
					value += matrixA.values[i][k] * matrixB.values[k][j];
				prodMatrix.values[i][j] = value;
			}
		}
		return true;
	}
	else
		return false;
}


void fillRandom(MATRIX & matrix)
{
    // fill matrix with random numbers
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			//matrix.values[i][j] = std::rand();
			matrix.values[i][j] = rand()%11 ;
		}
	}
}
 
void fillFloyd(MATRIX & matrix)
{
    // fill matrix as Floyd triangle
    for(int i=0; i<matrix.rows; i++){
    	for(int j=0; j<matrix.cols; j++){
    		if(j <= i)
    			matrix.values[i][j] = i + j + 1;
    		else
    			matrix.values[i][j] = 0;
    	}
    }
}
 
int main() {
    srand(time(0));
    
    // ask user matrices dimension
    int dimension;
    cout << "Dimension Matrix : ";
    cin >> dimension;
    
    MATRIX matrixA;
    MATRIX matrixB;
    MATRIX sumMatrix;
    MATRIX prodMatrix;
    
    initialize(matrixA, dimension, dimension);
    initialize(matrixB, dimension, dimension);
    
    fillRandom(matrixA);
    fillFloyd(matrixB);
    
    addition(matrixA, matrixB, sumMatrix);
    multiplication(matrixA, matrixB, prodMatrix);
    
    // print matrix
    cout << "Matrix A"<< endl;
    printMatrix(matrixA);
    
	cout << "Matrix B"<< endl;
    printMatrix(matrixB);
    
    cout << "Matrix Sum"<< endl;
    printMatrix(sumMatrix); 
    cout << "Matrix product" << endl;
    printMatrix(prodMatrix);
    
    // free memory
    clear(matrixA);
    clear(matrixB);
    clear(prodMatrix);
    clear(sumMatrix);
    
   return 0;
}
