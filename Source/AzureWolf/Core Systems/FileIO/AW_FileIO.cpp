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

bool fRead(const char* pFileName, string& outFile)
{
    ifstream f(pFileName);
    
    bool ret = false;
    /*
	ofstream out("filename.txt");
	out<<"Line 1:Hello World\n"
		<<"Line 2:Hello World\n"
		<<"Line 3:Hello World\n"<<endl;
		out.close();*/

    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        
        f.close();
        
        ret = true;
    }
    else {
		assertion(true,"Error");
    }
    
    return ret;
}

/*
bool FileIO::Open(const std::string& filename, int mode)
{
	if (mMode == NONE)
    {
        if (mode == READ || mode == READ_AND_SWAP)
        {
            mFile = fopen(filename.c_str(), "rbS");
        }
        else
        {
            mFile = fopen(filename.c_str(), "wbS");
        }

        if (mFile)
        {
            mMode = mode;
            return true;
        }
		
		fprintf(stderr, "Error Failed to open file %s\n",filename.c_str());
        assertion(false, "Failed to open file %s\n", filename.c_str());
    }
    else
    {
		fprintf(stderr, "File %s is already open\n",filename.c_str());
        assertion(false, "File %s is already open\n", filename.c_str());
    }
    return false;
}

bool FileIO::Close ()
{
    mMode = NONE;
    if (fclose(mFile) == 0)
    {
        return true;
    }
	
	fprintf(stderr, "Failed to close file\n");
    assertion(false, "Failed to close file\n");
    return false;
}

FileIO::operator bool () const
{
    return mMode != NONE;
}*/

/*
bool FileIO::LoadFileRaw(std::string& fileName, char** data, unsigned int* size)
{
	if (fileName != "") 
    {
        FILE *file = fopen(fileName.c_str(), "rt");

        if (file != NULL) 
        {
            fseek(file, 0, SEEK_END);
            *size = ftell(file);
            rewind(file);

            if (*size > 0) 
            {
                *data = (char*)malloc(sizeof(char) * (*size + 1));
                *size = fread(data, sizeof(char), *size, file);
                data[*size] = '\0';
            }

            fclose(file);
        }
    }

    return data;
}*/