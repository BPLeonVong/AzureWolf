#pragma once

namespace AW
{
	class FileIO
	{
	public:
		enum
		{
			NONE,
			READ,
			WRITE,
			READ_AND_SWAP,
			WRITE_AND_SWAP,

#ifdef AW_LITTLE_ENDIAN
			DEFAULT_READ = READ,
			DEFAULT_WRITE = WRITE
#else
			DEFAULT_READ = READ_AND_SWAP,
			DEFAULT_WRITE = WRITE_AND_SWAP
#endif

		};

		FileIO();
		FileIO(const std::string& filename,int mode);
		~FileIO();
	
	private:
		FILE* mFile;
		int mMode;
	};

#include "AW_FileIO.inl"

}