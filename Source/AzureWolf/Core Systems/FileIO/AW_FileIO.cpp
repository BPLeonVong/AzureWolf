#include "AzureWolfStd.h"
#include "AW_FileIO.h"

using namespace AW;

FileIO::FileIO()
	:
	mFile(0),
	mMode(NONE)
{
}

FileIO::FileIO(const std::string& filename, int mode)
	:
	mFile(0),
	mMode(NONE)
{
}

FileIO::~FileIO()
{
	if(mMode!=NONE)
	{
	}
}
