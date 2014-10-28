#include "stdafx.h"

const int PARAMS_COUNT  = 2;
const int MATRIX_MAX_ID = 2;
const int MATRIX_LENGTH = MATRIX_MAX_ID + 1;
const char *OUTPUT_FORMAT = "%.2f ";

typedef float MatrixType[MATRIX_LENGTH][MATRIX_LENGTH];
typedef float MatrixLineType[MATRIX_LENGTH];

MatrixType matrix1;
MatrixType matrix2;

enum class ReadMatrixErrorCode
{
    None,
    FileNotExists,
    FileHasIncorrectFormat,
    LessParamsCount
};

bool InitMatrixLine(const char *sourseStr, MatrixLineType * line)
{
    int result = std::sscanf(sourseStr, "%f\t%f\t%f", &(*line)[0], &(*line)[1], &(*line)[2]);
    return (result == MATRIX_LENGTH);
}

bool ReadMatrix(char *fileName, MatrixType *matrix, ReadMatrixErrorCode *errorCode)
{
    std::ifstream inputFile(fileName);
    std::string buffStr;
    int stringCount = 0;

    if (inputFile.bad())
    {
        *errorCode = ReadMatrixErrorCode::FileNotExists;
        return false;
    }
    
    int result;
    while (!inputFile.eof() && stringCount < MATRIX_LENGTH)
    {
        std::getline(inputFile, buffStr);
        
        if (!InitMatrixLine(buffStr.c_str(), &(*matrix)[stringCount]))
        {
            *errorCode = ReadMatrixErrorCode::FileHasIncorrectFormat;
            return false;
        }
        
        ++stringCount;
    }
    return stringCount > MATRIX_MAX_ID;
}

void PrintReadMatrixError(ReadMatrixErrorCode code)
{
    switch (code)
    {
        case ReadMatrixErrorCode::FileNotExists:
        {
            std::cout << "First input file doesn't exists!\n";
            break;
        }
        case ReadMatrixErrorCode::FileHasIncorrectFormat:
        {
            std::cout << "Input file has incorrect format!\n";
            break;
        }
        case ReadMatrixErrorCode::LessParamsCount:
        {
            std::cout << "Expected arguments: [Matrix 1 filename] [Matrix 2 filename]\n";
            break;
        }
    }
}

void PrintMatrixMult(MatrixType *matrix1, MatrixType *matrix2)
{
    for (int i = 0; i <= MATRIX_MAX_ID; ++i)
    {
        for (int j = 0; j <= MATRIX_MAX_ID; ++j)
        {
            float sum = 0;
            for (int k = 0; k <= MATRIX_MAX_ID; ++k)
            {
                sum += (*matrix1)[i][j] * (*matrix2)[k][j];
            }
            printf(OUTPUT_FORMAT, sum);
        }
        printf("\n");
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

    if (!ReadMatrix(argv[1], &matrix1, &errorCode))
    {
        PrintReadMatrixError(errorCode);
        return 1;
    }

    if (!ReadMatrix(argv[2], &matrix2, &errorCode))
    {
        PrintReadMatrixError(errorCode);
        return 1;
    }

    PrintMatrixMult(&matrix1, &matrix2);

    return 0;
}