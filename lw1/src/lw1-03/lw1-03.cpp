#include "stdafx.h"

const char PLUS = '+';
const char MINUS = '-';
const char DIVISION = '/';
const char MULTIPLICATION = '*';
const int OPERATOR_SYMBOLS_LENGTH = 1;

const int OPERANDS_CORRECT_CODE = 0;
const int DIVISION_BY_ZERO_CODE = 1;

const int PARSE_SUCCESS_CODE = 0;
const int OPERATOR_EXPECTED_CODE = 1;
const int NUMBER_EXPECTED_CODE = 2;
const int EMPTY_ARGUMENTS_LIST_CODE = 3;

typedef double (*EVAL_OPERATOR)(double, double);

enum PARSE_FLAG
{
    Number,
    Operator
};

double addup(double x, double y)
{
    return x + y;
}

double subtract(double x, double y)
{
    return x - y;
}

double multiply(double x, double y)
{
    return x * y;
}

double divide(double x, double y)
{
    return x / y;
}

EVAL_OPERATOR getOperatorFuncByChar(const char * str)
{
    EVAL_OPERATOR operatorFunc = NULL;
    if (strlen(str) == OPERATOR_SYMBOLS_LENGTH)
    {
        switch (*str)
        {
            case PLUS:
            {
                operatorFunc = addup;
                break;
            }
            case MINUS:
            {
                operatorFunc = subtract;
                break;
            }
            case DIVISION:
            {
                operatorFunc = divide;
                break;
            }
            case MULTIPLICATION:
            {
                operatorFunc = multiply;
                break;
            }
        }
    }
    return operatorFunc;
}

int StringToInt(const char * str, bool & err)
{
    char * pLastChar = NULL;
    int param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}

double StringToDouble(const char * str, bool & err)
{
    err = false;
    double d1 = strtod(str, NULL);
    if (d1 == 0)
    {
        StringToInt(str, err);
    }
    return d1;
}

int checkOperationCorrect(double leftOperand, double rightOperand, EVAL_OPERATOR func)
{
    int code = OPERANDS_CORRECT_CODE;
    if (func == divide && rightOperand == 0)
    {
        code = DIVISION_BY_ZERO_CODE;
    }
    return code;
}

void setDoubleNull(double ** x)
{
    delete *x;
    *x = NULL;
}

void moveRightToLeftOperand(double ** leftOperand, double ** rightOperand)
{
    *leftOperand = new double;
    **leftOperand = **rightOperand;
    setDoubleNull(rightOperand);
}

void switchParseFlag(PARSE_FLAG *flag)
{
    *flag = (*flag == Number) ? Operator : Number;
}

void evalOnce(double ** leftOperand, double ** rightOperand, EVAL_OPERATOR * func)
{
    **leftOperand = (*func)(**leftOperand, **rightOperand);
    setDoubleNull(rightOperand);
    func = NULL;
}

int tryParseArgument(double ** rightOperand, EVAL_OPERATOR * func, char * arg, PARSE_FLAG parseItem)
{
    int code = PARSE_SUCCESS_CODE;
    if (parseItem == Number)
    {
        bool err;
        *rightOperand = new double;
        **rightOperand = StringToDouble(arg, err);
        code = (err) ? NUMBER_EXPECTED_CODE : code;
    }
    else
    {
        *func = getOperatorFuncByChar(arg);
        code = (*func == NULL) ? OPERATOR_EXPECTED_CODE : code;
    }
    return code;
}

int tryEvalExprassionOnce(double ** leftOperand, double ** rightOperand, EVAL_OPERATOR * func)
{
    int code = OPERANDS_CORRECT_CODE;
    bool operandsExists = (*leftOperand != NULL && *rightOperand != NULL && func != NULL);
    if (operandsExists)
    {
        code = checkOperationCorrect(**leftOperand, **rightOperand, *func);
        if (code == OPERANDS_CORRECT_CODE)
        {
            evalOnce(leftOperand, rightOperand, func);
        }
    }
    return code;
}

void printArgumentParseErrorCode(int code, char* arg, int argKey)
{
    switch (code)
    {
        case OPERATOR_EXPECTED_CODE:
        {
            printf("\nParse Error : Unexpected parameter '%s' on position '%d', expected Operator\n", arg, argKey);
            break;
        }
        case NUMBER_EXPECTED_CODE:
        {
            printf("\nParse Error : Unexpected parameter '%s' on position '%d', expected Number\n", arg, argKey);
            break;
        }
        case EMPTY_ARGUMENTS_LIST_CODE:
        {
            printf("Program eval arithmetic expression of its command line arguments.\n");
            break;
        }
    }
}

void printOperandsErrorCode(int code)
{
    switch (code)
    {
        case DIVISION_BY_ZERO_CODE:
        {
            printf("\nEval Error: Division by zero!\n");
            break;
        }
    }
}

int main(int argc, char * argv[])
{
    if (argc <= 1)
    {
        printArgumentParseErrorCode(EMPTY_ARGUMENTS_LIST_CODE, argv[0], argc);
        return 0;
    }

    PARSE_FLAG currParseItem = Number;
    EVAL_OPERATOR currEvalFunc = NULL;
    double *leftOperand = NULL; 
    double *rightOperand = NULL;
    int code;

    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);

        code = tryParseArgument(&rightOperand, &currEvalFunc, argv[i], currParseItem);
        if (code != PARSE_SUCCESS_CODE)
        {
            printArgumentParseErrorCode(code, argv[i], i);
            return 1;
        }

        code = tryEvalExprassionOnce(&leftOperand, &rightOperand, &currEvalFunc);
        if (code != OPERANDS_CORRECT_CODE)
        {
            printOperandsErrorCode(code);
            return 1;
        }

        switchParseFlag(&currParseItem);
        if (leftOperand == NULL)
        {
            moveRightToLeftOperand(&leftOperand, &rightOperand);
        }
    }
    printf("= %.3f", *leftOperand);
    return 0;
}