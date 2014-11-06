#include "stdafx.h"

const int PARAMS_COUNT  = 2;
const int MATRIX_SIZE = 3;

typedef double ValType;
typedef ValType MatrixType[MATRIX_SIZE][MATRIX_SIZE];
typedef ValType MatrixLineType[MATRIX_SIZE];

using namespace std;

enum class ReadMatrixErrorCode
{
    None,
    FileNotExists,
    FileHasIncorrectFormat,
    LessParamsCount
};

bool ReadMatrixLineFromStr(string const& inputStr, MatrixLineType line, ReadMatrixErrorCode *errorCode)
{
    istringstream iss(inputStr);
    return static_cast<bool>( iss >> line[0] >> line[1] >> line[2] );
}

bool ReadMatrixFromStream(ifstream &input, MatrixType matrix, ReadMatrixErrorCode *errorCode)
{
    string buffStr;
    int stringCount = 0;
    while ( !input.eof() && (stringCount < MATRIX_SIZE) )
    {
        getline(input, buffStr);
        if (!ReadMatrixLineFromStr(buffStr, matrix[stringCount], errorCode))
        {
            *errorCode = ReadMatrixErrorCode::FileHasIncorrectFormat;
            break;
        }
        ++stringCount;
    }
    return stringCount >= MATRIX_SIZE;
}

bool ReadMatrix(const char *fileName, MatrixType matrix, ReadMatrixErrorCode *errorCode)
{
    ifstream input(fileName);
    string buffStr;
    int stringCount = 0;

    if (input.bad())
    {
        *errorCode = ReadMatrixErrorCode::FileNotExists;
        return false;
    }

    return ReadMatrixFromStream(input, matrix, errorCode);
}

void PrintReadMatrixError(ReadMatrixErrorCode code)
{
    switch (code)
    {
        case ReadMatrixErrorCode::FileNotExists:
        {
            cout << "First input file doesn't exists!\n";
            break;
        }
        case ReadMatrixErrorCode::FileHasIncorrectFormat:
        {
            cout << "Input file has incorrect format!\n";
            break;
        }
        case ReadMatrixErrorCode::LessParamsCount:
        {
            cout << "Expected arguments: [Matrix 1 filename] [Matrix 2 filename]\n";
            break;
        }
    }
}

void PrintMatrixMult(const MatrixType matrix1, const MatrixType matrix2)
{
    for (int row1 = 0; row1 < MATRIX_SIZE; ++row1)
    {
        for (int col = 0; col < MATRIX_SIZE; ++col)
        {
            ValType sum = 0;
            for (int row2 = 0; row2 < MATRIX_SIZE; ++row2)
            {
                sum += matrix1[row1][col] * matrix2[row2][col];
            }
            cout << sum << '\t';
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc <= PARAMS_COUNT)
    {
        PrintReadMatrixError(ReadMatrixErrorCode::LessParamsCount);
        return 1;
    }

    ReadMatrixErrorCode errorCode;

    MatrixType matrix1;
    if (!ReadMatrix(argv[1], matrix1, &errorCode))
    {
        PrintReadMatrixError(errorCode);
        return 1;
    }

    MatrixType matrix2;
    if (!ReadMatrix(argv[2], matrix2, &errorCode))
    {
        PrintReadMatrixError(errorCode);
        return 1;
    }

    PrintMatrixMult(matrix1, matrix2);

    return 0;
}