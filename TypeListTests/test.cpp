#include "pch.h"
#include "../TypeLists/TypeList.h"

#include <type_traits>

class TypeListTest : public ::testing::Test
{
protected:
	using lst = tl::TypeList<char, int, float, double>;
};

TEST_F(TypeListTest, SizeTest)
{
	EXPECT_EQ(lst::size(), 4);
}

TEST_F(TypeListTest, TestPrint)
{
	testing::internal::CaptureStdout();
	lst::print();
	std::string out = testing::internal::GetCapturedStdout();
	EXPECT_EQ(out, "char, int, float, double\b\b\n");
}

TEST_F(TypeListTest, TestTypeAt)
{
	EXPECT_TRUE((std::is_same_v<char, tl::algo::TypeAt<lst, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<lst, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<float, tl::algo::TypeAt<lst, 2>::Type>));
	EXPECT_TRUE((std::is_same_v<double, tl::algo::TypeAt<lst, 3>::Type>));
}

TEST_F(TypeListTest, TestPushFront)
{
	using newList = tl::algo::PushFront<lst, int[10]>::Result;
	EXPECT_TRUE((std::is_same_v<int[10], tl::algo::TypeAt<newList, 0>::Type>));
	EXPECT_EQ(newList::size(), lst::size() + 1);
}

TEST_F(TypeListTest, TestPushBack)
{
	using newList = tl::algo::PushBack<lst, int[10]>::Result;
	EXPECT_TRUE((std::is_same_v<int[10], tl::algo::TypeAt<newList, newList::size() - 1>::Type>));
	EXPECT_EQ(newList::size(), lst::size() + 1);
}

TEST_F(TypeListTest, TestPrintReversed)
{
	using reversed = tl::algo::Reverse<lst>::Result;
	testing::internal::CaptureStdout();
	reversed::print();
	std::string out = testing::internal::GetCapturedStdout();
	EXPECT_EQ(out, "double, float, int, char\b\b\n");
}

TEST_F(TypeListTest, TestRevrsed)
{
	using reversed = tl::algo::Reverse<lst>::Result;
	EXPECT_TRUE((std::is_same_v<double, tl::algo::TypeAt<reversed, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<float, tl::algo::TypeAt<reversed, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<reversed, 2>::Type>));
	EXPECT_TRUE((std::is_same_v<char, tl::algo::TypeAt<reversed, 3>::Type>));
	EXPECT_EQ(reversed::size(), lst::size());
}

TEST_F(TypeListTest, TestPopBack)
{
	using result = tl::algo::PopBack<lst>::Result;
	EXPECT_TRUE((std::is_same_v<char, tl::algo::TypeAt<lst, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<lst, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<float, tl::algo::TypeAt<lst, 2>::Type>));
	EXPECT_EQ(result::size(), lst::size() - 1);
}

TEST_F(TypeListTest, TestRemoveTypeFirst)
{
	using result = tl::algo::RemoveType<lst, char>::Result;

	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<result, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<float, tl::algo::TypeAt<result, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<double, tl::algo::TypeAt<result, 2>::Type>));
	EXPECT_EQ(result::size(), lst::size() - 1);
}

TEST_F(TypeListTest, TestRemoveTypeMid)
{
	using result = tl::algo::RemoveType<lst, float>::Result;

	EXPECT_TRUE((std::is_same_v<char, tl::algo::TypeAt<result, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<result, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<double, tl::algo::TypeAt<result, 2>::Type>));
	EXPECT_EQ(result::size(), lst::size() - 1);
}

TEST_F(TypeListTest, TestRemoveTypeLast)
{
	using result = tl::algo::RemoveType<lst, double>::Result;

	EXPECT_TRUE((std::is_same_v<char, tl::algo::TypeAt<result, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<result, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<float, tl::algo::TypeAt<result, 2>::Type>));
	EXPECT_EQ(result::size(), lst::size() - 1);
}

TEST_F(TypeListTest, TestRemoveTypeAll)
{
	using newList = tl::algo::PushFront<lst, double>::Result;
	using result = tl::algo::RemoveAll<newList, double>::Result;

	EXPECT_TRUE((std::is_same_v<char, tl::algo::TypeAt<result, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<result, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<float, tl::algo::TypeAt<result, 2>::Type>));
	EXPECT_EQ(result::size(),  newList::size() - 2);
}

TEST_F(TypeListTest, TestRemoveTypeAllAdjacent)
{
	using newList = tl::algo::PushFront<lst, char>::Result;
	using result = tl::algo::RemoveAll<newList, char>::Result;

	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<result, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<float, tl::algo::TypeAt<result, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<double, tl::algo::TypeAt<result, 2>::Type>));
	EXPECT_EQ(result::size(), newList::size() - 2);
}

TEST_F(TypeListTest, TestRemoveDups)
{
	using newList = tl::algo::PushFront<tl::algo::PushBack<lst, int>::Result, double>::Result;
	using result = tl::algo::RemoveDuplicates<newList>::Result;

	EXPECT_TRUE((std::is_same_v<double, tl::algo::TypeAt<result, 0>::Type>));
	EXPECT_TRUE((std::is_same_v<char, tl::algo::TypeAt<result, 1>::Type>));
	EXPECT_TRUE((std::is_same_v<int, tl::algo::TypeAt<result, 2>::Type>));
	EXPECT_TRUE((std::is_same_v<float, tl::algo::TypeAt<result, 3>::Type>));
	EXPECT_EQ(result::size(), lst::size());
}