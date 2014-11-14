#include "stdafx.h"

using namespace std;

const int PARAMS_COUNT = 5;
const char* CRYPT_ARGUMENT = "crypt";
const char* DECRYPT_ARGUMENT = "decrypt";
const int BIT_MASK[CHAR_BIT] = { 2, 3, 4, 6, 7, 0, 1, 5 };


enum class ErrorCodeType
{
    OpenFiles,
    ParsingModeParameter,
    WrongParamsNumber,
    ParsingKeyParameter
};

enum class BitOrderType
{
    Right,
    Revers
};

typedef void(*CryptFuncPtrType)(char&, const unsigned char);

char GetBit(char x, int p)
{
    return (x >> p) & 1;
}

bool ParseKey(char * keyStr, unsigned char * keyNum)
{
    char * pLastChar = NULL;
    *keyNum = static_cast<unsigned char>(strtol(keyStr, &pLastChar, 10));
    return !((*keyStr == '\0') || (*pLastChar != '\0'));
}

void ReadCharBinary(ifstream & input, char * ch)
{
    input.read(ch, sizeof(*ch));
}

void PrintCharBinary(ofstream & output, char ch)
{
    output.write(&ch, sizeof(ch));
}

char EncodeBits(const char ch)
{
    char modifiedCh = 0;
    for (int i = 0; i < CHAR_BIT; ++i)
    {
        modifiedCh |= GetBit(ch, i) << BIT_MASK[i];
    }
    return modifiedCh;
}

char DecodeBits(const char ch)
{
    char modifiedCh = 0;
    for (int i = 0; i < CHAR_BIT; ++i)
    {
        modifiedCh |= GetBit(ch, BIT_MASK[i]) << i;
    }
    return modifiedCh;
}

void Crypt(char & ch, const unsigned char key)
{
    ch ^= key;
    ch = EncodeBits(ch);
}

void Decrypt(char & ch, const unsigned char key)
{
    ch = DecodeBits(ch);
    ch ^= key;
}

CryptFuncPtrType GetCryptFuncByMode(const char* str)
{
    CryptFuncPtrType funcPtr = NULL;
    if (strcmp(str, CRYPT_ARGUMENT) == 0)
    {
        funcPtr = Crypt;
    }
    else if (strcmp(str, DECRYPT_ARGUMENT) == 0)
    {
        funcPtr = Decrypt;
    }
    return funcPtr;
}

void PrintErrorByCode(const ErrorCodeType errorCode)
{
    switch (errorCode)
    {
        case ErrorCodeType::OpenFiles:
        {
            cout << "Can't Open Files!" << endl;
            break;
        }
        case ErrorCodeType::ParsingModeParameter:
        {
            cout << "Invalid mode parameter\nUsage: [pack | unpack]" << endl;
            break;
        }
        case ErrorCodeType::WrongParamsNumber:
        {
            cout << "Wrong number of parameters!" << endl;
            break;
        }
        case ErrorCodeType::ParsingKeyParameter:
        {
            cout << "Invalid Key parameter" << endl;
            break;
        }
    }
}

void ProcessCrypting(ifstream & input, ofstream & output, const unsigned char key, CryptFuncPtrType cryptor)
{
    char ch;
    while (input.peek() != EOF)
    {
        ReadCharBinary(input, &ch);
        (*cryptor)(ch, key);
        PrintCharBinary(output, ch);
    }
}

int main(int argc, char* argv[])
{
    if (argc != PARAMS_COUNT)
    {
        PrintErrorByCode(ErrorCodeType::WrongParamsNumber);
        return 1;
    }

    CryptFuncPtrType cryptor = GetCryptFuncByMode(argv[1]);
    if (!cryptor)
    {
        PrintErrorByCode(ErrorCodeType::ParsingModeParameter);
        return 1;
    }

    unsigned char key;
    if (!ParseKey(argv[4], &key))
    {
        PrintErrorByCode(ErrorCodeType::ParsingKeyParameter);
        return 1;
    }

    ifstream input(argv[2], ios::in | ios::binary);
    ofstream output(argv[3], ios::out | ios::binary);
    if (input.bad() || output.bad())
    {
        PrintErrorByCode(ErrorCodeType::OpenFiles);
        return 1;
    }

    ProcessCrypting(input, output, key, cryptor);

    input.close();
    output.close();

    return 0;
}