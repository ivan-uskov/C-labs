#include "stdafx.h"

const char PLUS = '+';
const char MINUS = '-';
const char DIVISION = '/';
const char MULTIPLICATION = '*';
const int OPERATOR_SYMBOLS_LENGTH = 1;

typedef double (*EVAL_OPERATOR)(double, double);

enum PARSE_STATUS
{
    ParseSuccess,
    OperatorExpected,
    NumberExpected,
    EmptyArgumentsList
};

enum EVAL_STATUS
{
    OperadsCorrect,
    DivisionByZero
};

enum PARSE_FLAG
{
    Number,
    Operator
};

double Addup(double x, double y)
{
    return x + y;
}

double Subtract(double x, double y)
{
    return x - y;
}

double Multiply(double x, double y)
{
    return x * y;
}

double Divide(double x, double y)
{
    return x / y;
}

EVAL_OPERATOR GetOperatorFuncByChar(const char * str)
{
    EVAL_OPERATOR operatorFunc = NULL;
    if (strlen(str) == OPERATOR_SYMBOLS_LENGTH)
    {
        switch (*str)
        {
            case PLUS:
            {
                operatorFunc = Addup;
                break;
            }
            case MINUS:
            {
                operatorFunc = Subtract;
                break;
            }
            case DIVISION:
            {
                operatorFunc = Divide;
                break;
            }
            case MULTIPLICATION:
            {
                operatorFunc = Multiply;
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

EVAL_STATUS CheckOperationCorrect(double leftOperand, double rightOperand, EVAL_OPERATOR func)
{
    EVAL_STATUS code = OperadsCorrect;
    if (func == Divide && rightOperand == 0)
    {
        code = DivisionByZero;
    }
    return code;
}

void SetDoubleNull(double ** x)
{
    delete *x;
    *x = NULL;
}

void MoveRightToLeftOperand(double ** leftOperand, double ** rightOperand)
{
    *leftOperand = new double;
    **leftOperand = **rightOperand;
    SetDoubleNull(rightOperand);
}

void SwitchParseFlag(PARSE_FLAG *flag)
{
    *flag = (*flag == Number) ? Operator : Number;
}

void EvalOnce(double ** leftOperand, double ** rightOperand, EVAL_OPERATOR * func)
{
    **leftOperand = (*func)(**leftOperand, **rightOperand);
    SetDoubleNull(rightOperand);
    func = NULL;
}

PARSE_STATUS TryParseArgument(double ** rightOperand, EVAL_OPERATOR * func, char * arg, PARSE_FLAG parseItem)
{
    PARSE_STATUS code = ParseSuccess;
    if (parseItem == Number)
    {
        bool err;
        *rightOperand = new double;
        **rightOperand = StringToDouble(arg, err);
        code = (err) ? NumberExpected : code;
    }
    else
    {
        *func = GetOperatorFuncByChar(arg);
        code = (*func == NULL) ? OperatorExpected : code;
    }
    return code;
}

EVAL_STATUS TryEvalExprassionOnce(double ** leftOperand, double ** rightOperand, EVAL_OPERATOR * func)
{
    EVAL_STATUS status = OperadsCorrect;
    bool operandsExists = (*leftOperand != NULL && *rightOperand != NULL && func != NULL);
    if (operandsExists)
    {
        status = CheckOperationCorrect(**leftOperand, **rightOperand, *func);
        if (status == OperadsCorrect)
        {
            EvalOnce(leftOperand, rightOperand, func);
        }
    }
    return status;
}

void PrintArgumentParseErrorCode(PARSE_STATUS code, char* arg, int argKey)
{
    switch (code)
    {
        case OperatorExpected:
        {
            printf("\nParse Error : Unexpected parameter '%s' on position '%d', expected Operator\n", arg, argKey);
            break;
        }
        case NumberExpected:
        {
            printf("\nParse Error : Unexpected parameter '%s' on position '%d', expected Number\n", arg, argKey);
            break;
        }
        case EmptyArgumentsList:
        {
            printf("Program eval arithmetic expression of its command line arguments.\n");
            break;
        }
    }
}

void PrintOperandsErrorCode(EVAL_STATUS code)
{
    switch (code)
    {
        case DivisionByZero:
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
        PrintArgumentParseErrorCode(EmptyArgumentsList, argv[0], argc);
        return 0;
    }

    PARSE_FLAG currParseItem = Number;
    EVAL_OPERATOR currEvalFunc = NULL;
    double *leftOperand = NULL; 
    double *rightOperand = NULL;
    PARSE_STATUS parseStatus;
    EVAL_STATUS evalStatus;

    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);

        bool isLastArgOperator = ( (currParseItem == Operator) && (argc - 1 == i) );
        if (isLastArgOperator)
        {
            PrintArgumentParseErrorCode(NumberExpected, argv[i], i);
            return 1;
        }

        parseStatus = TryParseArgument(&rightOperand, &currEvalFunc, argv[i], currParseItem);
        if (parseStatus != ParseSuccess)
        {
            PrintArgumentParseErrorCode(parseStatus, argv[i], i);
            return 1;
        }

        evalStatus = TryEvalExprassionOnce(&leftOperand, &rightOperand, &currEvalFunc);
        if (evalStatus != OperadsCorrect)
        {
            PrintOperandsErrorCode(evalStatus);
            return 1;
        }

        SwitchParseFlag(&currParseItem);
        if (leftOperand == NULL)
        {
            MoveRightToLeftOperand(&leftOperand, &rightOperand);
        }
    }
    printf("= %.3f", *leftOperand);
    return 0;
}