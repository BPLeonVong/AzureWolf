#pragma once

#include "math.h"

namespace AW
{
	template <int DIMENSION, typename TYPE>
	class Tuple
	{
	public:
		Tuple();
		Tuple(const Tuple& tuple);
		~Tuple();

		inline operator const TYPE* () const;
		inline operator TYPE* ();
		inline const TYPE& operator[] (int i) const;
		inline TYPE& operator[] (int i);

    	Tuple& operator= (const Tuple& tuple);

    // Comparison.
		bool operator== (const Tuple& tuple) const;
		bool operator!= (const Tuple& tuple) const;
		bool operator<  (const Tuple& tuple) const;
		bool operator<= (const Tuple& tuple) const;
		bool operator>  (const Tuple& tuple) const;
		bool operator>= (const Tuple& tuple) const;

	protected:
		TYPE mTuple[DIMENSION];
	};
	
#include "../Utilities/AWTuple.inl"
}
