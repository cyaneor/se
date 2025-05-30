#include <gtest/gtest.h>
#include <se/memory_raw.h>
#include <se/size.h>
#include <se/static_array_size.h>

TEST(se_memory_raw_compare, null_pointers) {
  EXPECT_DEATH(se_memory_raw_compare(nullptr, nullptr, nullptr, nullptr), ".*");
}

TEST(se_memory_raw_compare, compare32) {
  unsigned char lhs[32] = {};
  unsigned char rhs[32] = {};

  const void *result = se_memory_raw_compare(lhs, lhs + 32, rhs, rhs + 32);
  EXPECT_EQ(result, nullptr);

  rhs[15] = 1;

  result = se_memory_raw_compare(lhs, lhs + 32, rhs, rhs + 32);
  EXPECT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 15);
}

TEST(se_memory_raw_compare, compare16) {
  unsigned char lhs[16] = {};
  unsigned char rhs[16] = {};

  const void *result = se_memory_raw_compare(lhs, lhs + 16, rhs, rhs + 16);
  EXPECT_EQ(result, nullptr);

  rhs[7] = 1;

  result = se_memory_raw_compare(lhs, lhs + 16, rhs, rhs + 16);
  EXPECT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 7);
}

TEST(se_memory_raw_compare, compare_same_length) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {1, 2, 3, 4, 5};
  constexpr se_usize_t len = se_static_array_size(lhs);
  EXPECT_EQ(se_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(se_memory_raw_compare, compare_different_length) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {1, 2, 3};
  constexpr se_usize_t lhs_len = se_static_array_size(lhs);
  constexpr se_usize_t rhs_len = se_static_array_size(rhs);

  EXPECT_EQ(se_memory_raw_compare(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]),
            nullptr);
}

TEST(se_memory_raw_compare, compare_different_values) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {1, 2, 0, 4, 5};
  constexpr se_usize_t len = se_static_array_size(lhs);

  EXPECT_EQ(se_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(se_memory_raw_compare, empty_array) {
  constexpr se_u8_t rhs[] = {1, 2, 3};
  constexpr se_usize_t rhs_len = se_static_array_size(rhs);
  EXPECT_DEATH(se_memory_raw_compare(nullptr, nullptr, rhs, &rhs[rhs_len]),
               ".*");
}

TEST(se_memory_raw_compare, compare_equal_after_different_elements) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {6, 7, 8, 4, 5};
  constexpr se_usize_t len = se_static_array_size(lhs);

  EXPECT_EQ(se_memory_raw_compare(lhs, &lhs[len], rhs, &rhs[len]), &lhs[0]);
}

TEST(se_memory_raw_compare_rev, null_pointers) {
  EXPECT_DEATH(se_memory_raw_compare_rev(nullptr, nullptr, nullptr, nullptr),
               ".*");
}

TEST(se_memory_raw_compare_rev, compare_same_length) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {1, 2, 3, 4, 5};
  constexpr se_usize_t len = se_static_array_size(lhs);

  EXPECT_EQ(se_memory_raw_compare_rev(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(se_memory_raw_compare_rev, compare_different_length) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {1, 2, 3};
  constexpr se_usize_t lhs_len = se_static_array_size(lhs);
  constexpr se_usize_t rhs_len = se_static_array_size(rhs);

  EXPECT_EQ(se_memory_raw_compare_rev(lhs, &lhs[lhs_len], rhs, &rhs[rhs_len]),
            &lhs[4]);
}

TEST(se_memory_raw_compare_rev, compare_different_values) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {1, 2, 3, 0, 5};
  constexpr se_usize_t len = se_static_array_size(lhs);

  EXPECT_EQ(se_memory_raw_compare_rev(lhs, &lhs[len], rhs, &rhs[len]), &lhs[3]);
}

TEST(se_memory_raw_compare_rev, empty_array) {
  constexpr se_u8_t rhs[] = {1, 2, 3};
  constexpr se_usize_t rhs_len = se_static_array_size(rhs);

  EXPECT_DEATH(se_memory_raw_compare_rev(nullptr, nullptr, rhs, &rhs[rhs_len]),
               ".*");
}

TEST(se_memory_raw_compare_rev, compare_equal_after_different_elements) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {6, 7, 8, 4, 5};
  constexpr se_usize_t len = se_static_array_size(lhs);

  EXPECT_EQ(se_memory_raw_compare_rev(lhs, &lhs[len], rhs, &rhs[len]), &lhs[2]);
}

TEST(se_memory_raw_compare_rev, compare_same_last_elements) {
  constexpr se_u8_t lhs[] = {0, 0, 0, 0, 5};
  constexpr se_u8_t rhs[] = {0, 0, 0, 0, 5};
  constexpr se_usize_t len = se_static_array_size(lhs);

  EXPECT_EQ(se_memory_raw_compare_rev(lhs, &lhs[len], rhs, &rhs[len]), nullptr);
}

