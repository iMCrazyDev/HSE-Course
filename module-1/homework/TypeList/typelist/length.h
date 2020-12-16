#pragma once

#include "typelist.h"

template<typename TypeList>
struct Length;

template<typename Head, typename Tail> 
struct Length<TypeList<Head,Tail>> {
	static constexpr int length = Length<Tail>::length + 1;
};

template<>
struct Length<NullType> {
	static constexpr int length = 0;
};
