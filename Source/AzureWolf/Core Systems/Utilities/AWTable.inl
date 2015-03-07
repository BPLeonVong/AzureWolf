template <int NROWS, int NCOLS, typename TYPE>
Table<NROWS,NCOLS,TYPE>::Table ()
{
}

template <int NROWS, int NCOLS, typename TYPE>
Table<NROWS,NCOLS,TYPE>::Table (const Table& table)
{
    for (int i = 0; i < NUMENTRIES; ++i)
    {
        mEntry[i] = table.mEntry[i];
    }
}

template <int NROWS, int NCOLS, typename TYPE>
Table<NROWS,NCOLS,TYPE>::~Table ()
{
}

template <int NROWS, int NCOLS, typename TYPE>
inline Table<NROWS,NCOLS,TYPE>::operator const TYPE* () const
{
    return mEntry;
}

template <int NROWS, int NCOLS, typename TYPE>
inline Table<NROWS,NCOLS,TYPE>::operator TYPE* ()
{
    return mEntry;
}

template <int NROWS, int NCOLS, typename TYPE>
inline const TYPE* Table<NROWS,NCOLS,TYPE>::operator[] (int row) const
{
    return &mEntry[NCOLS*row];
}

template <int NROWS, int NCOLS, typename TYPE>
inline TYPE* Table<NROWS,NCOLS,TYPE>::operator[] (int row)
{
    return &mEntry[NCOLS*row];
}

template <int NROWS, int NCOLS, typename TYPE>
inline const TYPE& Table<NROWS,NCOLS,TYPE>::operator() (int row, int col)
    const
{
    return mEntry[col + NCOLS*row];
}

template <int NROWS, int NCOLS, typename TYPE>
inline TYPE& Table<NROWS,NCOLS,TYPE>::operator() (int row, int col)
{
    return mEntry[col + NCOLS*row];
}

template <int NROWS, int NCOLS, typename TYPE>
void Table<NROWS,NCOLS,TYPE>::SetRow (int row,
    const Tuple<NCOLS,TYPE>& tuple)
{
    for (int c = 0, i = NCOLS*row; c < NCOLS; ++c, ++i)
    {
        mEntry[i] = tuple[c];
    }
}

template <int NROWS, int NCOLS, typename TYPE>
Tuple<NCOLS,TYPE> Table<NROWS,NCOLS,TYPE>::GetRow (int row) const
{
    Tuple<NROWS,TYPE> result;
    for (int c = 0, i = NCOLS*row; c < NCOLS; ++c, ++i)
    {
        result[c] = mEntry[i];
    }
    return result;
}

template <int NROWS, int NCOLS, typename TYPE>
void Table<NROWS,NCOLS,TYPE>::SetColumn (int col,
   const Tuple<NROWS,TYPE>& tuple)
{
    for (int r = 0, i = col; r < NROWS; ++r, i += NCOLS)
    {
        mEntry[i] = tuple[r];
    }
}

template <int NROWS, int NCOLS, typename TYPE>
Tuple<NROWS,TYPE> Table<NROWS,NCOLS,TYPE>::GetColumn (int col) const
{
    Tuple<NCOLS,TYPE> result;
    for (int r = 0, i = col; r < NROWS; ++r, i += NCOLS)
    {
        result[r] = mEntry[i];
    }
    return result;
}

template <int NROWS, int NCOLS, typename TYPE>
Table<NROWS,NCOLS,TYPE>& Table<NROWS,NCOLS,TYPE>::operator= (
    const Table& table)
{
    for (int i = 0; i < NUMENTRIES; i++)
    {
        mEntry[i] = table.mEntry[i];
    }
    return *this;
}

template <int NROWS, int NCOLS, typename TYPE>
bool Table<NROWS,NCOLS,TYPE>::operator== (const Table& table) const
{
    for (int i = 0; i < NUMENTRIES; ++i)
    {
        if (mEntry[i] != table.mEntry[i])
        {
            return false;
        }
    }
    return true;
}

template <int NROWS, int NCOLS, typename TYPE>
bool Table<NROWS,NCOLS,TYPE>::operator!= (const Table& table) const
{
    for (int i = 0; i < NUMENTRIES; ++i)
    {
        if (mEntry[i] != table.mEntry[i])
        {
            return true;
        }
    }
    return false;
}

template <int NROWS, int NCOLS, typename TYPE>
bool Table<NROWS,NCOLS,TYPE>::operator<  (const Table& table) const
{
    for (int i = 0; i < NUMENTRIES; ++i)
    {
        if (mEntry[i] < table.mEntry[i])
        {
            return true;
        }

        if (mEntry[i] > table.mEntry[i])
        {
            return false;
        }
    }
    return false;
}

template <int NROWS, int NCOLS, typename TYPE>
bool Table<NROWS,NCOLS,TYPE>::operator<= (const Table& table) const
{
    for (int i = 0; i < NUMENTRIES; ++i)
    {
        if (mEntry[i] < table.mEntry[i])
        {
            return true;
        }

        if (mEntry[i] > table.mEntry[i])
        {
            return false;
        }
    }
    return true;
}

template <int NROWS, int NCOLS, typename TYPE>
bool Table<NROWS,NCOLS,TYPE>::operator>  (const Table& table) const
{
    for (int i = 0; i < NUMENTRIES; ++i)
    {
        if (mEntry[i] > table.mEntry[i])
        {
            return true;
        }

        if (mEntry[i] < table.mEntry[i])
        {
            return false;
        }
    }
    return false;
}

template <int NROWS, int NCOLS, typename TYPE>
bool Table<NROWS,NCOLS,TYPE>::operator>= (const Table& table) const
{
    for (int i = 0; i < NUMENTRIES; ++i)
    {
        if (mEntry[i] > table.mEntry[i])
        {
            return true;
        }

        if (mEntry[i] < table.mEntry[i])
        {
            return false;
        }
    }
    return true;
}
