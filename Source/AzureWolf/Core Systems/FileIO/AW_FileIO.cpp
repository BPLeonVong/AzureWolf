#include "AzureWolfStd.h"
#include "AW_FileIO.h"


using namespace AW;

bool fRead(const char* pFileName, string& outFile)
{
    ifstream f(pFileName);
    
    bool ret = false;

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