TEST(se_memory_raw_copy, copy_with64_divisible_length) {
  constexpr se_usize_t len = 64;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xAB;

  memset(src, value, len);
  void *result = se_memory_raw_copy(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_copy, copy_with32_divisible_length) {
  constexpr se_usize_t len = 32;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xCD;

  memset(src, value, len);
  void *result = se_memory_raw_copy(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_copy, copy_with16_divisible_length) {
  constexpr se_usize_t len = 16;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xEF;

  memset(src, value, len);
  void *result = se_memory_raw_copy(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_copy, copy_with8_divisible_length) {
  constexpr se_usize_t len = 8;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xFF;

  memset(src, value, len);
  void *result = se_memory_raw_copy(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_copy, copy_with_non_divisible_length) {
  constexpr se_usize_t len = 12;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0x01;

  memset(src, value, len);
  void *result = se_memory_raw_copy(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_copy_rev, copy_rev_with64_divisible_length) {
  constexpr se_usize_t len = 64;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xAB;

  memset(src, value, len);
  void *result = se_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (se_usize_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(se_memory_raw_copy_rev, copy_rev_with32_divisible_length) {
  constexpr se_usize_t len = 32;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xCD;

  memset(src, value, len);
  void *result = se_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (se_usize_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(se_memory_raw_copy_rev, copy_rev_with16_divisible_length) {
  constexpr se_usize_t len = 16;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xEF;

  memset(src, value, len);
  void *result = se_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (se_usize_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(se_memory_raw_copy_rev, copy_rev_with8_divisible_length) {
  constexpr se_usize_t len = 8;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xFF;

  memset(src, value, len);
  void *result = se_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (se_usize_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(se_memory_raw_copy_rev, copy_rev_with_non_divisible_length) {
  constexpr se_usize_t len = 12;
  se_u8_t src[len];
  se_u8_t dst[len];
  constexpr se_u8_t value = 0x01;

  memset(src, value, len);
  void *result = se_memory_raw_copy_rev(dst, &dst[len], src, &src[len]);
  EXPECT_EQ(result, dst);

  for (se_usize_t i = 0; i < len; ++i) {
    ASSERT_EQ(dst[len - 1 - i], value);
  }
}

TEST(se_memory_raw_move, move64_bytes) {
  constexpr se_u64_t src[] = {1, 2, 3, 4};
  se_u64_t dst[4];

  void *result = se_memory_raw_move(dst, dst + 4, src, src + 4);
  ASSERT_EQ(result, &dst[4]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(dst[i], src[i]);
  }
}

TEST(se_memory_raw_move, move32_bytes) {
  constexpr se_u32_t src[] = {1, 2, 3, 4};
  se_u32_t dst[4];

  void *result = se_memory_raw_move(dst, dst + 4, src, src + 4);
  ASSERT_EQ(result, &dst[4]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(dst[i], src[i]);
  }
}

TEST(se_memory_raw_move, move16_bytes) {
  constexpr se_u16_t src[] = {1, 2, 3, 4};
  se_u16_t dst[4];

  void *result = se_memory_raw_move(dst, dst + 4, src, src + 4);
  ASSERT_EQ(result, &dst[4]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(dst[i], src[i]);
  }
}

TEST(se_memory_raw_move, move8_bytes) {
  constexpr se_u8_t src[] = {1, 2, 3, 4};
  se_u8_t dst[4];

  void *result = se_memory_raw_move(dst, dst + 4, src, src + 4);
  ASSERT_EQ(result, &dst[4]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(dst[i], src[i]);
  }
}

TEST(se_memory_raw_move, move64_bytes_overlap) {
  se_u64_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

  void *result = se_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
  ASSERT_EQ(result, &buf[6]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(buf[i + 2], i + 1);
  }
}

TEST(se_memory_raw_move, move32_bytes_overlap) {
  se_u32_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

  void *result = se_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
  ASSERT_EQ(result, &buf[6]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(buf[i + 2], i + 1);
  }
}

TEST(se_memory_raw_move, move16_bytes_overlap) {
  se_u16_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

  void *result = se_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
  ASSERT_EQ(result, &buf[6]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(buf[i + 2], i + 1);
  }
}

TEST(se_memory_raw_move, move8_bytes_overlap) {
  se_u8_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8};

  void *result = se_memory_raw_move(buf + 2, buf + 2 + 4, buf, buf + 4);
  ASSERT_EQ(result, &buf[6]);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(buf[i + 2], i + 1);
  }
}

TEST(se_memory_raw_find, NormalTest) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {3, 4};

  const void *result = se_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2);
  EXPECT_EQ(result, lhs + 2);
}

TEST(se_memory_raw_find, null_pointer) {
  const constexpr se_u8_t *lhs = nullptr;
  constexpr se_u8_t rhs[] = {3, 4};

  EXPECT_DEATH(se_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2), ".*");
}

TEST(se_memory_raw_find, empty_lhs) {
  const constexpr se_u8_t *lhs = nullptr;
  constexpr se_u8_t rhs[] = {3, 4};

  EXPECT_DEATH(se_memory_raw_find(lhs, lhs, rhs, rhs + 2), ".*");
}

TEST(se_memory_raw_find, empty_rhs) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  const constexpr se_u8_t *rhs = nullptr;

  EXPECT_DEATH(se_memory_raw_find(lhs, lhs + 5, rhs, rhs), ".*");
}

TEST(se_memory_raw_find, no_match) {
  constexpr se_u8_t lhs[] = {1, 2, 3, 4, 5};
  constexpr se_u8_t rhs[] = {6, 7};

  const void *result = se_memory_raw_find(lhs, lhs + 5, rhs, rhs + 2);
  EXPECT_EQ(result, nullptr);
}

TEST(se_memory_raw_find, match_at_start) {
  constexpr se_u8_t lhs[] = {3, 4, 5};
  constexpr se_u8_t rhs[] = {3, 4};

  const void *result = se_memory_raw_find(lhs, lhs + 3, rhs, rhs + 2);
  EXPECT_EQ(result, lhs);
}

TEST(se_memory_raw_find_rev, find_substring_in_string) {
  constexpr se_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  constexpr se_u8_t rhs[] = {0x03, 0x04};

  const void *result = se_memory_raw_find_rev(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 2);
}

TEST(se_memory_raw_find_rev, substring_not_found) {
  constexpr se_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  constexpr se_u8_t rhs[] = {0x07, 0x08};

  const void *result = se_memory_raw_find_rev(lhs, &lhs[6], rhs, &rhs[2]);
  ASSERT_EQ(result, nullptr);
}

TEST(se_memory_raw_find_rev, find_substring_at_end) {
  constexpr se_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  constexpr se_u8_t rhs[] = {0x05, 0x06};

  const void *result = se_memory_raw_find_rev(lhs, &lhs[6], rhs, &rhs[2]);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, lhs + 4);
}

TEST(se_memory_raw_find_rev, empty_arrays) {
  EXPECT_DEATH(se_memory_raw_find_rev(nullptr, nullptr, nullptr, nullptr),
               ".*");
}

TEST(se_memory_raw_find_rev, rhs_longer_than_lhs) {
  constexpr se_u8_t lhs[] = {0x01, 0x02, 0x03};
  constexpr se_u8_t rhs[] = {0x01, 0x02, 0x03, 0x04};

  ASSERT_EQ(se_memory_raw_find_rev(lhs, &lhs[3], rhs, &rhs[4]), nullptr);
}

TEST(se_memory_raw_find_rev, null_pointer_check) {
  constexpr se_u8_t lhs[] = {0x01, 0x02, 0x03, 0x04};
  constexpr se_u8_t rhs[] = {0x03, 0x04};
  EXPECT_DEATH(se_memory_raw_find_rev(nullptr, &lhs[4], rhs, &rhs[2]), ".*");
}

TEST(se_memory_raw_repeat, basic_set_operation) {
  se_u8_t dst[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  constexpr se_u8_t src[] = {0x01, 0x02, 0x03};

  void *result = se_memory_raw_repeat(dst, dst + 6, src, src + 3);

  ASSERT_EQ(result, dst + 6);
  EXPECT_EQ(dst[0], 0x01);
  EXPECT_EQ(dst[1], 0x02);
  EXPECT_EQ(dst[2], 0x03);
  EXPECT_EQ(dst[3], 0x01);
  EXPECT_EQ(dst[4], 0x02);
  EXPECT_EQ(dst[5], 0x03);
}

TEST(se_memory_raw_repeat, exact_size_fit) {
  se_u8_t dst[4] = {0x00, 0x00, 0x00, 0x00};
  constexpr se_u8_t src[] = {0xAA, 0xBB};

  void *result = se_memory_raw_repeat(dst, dst + 4, src, src + 2);

  ASSERT_EQ(result, dst + 4);
  EXPECT_EQ(dst[0], 0xAA);
  EXPECT_EQ(dst[1], 0xBB);
  EXPECT_EQ(dst[2], 0xAA);
  EXPECT_EQ(dst[3], 0xBB);
}

TEST(se_memory_raw_repeat, single_byte_pattern) {
  se_u8_t dst[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
  constexpr se_u8_t src[] = {0xFF};

  void *result = se_memory_raw_repeat(dst, dst + 5, src, src + 1);

  ASSERT_EQ(result, dst + 5);
  for (unsigned char i : dst) {
    EXPECT_EQ(i, 0xFF);
  }
}

TEST(se_memory_raw_repeat, null_pointer_check) {
  constexpr se_u8_t src[] = {0x01, 0x02};
  EXPECT_DEATH(se_memory_raw_repeat(nullptr, nullptr, src, src + 2), ".*");
}

TEST(se_memory_raw_repeat, partial_fill_at_end) {
  se_u8_t dst[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
  constexpr se_u8_t src[] = {0x11, 0x22, 0x33};

  void *result = se_memory_raw_repeat(dst, dst + 5, src, src + 3);

  ASSERT_EQ(result, dst + 5);
  EXPECT_EQ(dst[0], 0x11);
  EXPECT_EQ(dst[1], 0x22);
  EXPECT_EQ(dst[2], 0x33);
  EXPECT_EQ(dst[3], 0x11);
  EXPECT_EQ(dst[4], 0x22);
}

TEST(se_memory_raw_set, set_with64_divisible_length) {
  constexpr se_usize_t len = 64;
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xAB;

  void *result = se_memory_raw_set(dst, &dst[len], value);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_set, set_with32_divisible_length) {
  constexpr se_usize_t len = 32;
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xCD;

  void *result = se_memory_raw_set(dst, &dst[len], value);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_set, set_with16_divisible_length) {
  constexpr se_usize_t len = 16;
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xEF;

  void *result = se_memory_raw_set(dst, &dst[len], value);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_set, set_with8_divisible_length) {
  constexpr se_usize_t len = 8;
  se_u8_t dst[len];
  constexpr se_u8_t value = 0xFF;

  void *result = se_memory_raw_set(dst, &dst[len], value);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_set, set_with_non_divisible_length) {
  constexpr se_usize_t len = 12;
  se_u8_t dst[len];
  constexpr se_u8_t value = 0x01;

  void *result = se_memory_raw_set(dst, &dst[len], value);
  EXPECT_EQ(result, dst + len);

  for (unsigned char i : dst) {
    ASSERT_EQ(i, value);
  }
}

TEST(se_memory_raw_set, set_zero_length) {
  constexpr se_usize_t len = 0;
  se_u8_t dst[1] = {0xAA};
  constexpr se_u8_t value = 0x55;

  void *result = se_memory_raw_set(dst, dst, value);
  EXPECT_EQ(result, dst);
  ASSERT_EQ(dst[0], 0xAA);
}

TEST(se_memory_raw_set, set_static_array_16_bytes_int16) {
  se_u16_t dst[8];
  constexpr se_u8_t value = 0x3C;

  void *result = se_memory_raw_set(dst, dst + 8, value);
  EXPECT_EQ(result, dst + 8);

  const auto *ptr = reinterpret_cast<const se_u8_t *>(dst);
  for (size_t i = 0; i < 16; i++) {
    ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
  }
}

TEST(se_memory_raw_set, set_static_array_32_bytes_int32) {
  se_u32_t dst[8];
  constexpr se_u8_t value = 0x7E;

  void *result = se_memory_raw_set(dst, dst + 8, value);
  EXPECT_EQ(result, dst + 8);

  const auto *ptr = reinterpret_cast<const se_u8_t *>(dst);
  for (size_t i = 0; i < 32; i++) {
    ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
  }
}

TEST(se_memory_raw_set, set_static_array_64_bytes_mixed_types) {
  struct {
    se_u16_t a[16];
    se_u32_t b[8];
  } dst = {};
  constexpr se_u8_t value = 0xA5;

  void *result = se_memory_raw_set(&dst, &dst + 1, value);
  EXPECT_EQ(result, &dst + 1);

  const auto *ptr = reinterpret_cast<const se_u8_t *>(&dst);
  for (size_t i = 0; i < 64; i++) {
    ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
  }
}

TEST(se_memory_raw_set, set_large_static_array_1024_bytes_int64) {
  se_u64_t dst[128];
  constexpr se_u8_t value = 0x11;

  void *result = se_memory_raw_set(dst, dst + 128, value);
  EXPECT_EQ(result, dst + 128);

  const auto *ptr = reinterpret_cast<const se_u8_t *>(dst);
  for (size_t i = 0; i < 1024; i++) {
    ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
  }
}

TEST(se_memory_raw_set, set_small_non_power_of_two_array) {
  se_u32_t dst[5];
  constexpr se_u8_t value = 0xBD;

  void *result = se_memory_raw_set(dst, dst + 5, value);
  EXPECT_EQ(result, dst + 5);

  const auto *ptr = reinterpret_cast<const se_u8_t *>(dst);
  for (size_t i = 0; i < 20; i++) {
    ASSERT_EQ(ptr[i], value) << "Failed at byte " << i;
  }
}