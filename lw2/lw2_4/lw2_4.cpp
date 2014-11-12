#include "stdafx.h"

using namespace std;

const int PARAMS_COUNT = 4;
const char* PACK_ARGUMENT = "pack";
const char* UNPACK_ARGUMENT = "unpack";

enum class ErrorCodeType
{
    OpenFiles,
    ParsingModeParameter,
    WrongParamsNumber,
    PackedFileDamaged
};

struct RLEChunk
{
    unsigned char count;
    char val;
};

typedef bool(*RleCompressorPtrType)(ifstream&, ofstream&, ErrorCodeType&);

void ReadCharBinary(ifstream & input, char * ch)
{
    input.read(ch, sizeof(*ch));
}

void WriteChunk(ofstream &output, RLEChunk const& chunk)
{
    output.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
}

void ExpandChunk(ofstream &output, RLEChunk const& symbol)
{
    for (int i = 0; i < symbol.count; ++i)
    {
        output.put(symbol.val);
    }
}

RLEChunk ReadChunk(ifstream &input)
{
    RLEChunk chunk;
    ReadCharBinary(input, reinterpret_cast<char*>(&chunk.count));
    ReadCharBinary(input, &chunk.val);
    return chunk;
}

streamoff GetFileSize(ifstream & input)
{
    auto currPos = input.tellg();
    input.seekg(0, ios::end);
    auto size = input.tellg();
    input.seekg(currPos, ios::beg);
    return size;
}

bool CanUnpack(ifstream & input)
{
    return (GetFileSize(input) % 2 == 0);
}

void ReadSymbolUpacked(ifstream& input, RLEChunk & symbol)
{
    ReadCharBinary(input, &symbol.val);
    symbol.count = 1;
    while (!input.eof() && (symbol.val == input.peek()) && (symbol.count < UCHAR_MAX))
    {
        ReadCharBinary(input, &symbol.val);
        ++symbol.count;
    }
}

bool Pack(ifstream& input, ofstream& output, ErrorCodeType &errorCode)
{
    RLEChunk currSym;
    while (!input.eof())
    {
        ReadSymbolUpacked(input, currSym);
        WriteChunk(output, currSym);
    }
    return true;
}

bool Unpack(ifstream& input, ofstream& output, ErrorCodeType &errorCode)
{
    if (!CanUnpack(input))
    {
        errorCode = ErrorCodeType::PackedFileDamaged;
        return false;
    }

    RLEChunk currSym;
    while (input.peek() != EOF)
    {
        currSym = ReadChunk(input);
        ExpandChunk(output, currSym);
    }
    return true;
}

RleCompressorPtrType GetProgramByMode(const char* str)
{
    RleCompressorPtrType funcPtr = NULL;
    if (strcmp(str, PACK_ARGUMENT) == 0)
    {
        funcPtr = Pack;
    }
    else if (strcmp(str, UNPACK_ARGUMENT) == 0)
    {
        funcPtr = Unpack;
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
        case ErrorCodeType::PackedFileDamaged:
        {
            cout << "Can't unpack, input file damaged!" << endl;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != PARAMS_COUNT)
    {
        PrintErrorByCode(ErrorCodeType::WrongParamsNumber);
        return 1;
    }

    RleCompressorPtrType compressor = GetProgramByMode(argv[1]);
    if (!compressor)
    {
        PrintErrorByCode(ErrorCodeType::ParsingModeParameter);
        return 1;
    }

    ifstream input(argv[2], ios::in | ios::binary);
    ofstream output(argv[3], ios::out | ios::binary);
    if (input.bad() || output.bad())
    {
        PrintErrorByCode(ErrorCodeType::OpenFiles);
        return 1;
    }

    ErrorCodeType errorCode;
    if ( !(*compressor)(input, output, errorCode) )
    {
        PrintErrorByCode(errorCode);
        return 1;
    }

    input.close();
    output.close();

    return 0;
}