#include "gtest/gtest.h"

#include <cppthings/defer.hpp>

TEST (cppthings, Defer) {
  int i = 0;
  {
    cppthings::defer([&]() { i = 33; });
  }
  EXPECT_EQ(i, 33);
}


TEST (cppthings, DeferCancel) {
  int i = 0;
  {
    cppthings::defer([&]() { i = 33; }).cancel();
  }
  EXPECT_EQ(i, 0);
}

TEST (cppthings, Transactions) {
  int i = 0;
  {
    cppthings::transaction tx;
    i += 1;
    tx.add([&]{ i -= 1; });
    i += 3;
    tx.add([&]{ i -= 3; });
    EXPECT_EQ(i, 4);
    tx.rollback();
    EXPECT_EQ(i, 0);
    i += 1;
    tx.add([&] { i -= 1; });
  }
  EXPECT_EQ(i, 0);
}

TEST (cppthings, TransactionsAutoManual) {
  int i = 0;
  {
    cppthings::transaction tx;
    i += 1;
    tx.add([&]{ i -= 1; });
    i += 3;
    tx.add([&]{ i -= 3; });
    EXPECT_EQ(i, 4);
    tx.rollback();
    EXPECT_EQ(i, 0);

  }
  EXPECT_EQ(i, 0);
}

TEST (cppthings, TransactionsNonAuto) {
  int i = 0;
  {
    cppthings::transaction tx(false);
    i += 1;
    tx.add([&]{ i -= 1; });
    i += 3;
    tx.add([&]{ i -= 3; });
    EXPECT_EQ(i, 4);
  }
  EXPECT_EQ(i, 4);
}

TEST (cppthings, TransactionsManual) {
  int i = 0;
  {
    cppthings::transaction tx(false);
    i += 1;
    tx.add([&]{ i -= 1; });
    i += 3;
    tx.add([&]{ i -= 3; });
    EXPECT_EQ(i, 4);
    tx.rollback();
    EXPECT_EQ(i, 0);
    i += 1;
    tx.add([&] { i -= 1; });
  }
  EXPECT_EQ(i, 1);
}
