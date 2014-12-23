#include "stdafx.h"
#include "VectorProcessor.h"

using namespace std;

bool ReadVecOfDouble(std::istream & input, vector<double> & buff)
{
    buff.clear();
    istream_iterator<double> start(input);
    istream_iterator<double> end;
    copy(start, end, back_inserter(buff));

    return !buff.empty();
}

double SumPositive(vector<double> const& vec)
{
    auto positiveSumator = [](double prev, double curr)
    {
        return (curr > 0 ) ? prev + curr : prev;
    };
    return accumulate(vec.begin(), vec.end(), 0.0, positiveSumator);
}

struct CTransformer
{
public:
	CTransformer(const double positivesSum)
		: m_isEven(false)
		, m_positivesSum(positivesSum)
	{
	}

	double operator() (double i)
	{
		auto modified = (m_isEven) ? i - m_positivesSum : i * 2;
		m_isEven = !m_isEven;
		return modified;
	}

private:
	bool m_isEven;
	const double m_positivesSum;
};

/*
    Even vec elements *= 2
    Odd vec elements  -= sum of positive elements
    Sort elements
*/
void ProcessVector(vector<double> & vec)
{
    auto vecStart = vec.begin();
    auto vecEnd = vec.end();

    CTransformer transformer(SumPositive(vec));

    transform(vecStart, vecEnd, vecStart, transformer);

    sort(vecStart, vecEnd);
}

void PrintVector(ostream & output, vector<double> const& vec, string const& delemiter)
{
    ostream_iterator<double> outputIt(output, delemiter.c_str());
    copy(vec.cbegin(), vec.cend(), outputIt);
}
