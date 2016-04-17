/** @file AllocatorTests.cpp
 *
 *  Unit tests for pistis::testing::Allocator
 */
#include <pistis/testing/Allocator.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <stdint.h>

using namespace pistis::testing;

TEST(Allocator, ConstructionTest) {
  Allocator<uint32_t> nameless;
  Allocator<uint32_t> named("TEST");

  EXPECT_EQ("", nameless.name());
  EXPECT_FALSE(nameless.movedFrom());
  EXPECT_FALSE(nameless.moved());
  
  EXPECT_EQ("TEST", named.name());
  EXPECT_FALSE(named.movedFrom());
  EXPECT_FALSE(named.moved());
}

TEST(Allocator, CopyConstructionTest) {
  Allocator<uint32_t> src("TEST");
  Allocator<uint32_t> dest(src);

  EXPECT_EQ("TEST", src.name());
  EXPECT_FALSE(src.movedFrom());
  EXPECT_FALSE(src.moved());
  
  EXPECT_EQ("TEST", dest.name());
  EXPECT_FALSE(dest.movedFrom());
  EXPECT_FALSE(dest.moved());
}

TEST(Allocator, MoveConstructionTest) {
  Allocator<uint32_t> src("TEST");
  Allocator<uint32_t> dest(std::move(src));

  // State of src is undefined, except for src.movedFrom()
  EXPECT_TRUE(src.movedFrom());

  EXPECT_EQ("TEST", dest.name());
  EXPECT_TRUE(dest.moved());
  EXPECT_FALSE(dest.movedFrom());
}

TEST(Allocator, CopyAssignmentTest) {
  Allocator<uint32_t> src("TEST");
  Allocator<uint32_t> dest;

  EXPECT_EQ("TEST", src.name());
  EXPECT_FALSE(src.moved());
  EXPECT_FALSE(src.movedFrom());
  
  EXPECT_EQ("", dest.name());
  EXPECT_FALSE(dest.moved());
  EXPECT_FALSE(dest.movedFrom());

  dest = src;
  EXPECT_EQ("TEST", src.name());
  EXPECT_FALSE(src.moved());
  EXPECT_FALSE(src.movedFrom());
  
  EXPECT_EQ("TEST", dest.name());
  EXPECT_FALSE(dest.moved());
  EXPECT_FALSE(dest.movedFrom());
}

TEST(Allocator, MoveAssignmentTest) {
  Allocator<uint32_t> src("TEST");
  Allocator<uint32_t> dest;

  EXPECT_EQ("TEST", src.name());
  EXPECT_FALSE(src.moved());
  EXPECT_FALSE(src.movedFrom());
  
  EXPECT_EQ("", dest.name());
  EXPECT_FALSE(dest.moved());
  EXPECT_FALSE(dest.movedFrom());

  dest = std::move(src);
  EXPECT_TRUE(src.movedFrom());
  EXPECT_EQ("TEST", dest.name());
  EXPECT_TRUE(dest.moved());
}

