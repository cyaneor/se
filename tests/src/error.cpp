#include <gtest/gtest.h>
#include <se/error.h>

constexpr const auto SE_ERROR_CODE_SOME_ERROR = 666;

TEST(se_error, get_code) {
  se_error_t err = {15};
  EXPECT_EQ(se_error_get_code(&err), 15);
}

TEST(se_error, get_code_null) {
  EXPECT_DEATH(se_error_get_code(nullptr), ".*");
}

TEST(se_error, get_desc) {
  se_error_t err = {.desc = "Test error"};
  EXPECT_STREQ(se_error_get_desc(&err), "Test error");
}

TEST(se_error, get_desc_null) {
  EXPECT_DEATH(se_error_get_desc(nullptr), ".*");
}

TEST(se_error, set) {
  se_error_t err = {};
  se_error_set(&err, SE_ERROR_CODE_SOME_ERROR, "Test error");

  EXPECT_EQ(err.code, SE_ERROR_CODE_SOME_ERROR);
  EXPECT_STREQ(err.desc, "Test error");
}

TEST(se_error, set_null) {
  EXPECT_DEATH(se_error_set(nullptr, SE_ERROR_CODE_SOME_ERROR, "Test error"),
               ".*");
}

TEST(se_error, set_code) {
  se_error_t err = {};
  se_error_set_code(&err, SE_ERROR_CODE_SOME_ERROR);
  EXPECT_EQ(err.code, SE_ERROR_CODE_SOME_ERROR);
  EXPECT_EQ(err.desc, nullptr);
}

TEST(se_error, unpack) {
  se_error_t err = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Test error"};
  se_error_code_t code;
  const char *desc;
  se_error_unpack(&err, &code, &desc);
  EXPECT_EQ(code, SE_ERROR_CODE_SOME_ERROR);
  EXPECT_STREQ(desc, "Test error");
}

TEST(se_error, unpack_partial) {
  se_error_t err = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Test error"};

  se_error_code_t code;
  se_error_unpack(&err, &code, nullptr);
  EXPECT_EQ(code, SE_ERROR_CODE_SOME_ERROR);

  const char *desc;
  se_error_unpack(&err, nullptr, &desc);
  EXPECT_STREQ(desc, "Test error");
}

TEST(se_error, assign) {
  se_error_t err = {};
  se_error_t other = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Test error"};
  se_error_assign(&err, &other);
  EXPECT_EQ(err.code, SE_ERROR_CODE_SOME_ERROR);
  EXPECT_STREQ(err.desc, "Test error");
}

TEST(se_error, clear) {
  se_error_t err = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Test error"};
  se_error_clear(&err);
  EXPECT_EQ(err.code, SE_ERROR_CODE_NONE);
  EXPECT_EQ(err.desc, nullptr);
}

TEST(se_error, get_code_and_clear) {
  se_error_t err = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Test error"};
  se_error_code_t code = se_error_get_code_and_clear(&err);
  EXPECT_EQ(code, SE_ERROR_CODE_SOME_ERROR);
  EXPECT_EQ(err.code, SE_ERROR_CODE_NONE);
  EXPECT_EQ(err.desc, nullptr);
}

TEST(se_error, is_code) {
  se_error_t err = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Test error"};
  EXPECT_TRUE(se_error_is_code(&err, SE_ERROR_CODE_SOME_ERROR));
  EXPECT_FALSE(se_error_is_code(&err, SE_ERROR_CODE_NONE));
}

TEST(se_error, is_code_equal) {
  se_error_t err1 = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Test error"};
  se_error_t err2 = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Other error"};
  EXPECT_TRUE(se_error_is_code_equal(&err1, &err2));
  se_error_t err3 = {.code = SE_ERROR_CODE_NONE, .desc = "Test error"};
  EXPECT_FALSE(se_error_is_code_equal(&err1, &err3));
}

TEST(se_error, is_ok) {
  se_error_t err = {.code = SE_ERROR_CODE_NONE, .desc = nullptr};
  EXPECT_TRUE(se_error_is_ok(&err));
  se_error_t err2 = {.code = SE_ERROR_CODE_SOME_ERROR, .desc = "Test error"};
  EXPECT_FALSE(se_error_is_ok(&err2));
}