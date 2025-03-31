#include <gtest/gtest.h>
#include <se/memory/memory_view.h>
#include <se/static/static_array_size.h>

TEST(se_memory_view_get_begin, valid_pointer) {
  int value = 42;
  se_memory_view_t range = {&value, nullptr};
  EXPECT_EQ(se_memory_view_get_begin(&range), &value);
}

TEST(se_memory_view_get_begin, null_pointer) {
  EXPECT_EQ(se_memory_view_get_begin(nullptr), nullptr);
  // EXPECT_EQ(se_runtime_error_code, SE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(se_memory_view_get_end, valid_pointer) {
  int value = 42;
  se_memory_view_t range = {nullptr, &value};
  EXPECT_EQ(se_memory_view_get_end(&range), &value);
}

TEST(se_memory_view_get_end, null_pointer) {
  EXPECT_EQ(se_memory_view_get_end(nullptr), nullptr);
  // EXPECT_EQ(se_runtime_error_code, SE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(se_memory_view_is_empty, empty_range) {
  int value = 42;
  se_memory_view_t range = {&value, &value};
  EXPECT_TRUE(se_memory_view_is_empty(&range));
}

TEST(se_memory_view_is_empty, non_empty_range) {
  int value1 = 42;
  int value2 = 84;
  se_memory_view_t range = {&value1, &value2};
  EXPECT_FALSE(se_memory_view_is_empty(&range));
}

TEST(se_memory_view_is_empty, null_pointer) {
  EXPECT_TRUE(se_memory_view_is_empty(nullptr));
  // Если есть проверка ошибок, можно добавить: EXPECT_EQ(se_error_get_code(),
  // SE_RUNTIME_ERROR_NULL_POINTER);
}

TEST(se_memory_view_is_empty, null_end) {
  int value = 42;
  se_memory_view_t range = {&value, nullptr};
  EXPECT_FALSE(se_memory_view_is_empty(&range));
}

TEST(se_memory_view_unpack, basic_unpacking) {
  int test_data_begin = 42;
  int test_data_end = 84;

  se_memory_view_t range = {&test_data_begin, &test_data_end};

  const void *result_begin = nullptr;
  const void *result_end = nullptr;

  se_memory_view_unpack(&range, &result_begin, &result_end);

  EXPECT_EQ(result_begin, &test_data_begin)
      << "Begin pointer should match input begin";
  EXPECT_EQ(result_end, &test_data_end) << "End pointer should match input end";
}

TEST(se_memory_view_unpack, null_begin_pointer) {
  int test_data_end = 84;
  se_memory_view_t range = {nullptr, &test_data_end};

  const void *result_end = nullptr;
  se_memory_view_unpack(&range, nullptr, &result_end);

  EXPECT_EQ(result_end, &test_data_end)
      << "End pointer should be set when begin is nullptr";
}

TEST(se_memory_view_unpack, null_end_pointer) {
  int test_data_begin = 42;
  se_memory_view_t range = {&test_data_begin, nullptr};

  const void *result_begin = nullptr;
  se_memory_view_unpack(&range, &result_begin, nullptr);

  EXPECT_EQ(result_begin, &test_data_begin)
      << "Begin pointer should be set when end is nullptr";
}

TEST(se_memory_view_unpack, both_null_pointers) {
  int test_data_begin = 42;
  int test_data_end = 84;

  se_memory_view_t range = {&test_data_begin, &test_data_end};
  se_memory_view_unpack(&range, nullptr, nullptr);
}

TEST(se_memory_view_is_valid, valid_range) {
  int data[] = {42, 84};
  se_memory_view_t range = {data, &data[1]};

  bool result = se_memory_view_is_valid(&range);
  EXPECT_TRUE(result) << "Valid range should return true";
}

TEST(se_memory_view_is_valid, invalid_range_begin_after_end) {
  int data[] = {42, 84};
  se_memory_view_t range = {&data[1], data};

  bool result = se_memory_view_is_valid(&range);
  EXPECT_FALSE(result) << "Range with begin > end should return false";
}

TEST(se_memory_view_is_valid, null_begin) {
  int data = 84;
  se_memory_view_t range = {nullptr, &data};

  bool result = se_memory_view_is_valid(&range);
  EXPECT_FALSE(result) << "Range with null begin should return false";
}

TEST(se_memory_view_is_valid, null_end) {
  int data = 42;
  se_memory_view_t range = {&data, nullptr};

  bool result = se_memory_view_is_valid(&range);
  EXPECT_FALSE(result) << "Range with null end should return false";
}

TEST(se_memory_view_is_valid, both_null) {
  se_memory_view_t range = {};

  bool result = se_memory_view_is_valid(&range);
  EXPECT_FALSE(result) << "Range with both null pointers should return false";
}

TEST(se_memory_view_is_valid, same_address) {
  int data[] = {42};
  se_memory_view_t range = {data, data};

  bool result = se_memory_view_is_valid(&range);
  EXPECT_TRUE(result)
      << "Range with same begin and end address should return true";
}

