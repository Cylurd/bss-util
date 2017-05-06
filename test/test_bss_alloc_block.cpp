// Copyright �2017 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in "bss_util.h"

#include "bss-util/bss_alloc_block.h"
#include "test_alloc.h"

using namespace bss;

TESTDEF::RETPAIR test_bss_ALLOC_BLOCK()
{
  BEGINTEST;
  TEST_ALLOC_FUZZER<BlockAlloc<size_t>, size_t, 1, 10000>(__testret);
  ENDTEST;
}