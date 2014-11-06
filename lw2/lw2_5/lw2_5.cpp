#include "stdafx.h"

using namespace std;

const int PARAMS_COUNT = 5;
const int BITS_IN_CHAR = 8;
const char* CRYPT_ARGUMENT = "crypt";
const char* DECRYPT_ARGUMENT = "decrypt";

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

struct CryptorType
{
    unsigned char key;
    void(*cryptorFunc)(char&, CryptorType const &);
    int * bitMask;
};

typedef void(*CryptFuncPtrType)(char&, CryptorType const &);

char GetBits(char x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
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

void SwitchBits(char & ch, BitOrderType type, int *bitMask)
{
    char modifiedCh = 0;
    for (int i = 0; i < BITS_IN_CHAR; ++i)
    {
        if (type == BitOrderType::Revers)
        {
            modifiedCh |= GetBits(ch, i, 1) << bitMask[i];
        }
        else
        {
            modifiedCh |= GetBits(ch, bitMask[i], 1) << i;
        }
    }
    ch = modifiedCh;
}

void Crypt(char & ch, CryptorType const& cryptor)
{
    ch ^= cryptor.key;
    SwitchBits(ch, BitOrderType::Revers, cryptor.bitMask);
}

void Decrypt(char & ch, CryptorType const& cryptor)
{
    SwitchBits(ch, BitOrderType::Right, cryptor.bitMask);
    ch ^= cryptor.key;
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

void ProcessCrypting(ifstream & input, ofstream & output, CryptorType const& cryptor)
{
    char ch;
    while (input.peek() != EOF)
    {
        ReadCharBinary(input, &ch);
        (*cryptor.cryptorFunc)(ch, cryptor);
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

    int bitMask[BITS_IN_CHAR] = { 2, 3, 4, 6, 7, 0, 1, 5 };

    CryptorType cryptor;
    cryptor.bitMask = bitMask;
    cryptor.cryptorFunc = GetCryptFuncByMode(argv[1]);
    if (!cryptor.cryptorFunc)
    {
        PrintErrorByCode(ErrorCodeType::ParsingModeParameter);
        return 1;
    }

    if (!ParseKey(argv[4], &cryptor.key))
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

    ProcessCrypting(input, output, cryptor);

    input.close();
    output.close();

    return 0;
}