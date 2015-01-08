#pragma once

#if defined(NDEBUG)
#	define new0 new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define new0 new
#endif


template <typename T>
T* new1 (const size_t bound0);

template <typename T>
T** new2 (const size_t bound0, const size_t bound1);

template <typename T>
T*** new3 (const size_t bound0, const size_t bound1, const size_t bound2);

template <typename T>
T**** new4 (const size_t bound0, const size_t bound1, const size_t bound2,
    const size_t bound3);

template <typename T>
void delete0 (T*& data);

template <typename T>
void delete1 (T*& data);

template <typename T>
void delete2 (T**& data);

template <typename T>
void delete3 (T***& data);

template <typename T>
void delete4 (T****& data);

#include "../Memory/AW_Memory.inl"