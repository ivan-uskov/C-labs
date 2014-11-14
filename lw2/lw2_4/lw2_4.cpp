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

typedef bool(*RLEProcessor)(ifstream&, ofstream&, ErrorCodeType&);

RLEChunk ReadChunk(ifstream &input)
{
    RLEChunk chunk;
    input.read(reinterpret_cast<char*>(&chunk), sizeof(chunk));
    return chunk;
}

void ReadCharSequence(ifstream& input, RLEChunk & chunk)
{
    chunk.val = input.get();
    chunk.count = 1;
    while (!input.eof() && (chunk.val == input.peek()) && (chunk.count < UCHAR_MAX))
    {
        chunk.val = input.get();
        ++chunk.count;
    }
}

void WriteChunk(ofstream &output, RLEChunk const& chunk)
{
    output.write(reinterpret_cast<const char*>(&chunk), sizeof(chunk));
}

void ExpandChunk(ofstream &output, RLEChunk const& chunk)
{
    for (int i = 0; i < chunk.count; ++i)
    {
        output.put(chunk.val);
    }
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

bool Pack(ifstream& input, ofstream& output, ErrorCodeType &errorCode)
{
    RLEChunk chunk;
    while (!input.eof())
    {
        ReadCharSequence(input, chunk);
        WriteChunk(output, chunk);
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

    RLEChunk chunk;
    while (input.peek() != EOF)
    {
        chunk = ReadChunk(input);
        ExpandChunk(output, chunk);
    }
    return true;
}

RLEProcessor GetProgramByMode(const char* str)
{
    RLEProcessor funcPtr = nullptr;
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

    RLEProcessor processor = GetProgramByMode(argv[1]);
    if (!processor)
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
    if (!(*processor)(input, output, errorCode))
    {
        PrintErrorByCode(errorCode);
        return 1;
    }

    input.close();
    output.close();

    return 0;
}