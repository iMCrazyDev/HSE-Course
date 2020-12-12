#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<typename Head, typename Tail>
struct NoDuplicates<TypeList<Head, Tail>> {
private:
	typedef typename NoDuplicates<Tail>::NewTypeList Deep;
	typedef typename Erase<Deep, Head>::NewTypeList DeepDupl;
public:
	typedef TypeList<Head, DeepDupl> NewTypeList;
};
template<>
struct NoDuplicates<NullType> {
	typedef NullType NewTypeList;
};