TEST(se_memory_view_contains_pointer, pointer_within_range) {
  int data[] = {42, 84};
  se_memory_view_t range = {data, &data[1]};
  void *ptr = &data[1];

  bool result = se_memory_view_contains_pointer(&range, ptr);
  EXPECT_TRUE(result) << "Pointer within range should return true";
}

TEST(se_memory_view_contains_pointer, pointer_before_range) {
  int data[] = {42, 84};
  se_memory_view_t range = {data, &data[1]};
  void *ptr = &data[0] - 1;

  bool result = se_memory_view_contains_pointer(&range, ptr);
  EXPECT_FALSE(result) << "Pointer before range should return false";
}

TEST(se_memory_view_contains_pointer, pointer_after_range) {
  int data[] = {42, 84};
  se_memory_view_t range = {data, &data[1]};
  void *ptr = &data[2];

  bool result = se_memory_view_contains_pointer(&range, ptr);
  EXPECT_FALSE(result) << "Pointer after range should return false";
}

TEST(se_memory_view_contains_pointer, pointer_at_beginning_of_range) {
  int data[] = {42, 84};
  se_memory_view_t range = {data, &data[1]};
  void *ptr = &data[0];

  bool result = se_memory_view_contains_pointer(&range, ptr);
  EXPECT_TRUE(result) << "Pointer at beginning of range should return true";
}

TEST(se_memory_view_contains_pointer, null_pointer) {
  int data[] = {42, 84};
  se_memory_view_t range = {data, &data[1]};
  void *ptr = nullptr;

  bool result = se_memory_view_contains_pointer(&range, ptr);
  EXPECT_FALSE(result) << "Null pointer should return false";
}

TEST(se_memory_view_contains_pointer, empty_range) {
  se_memory_view_t range = {nullptr, nullptr};
  int value = 42;
  void *ptr = &value;

  bool result = se_memory_view_contains_pointer(&range, ptr);
  EXPECT_FALSE(result) << "Empty range should return false for any pointer";
}

TEST(se_memory_view_contains_pointer, empty_range_returns_false_for_nullptr) {
  se_memory_view_t range = {nullptr, nullptr};

  bool result = se_memory_view_contains_pointer(&range, nullptr);
  EXPECT_FALSE(result) << "Empty range should not contain nullptr";
}

TEST(se_memory_view_contains_range, fully_within) {
  int data[] = {1, 2, 3, 4, 5};
  se_memory_view_t range = {data, data + 5};

  bool result = se_memory_view_contains_range(&range, data + 1, data + 4);
  EXPECT_TRUE(result);
}

TEST(se_memory_view_contains_range, exactly_equal) {
  int data[] = {1, 2, 3, 4, 5};
  se_memory_view_t range = {data, data + 5};

  bool result = se_memory_view_contains_range(&range, data, data + 5);
  EXPECT_TRUE(result);
}

TEST(se_memory_view_contains_range, overlapping_low) {
  int data[] = {1, 2, 3, 4, 5};
  se_memory_view_t range = {data, data + 5};

  bool result = se_memory_view_contains_range(&range, data - 1, data + 2);
  EXPECT_FALSE(result);
}

TEST(se_memory_view_contains_range, overlapping_high) {
  int data[] = {1, 2, 3, 4, 5};
  se_memory_view_t range = {data, data + 5};

  bool result = se_memory_view_contains_range(&range, data + 3, data + 6);
  EXPECT_FALSE(result);
}

TEST(se_memory_view_contains_range, outside_range_low) {
  int data[] = {1, 2, 3, 4, 5};
  se_memory_view_t range = {data + 1, data + 4};

  bool result = se_memory_view_contains_range(&range, data, data + 2);
  EXPECT_FALSE(result);
}

TEST(se_memory_view_contains_range, outside_range_high) {
  int data[] = {1, 2, 3, 4, 5};
  se_memory_view_t range = {data + 1, data + 4};

  bool result = se_memory_view_contains_range(&range, data + 3, data + 5);
  EXPECT_FALSE(result);
}

TEST(se_memory_view_contains_range, null_range) {
  se_memory_view_t range = {nullptr, nullptr};

  bool result = se_memory_view_contains_range(&range, nullptr, nullptr);
  EXPECT_FALSE(result);
}

TEST(se_memory_view_contains_range, null_begin_end) {
  int data[] = {1, 2, 3, 4, 5};
  se_memory_view_t range = {data, data + 5};

  bool result = se_memory_view_contains_range(&range, nullptr, nullptr);
  EXPECT_FALSE(result);
}

TEST(se_memory_view_is_multiple_of, valid_multiple) {
  int data[4];
  se_memory_view_t range = {data, &data[4]};
  se_usize_t element_size = sizeof(int);

  bool result = se_memory_view_is_multiple_of(&range, element_size);
  EXPECT_TRUE(result) << "Size should be a multiple of element size";
}

TEST(se_memory_view_is_multiple_of, valid_not_multiple) {
  char data[5];
  se_memory_view_t range = {data, &data[5]};
  se_usize_t element_size = 3;

  bool result = se_memory_view_is_multiple_of(&range, element_size);
  EXPECT_FALSE(result) << "Size should not be a multiple of element size";
}

