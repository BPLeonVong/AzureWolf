#pragma once

#include "../types.h"

namespace AW
{
	class Float4 : public Tuple<4,float>
	{
	public:
		inline Float4 ();
		inline ~Float4 ();
		inline Float4 (float f0, float f1, float f2, float f3);
		inline Float4 (const Float4& tuple);

		inline Float4& operator= (const Float4& tuple);
	};
	
#include "../DataTypes/AWFloat4.inl"
}
