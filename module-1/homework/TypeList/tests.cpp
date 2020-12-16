#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "typelist/append.h"
#include "typelist/eraseall.h"
#include "typelist/indexof.h"
#include "typelist/length.h"
#include "typelist/noduplicates.h"
#include "typelist/replace.h"
#include "typelist/typeat.h"

#include "gtest/gtest.h"

TEST(Append, Test1) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    typedef TypeList<int, TypeList<double, TypeList<std::string, NullType>>> expected;
    
    testing::StaticAssertTypeEq<Append<actual, std::string>::NewTypeList, expected>();
}

TEST(Append, Test2) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    typedef TypeList<int, TypeList<double, TypeList<std::string, NullType>>> expected;
    
    static_assert((!std::is_same<Append<actual, int>::NewTypeList, expected>::value));
}

TEST(Append, Test3) {
    typedef TypeList<int, NullType> expected;

    testing::StaticAssertTypeEq<Append<NullType, int>::NewTypeList, expected>();
}

TEST(Append, Test4) {
    testing::StaticAssertTypeEq<Append<NullType, NullType>::NewTypeList, NullType>();
}

TEST(Erase, Test1) {
    typedef TypeList<int, TypeList<int, NullType>> actual;
    typedef TypeList<int, NullType> expected;

    testing::StaticAssertTypeEq<Erase<actual, int>::NewTypeList, expected>();
}

TEST(Erase, Test2) {
    testing::StaticAssertTypeEq<Erase<NullType, int>::NewTypeList, NullType>();
}

TEST(EraseAll, Test1) {
    typedef TypeList<int, TypeList<int, NullType>> actual;
    
    testing::StaticAssertTypeEq<EraseAll<actual, int>::NewTypeList, NullType>();
}

TEST(EraseAll, Test2) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    typedef TypeList<double, NullType> expected;

    testing::StaticAssertTypeEq<EraseAll<actual, int>::NewTypeList, expected>();
}

TEST(EraseAll, Test3) {
    testing::StaticAssertTypeEq<EraseAll<NullType, int>::NewTypeList, NullType>();
}

TEST(IndexOf, Test1) {
    typedef TypeList<int, TypeList<double, NullType>> actual;

    static_assert(IndexOf<actual, double>::pos == 1, "expected pos=1");
}