TEST(se_memory_view_is_multiple_of, zero_element_size) {
  int data[4];
  se_memory_view_t range = {data, &data[4]};
  se_usize_t element_size = 0;

  // Ожидаем, что функция вызовет ассерцию или вернет false
  // EXPECT_DEATH(se_memory_view_multiple_of(&range, element_size), ".*");
}

TEST(se_memory_view_is_multiple_of, empty_range) {
  se_memory_view_t range = {nullptr, nullptr};
  se_usize_t element_size = sizeof(int);

  bool result = se_memory_view_is_multiple_of(&range, element_size);
  EXPECT_TRUE(result)
      << "Empty range should be considered a multiple of any element size";
}

TEST(se_memory_view_is_multiple_of, single_element_range) {
  int data[1];
  se_memory_view_t range = {data, &data[1]};
  se_usize_t element_size = sizeof(int);

  bool result = se_memory_view_is_multiple_of(&range, element_size);
  EXPECT_TRUE(result)
      << "Single element range should be a multiple of element size";
}

TEST(se_memory_view_is_aligned, valid_aligned) {
  int data[4];
  se_memory_view_t range = {data, &data[4]};
  se_usize_t alignment_size = 4;

  bool result = se_memory_view_is_aligned(&range, alignment_size);
  EXPECT_TRUE(result) << "Range should be aligned with alignment_size="
                      << alignment_size;
}

TEST(se_memory_view_is_aligned, zero_alignment) {
  int data[2];
  se_memory_view_t range = {data, &data[2]};
  se_usize_t alignment_size = 0;

  // Ожидаем, что assert в функции сработает, но для теста проверяем поведение
  //  EXPECT_DEATH(se_memory_view_aligned(&range, alignment_size),
  //               "SE_RUNTIME_ERROR_INVALID_ARGUMENT")
  //      << "Function should assert on zero alignment";
}

TEST(se_memory_view_is_aligned, single_element_aligned) {
  double data;
  se_memory_view_t range = {&data, &data + 1};
  se_usize_t alignment_size = 8;

  bool result = se_memory_view_is_aligned(&range, alignment_size);
  EXPECT_TRUE(result) << "Single element should be aligned with alignment_size="
                      << alignment_size;
}

TEST(se_memory_view_is_aligned, empty_range_aligned) {
  int data;
  se_memory_view_t range = {&data, &data};
  se_usize_t alignment_size = 4;

  bool result = se_memory_view_is_aligned(&range, alignment_size);
  EXPECT_TRUE(result) << "Empty range should be considered aligned";
}

TEST(se_memory_view_get_size, valid_range) {
  int data[2] = {};
  se_memory_view_t range = {data, &data[2]};
  se_usize_t expected_size = se_static_array_size(data) * sizeof(int);

  se_usize_t size = se_memory_view_get_size(&range);
  EXPECT_EQ(size, expected_size)
      << "Size should match the difference between begin and end";
}

TEST(se_memory_view_get_size, empty_range) {
  int data;
  se_memory_view_t range = {&data, &data};

  se_usize_t size = se_memory_view_get_size(&range);
  EXPECT_EQ(size, 0) << "Size of an empty range should be zero";
}

TEST(se_memory_view_get_size, single_element_range) {
  int data;
  se_memory_view_t range = {&data, &data + 1};

  se_usize_t size = se_memory_view_get_size(&range);
  EXPECT_EQ(size, sizeof(data))
      << "Size should be equal to the size of a single element";
}

TEST(se_memory_view_get_size, invalid_range) {
  se_memory_view_t range = {nullptr, nullptr};
  // EXPECT_DEATH(se_memory_view_size(&range), ".*");
}

TEST(se_memory_view_is_valid_offset, valid_offset_within_range) {
  int data[5];
  se_memory_view_t range = {data, &data[5]};
  se_uoffset_t offset = 2 * sizeof(int);

  bool result = se_memory_view_is_valid_offset(&range, offset);
  EXPECT_TRUE(result) << "Offset should be valid within the range";
}

TEST(se_memory_view_is_valid_offset, offset_equal_to_range_size) {
  int data[5];
  se_memory_view_t range = {data, &data[5]};
  se_uoffset_t offset = 5 * sizeof(int);

  bool result = se_memory_view_is_valid_offset(&range, offset);
  EXPECT_FALSE(result) << "Offset equal to range size should be invalid";
}

TEST(se_memory_view_is_valid_offset, offset_greater_than_range_size) {
  int data[5];
  se_memory_view_t range = {data, &data[5]};
  se_uoffset_t offset = 6 * sizeof(int);

  bool result = se_memory_view_is_valid_offset(&range, offset);
  EXPECT_FALSE(result) << "Offset greater than range size should be invalid";
}

TEST(se_memory_view_is_valid_offset, negative_offset) {
  int data[5];
  se_memory_view_t range = {data, &data[5]};
  se_uoffset_t offset = -1;

  bool result = se_memory_view_is_valid_offset(&range, offset);
  EXPECT_FALSE(result) << "Negative offset should be invalid";
}