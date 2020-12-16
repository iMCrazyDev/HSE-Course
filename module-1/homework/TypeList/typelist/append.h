#pragma once

#include "typelist.h"

template<typename TList, typename NewType>

struct Append;

template<typename Head,typename Tail, typename NewType>
struct Append<TypeList<Head, Tail>, NewType> {
	typedef TypeList<Head, typename Append<Tail, NewType>::NewTypeList> NewTypeList;
};

template<typename Head, typename NewType>
struct Append<TypeList<Head, NullType>, NewType> {
	typedef TypeList<Head, TypeList<NewType, NullType>> NewTypeList;
};
template<typename NewType>
struct Append<NullType, NewType> {
	typedef TypeList <NewType, NullType> NewTypeList;
};
template<>
struct Append<NullType,NullType> {
	typedef NullType NewTypeList;
};

