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

	template <int NROWS, int NCOLS, typename TYPE>
	class Table
	{
	public:
		Table();
		Table(const Table& table);
		~Table();

		    // Coordinate access.
		inline operator const TYPE* () const;
		inline operator TYPE* ();
		inline const TYPE* operator[] (int row) const;
		inline TYPE* operator[] (int row);
		inline const TYPE& operator() (int row, int col) const;
		inline TYPE& operator() (int row, int col);
		void SetRow (int row, const Tuple<NCOLS,TYPE>& tuple);
		Tuple<NCOLS,TYPE> GetRow (int row) const;
		void SetColumn (int col, const Tuple<NROWS,TYPE>& tuple);
		Tuple<NROWS,TYPE> GetColumn (int col) const;

	    // Assignment.
	    Table& operator= (const Table& table);

	    // Comparison.
	    bool operator== (const Table& table) const;
	    bool operator!= (const Table& table) const;
	    bool operator<  (const Table& table) const;
	    bool operator<= (const Table& table) const;
	    bool operator>  (const Table& table) const;
		bool operator>= (const Table& table) const;

	protected:
		// The array is stored in row-major order.
		enum { NUMENTRIES = NROWS*NCOLS };
		TYPE mEntry[NUMENTRIES];
	};
	
#include "../Utilities/AWTuple.inl"
}
