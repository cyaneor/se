#include <gtest/gtest.h>
#include <se/numeric_limits.h>

TEST(numeric_limits, char_type_size) {
  EXPECT_EQ(sizeof(char), SE_CHAR_T_SIZE);
}

TEST(numeric_limits, short_type_size) {
  EXPECT_EQ(sizeof(short), SE_SHORT_T_SIZE);
}

TEST(numeric_limits, int_type_size) { EXPECT_EQ(sizeof(int), SE_INT_T_SIZE); }

TEST(numeric_limits, long_type_size) {
  EXPECT_EQ(sizeof(long), SE_LONG_T_SIZE);
}

TEST(numeric_limits, llong_type_size) {
  EXPECT_EQ(sizeof(long long), SE_LLONG_T_SIZE);
}

TEST(numeric_limits, uchar_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned char>::min(), SE_UCHAR_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned char>::max(), SE_UCHAR_T_MAX);
}

TEST(numeric_limits, ushort_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned short>::min(), SE_USHORT_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned short>::max(), SE_USHORT_T_MAX);
}

TEST(numeric_limits, uint_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned int>::min(), SE_UINT_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned int>::max(), SE_UINT_T_MAX);
}

TEST(numeric_limits, ulong_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned long>::min(), SE_ULONG_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned long>::max(), SE_ULONG_T_MAX);
}

TEST(numeric_limits, ullong_type_limits) {
  EXPECT_EQ(std::numeric_limits<unsigned long long>::min(), SE_ULLONG_T_MIN);
  EXPECT_EQ(std::numeric_limits<unsigned long long>::max(), SE_ULLONG_T_MAX);
}

TEST(numeric_limits, schar_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed char>::min(), SE_SCHAR_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed char>::max(), SE_SCHAR_T_MAX);
}

TEST(numeric_limits, sshort_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed short>::min(), SE_SSHORT_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed short>::max(), SE_SSHORT_T_MAX);
}

TEST(numeric_limits, sint_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed int>::min(), SE_SINT_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed int>::max(), SE_SINT_T_MAX);
}

TEST(numeric_limits, slong_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed long>::min(), SE_SLONG_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed long>::max(), SE_SLONG_T_MAX);
}

TEST(numeric_limits, sllong_type_limits) {
  EXPECT_EQ(std::numeric_limits<signed long long>::min(), SE_SLLONG_T_MIN);
  EXPECT_EQ(std::numeric_limits<signed long long>::max(), SE_SLLONG_T_MAX);
}