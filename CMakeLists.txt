# bss-util cmake file
# Licensed under Apache Public License 2.0

cmake_minimum_required(VERSION 3.1)

set(BSS-UTIL_VERSION 0.5.2.0)

# Options in this build
option(BSS-UTIL_STATIC "Build BSS-Util as a static library" OFF)
option(BSS-UTIL_BUILD_TESTS "Build library tests" ON)

project(bss-util VERSION ${BSS-UTIL_VERSION})

# Add sources and includes (includes are requires for IDEs like XCode for Visual Studio)
set(SOURCES ${CMAKE_SOURCE_DIR}/bss-util/bss_util.cpp ${CMAKE_SOURCE_DIR}/bss-util/bss_util_c.c ${CMAKE_SOURCE_DIR}/bss-util/ConvertUTF.c ${CMAKE_SOURCE_DIR}/bss-util/HighPrecisionTimer.cpp
    ${CMAKE_SOURCE_DIR}/bss-util/INIentry.cpp ${CMAKE_SOURCE_DIR}/bss-util/INIParser.c ${CMAKE_SOURCE_DIR}/bss-util/INIsection.cpp ${CMAKE_SOURCE_DIR}/bss-util/INIstorage.cpp ${CMAKE_SOURCE_DIR}/bss-util/Logger.cpp
    ${CMAKE_SOURCE_DIR}/bss-util/profiler.cpp ${CMAKE_SOURCE_DIR}/bss-util/UBJSON.cpp ${CMAKE_SOURCE_DIR}/bss-util/XML.cpp)

set(INCLUDES ${CMAKE_SOURCE_DIR}/include/bss-util/AATree.h ${CMAKE_SOURCE_DIR}/include/bss-util/algo.h ${CMAKE_SOURCE_DIR}/include/bss-util/AliasTable.h ${CMAKE_SOURCE_DIR}/include/bss-util/Alloc.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/Animation.h ${CMAKE_SOURCE_DIR}/include/bss-util/Array.h ${CMAKE_SOURCE_DIR}/include/bss-util/ArrayCircular.h ${CMAKE_SOURCE_DIR}/include/bss-util/ArraySort.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/AVLTree.h ${CMAKE_SOURCE_DIR}/include/bss-util/BinaryHeap.h ${CMAKE_SOURCE_DIR}/include/bss-util/BitField.h ${CMAKE_SOURCE_DIR}/include/bss-util/BitStream.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/BlockAlloc.h ${CMAKE_SOURCE_DIR}/include/bss-util/BlockAllocMT.h ${CMAKE_SOURCE_DIR}/include/bss-util/bss_util.h ${CMAKE_SOURCE_DIR}/include/bss-util/bss_util_c.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/CacheAlloc.h ${CMAKE_SOURCE_DIR}/include/bss-util/Collision.h ${CMAKE_SOURCE_DIR}/include/bss-util/CompactArray.h ${CMAKE_SOURCE_DIR}/include/bss-util/compare.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/compiler.h ${CMAKE_SOURCE_DIR}/include/bss-util/defines.h ${CMAKE_SOURCE_DIR}/include/bss-util/Delegate.h ${CMAKE_SOURCE_DIR}/include/bss-util/DisjointSet.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/Dual.h ${CMAKE_SOURCE_DIR}/include/bss-util/DynArray.h ${CMAKE_SOURCE_DIR}/include/bss-util/FixedPt.h ${CMAKE_SOURCE_DIR}/include/bss-util/Geometry.h ${CMAKE_SOURCE_DIR}/include/bss-util/Graph.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/GreedyAlloc.h ${CMAKE_SOURCE_DIR}/include/bss-util/GreedyBlockAlloc.h ${CMAKE_SOURCE_DIR}/include/bss-util/Hash.h ${CMAKE_SOURCE_DIR}/include/bss-util/HighPrecisionTimer.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/INIentry.h ${CMAKE_SOURCE_DIR}/include/bss-util/INIparse.h ${CMAKE_SOURCE_DIR}/include/bss-util/INIsection.h ${CMAKE_SOURCE_DIR}/include/bss-util/INIstorage.h ${CMAKE_SOURCE_DIR}/include/bss-util/JSON.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/KDTree.h ${CMAKE_SOURCE_DIR}/include/bss-util/khash.h ${CMAKE_SOURCE_DIR}/include/bss-util/LinkedArray.h ${CMAKE_SOURCE_DIR}/include/bss-util/LinkedList.h ${CMAKE_SOURCE_DIR}/include/bss-util/literals.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/LLBase.h ${CMAKE_SOURCE_DIR}/include/bss-util/lockless.h ${CMAKE_SOURCE_DIR}/include/bss-util/LocklessQueue.h ${CMAKE_SOURCE_DIR}/include/bss-util/Logger.h ${CMAKE_SOURCE_DIR}/include/bss-util/Map.h ${CMAKE_SOURCE_DIR}/include/bss-util/os.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/PriorityQueue.h ${CMAKE_SOURCE_DIR}/include/bss-util/Profiler.h ${CMAKE_SOURCE_DIR}/include/bss-util/Queue.h ${CMAKE_SOURCE_DIR}/include/bss-util/RandomQueue.h ${CMAKE_SOURCE_DIR}/include/bss-util/Rational.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/RefCounter.h ${CMAKE_SOURCE_DIR}/include/bss-util/RingAlloc.h ${CMAKE_SOURCE_DIR}/include/bss-util/RWLock.h ${CMAKE_SOURCE_DIR}/include/bss-util/Scheduler.h ${CMAKE_SOURCE_DIR}/include/bss-util/Serializer.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/Singleton.h ${CMAKE_SOURCE_DIR}/include/bss-util/SmartPtr.h ${CMAKE_SOURCE_DIR}/include/bss-util/sseVec.h ${CMAKE_SOURCE_DIR}/include/bss-util/Stack.h ${CMAKE_SOURCE_DIR}/include/bss-util/Str.h ${CMAKE_SOURCE_DIR}/include/bss-util/stream.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/StringTable.h ${CMAKE_SOURCE_DIR}/include/bss-util/Thread.h ${CMAKE_SOURCE_DIR}/include/bss-util/ThreadPool.h ${CMAKE_SOURCE_DIR}/include/bss-util/TOML.h ${CMAKE_SOURCE_DIR}/include/bss-util/TRBtree.h ${CMAKE_SOURCE_DIR}/include/bss-util/Trie.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/UBJSON.h ${CMAKE_SOURCE_DIR}/include/bss-util/utf_conv.h ${CMAKE_SOURCE_DIR}/include/bss-util/Variant.h ${CMAKE_SOURCE_DIR}/include/bss-util/vector.h ${CMAKE_SOURCE_DIR}/include/bss-util/win32_includes.h ${CMAKE_SOURCE_DIR}/include/bss-util/XML.h
    ${CMAKE_SOURCE_DIR}/include/bss-util/XorshiftEngine.h ${CMAKE_SOURCE_DIR}/bss-util/fontconfig/fontconfig.h)

set(LIBRARY_NAME "bss-util")

# Arch postfix as shown in test.cpp
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(LIBRARY_NAME "${LIBRARY_NAME}32")
endif()

# Static/dynamic library switch
if (BSS-UTIL_STATIC)
    set(LIBRARY_TYPE STATIC)
    set(LIBRARY_NAME "${LIBRARY_NAME}_s")
else()
    set(LIBRARY_TYPE SHARED)
endif()

add_library(${LIBRARY_NAME} ${LIBRARY_TYPE} ${SOURCES} ${INCLUDES} ${CMAKE_SOURCE_DIR}/bss-util/bss-util.rc)

# Common target directives
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include PRIVATE ${CMAKE_SOURCE_DIR}/bss-util/fontconfig)
set_target_properties(${LIBRARY_NAME} PROPERTIES DEBUG_POSTFIX "_d" CXX_STANDARD 17)

# Windows specific options
if (WIN32)
    target_link_libraries(${LIBRARY_NAME} PUBLIC psapi)

    # Enable unicode build
    target_compile_definitions(${LIBRARY_NAME} PRIVATE _UNICODE UNICODE)
endif()

# Linking options if the library is static or not
if (NOT BSS-UTIL_STATIC)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE BSS_UTIL_EXPORTS)
else()
    target_compile_definitions(${LIBRARY_NAME} PUBLIC BSS_STATIC_LIB)
endif()

# Build the test executable or not
if (BSS-UTIL_BUILD_TESTS)
    set(TESTS_SRC ${CMAKE_SOURCE_DIR}/test/test.cpp ${CMAKE_SOURCE_DIR}/test/test.h ${CMAKE_SOURCE_DIR}/test/test_aatree.cpp ${CMAKE_SOURCE_DIR}/test/test_aliastable.cpp
        ${CMAKE_SOURCE_DIR}/test/test_alloc.h ${CMAKE_SOURCE_DIR}/test/test_animation.cpp ${CMAKE_SOURCE_DIR}/test/test_array.cpp ${CMAKE_SOURCE_DIR}/test/test_arraycircular.cpp
        ${CMAKE_SOURCE_DIR}/test/test_arraysort.cpp ${CMAKE_SOURCE_DIR}/test/test_avltree.cpp ${CMAKE_SOURCE_DIR}/test/test_binaryheap.cpp ${CMAKE_SOURCE_DIR}/test/test_bitfield.cpp
        ${CMAKE_SOURCE_DIR}/test/test_bss_algo.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_alloc_block.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_alloc_block_mt.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_alloc_cache.cpp
        ${CMAKE_SOURCE_DIR}/test/test_bss_alloc_circular.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_alloc_greedy.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_alloc_greedy_block.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_defines.cpp
        ${CMAKE_SOURCE_DIR}/test/test_bss_graph.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_logger.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_sse.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_util.cpp ${CMAKE_SOURCE_DIR}/test/test_bss_util_c.cpp
        ${CMAKE_SOURCE_DIR}/test/test_bss_vector.cpp ${CMAKE_SOURCE_DIR}/test/test_c.c ${CMAKE_SOURCE_DIR}/test/test_collision.cpp ${CMAKE_SOURCE_DIR}/test/test_compactarray.cpp ${CMAKE_SOURCE_DIR}/test/test_delegate.cpp
        ${CMAKE_SOURCE_DIR}/test/test_disjointset.cpp ${CMAKE_SOURCE_DIR}/test/test_dual.cpp ${CMAKE_SOURCE_DIR}/test/test_dynarray.cpp ${CMAKE_SOURCE_DIR}/test/test_fixedpt.cpp ${CMAKE_SOURCE_DIR}/test/test_geometry.cpp
        ${CMAKE_SOURCE_DIR}/test/test_hash.cpp ${CMAKE_SOURCE_DIR}/test/test_highprecisiontimer.cpp ${CMAKE_SOURCE_DIR}/test/test_inistorage.cpp ${CMAKE_SOURCE_DIR}/test/test_json.cpp ${CMAKE_SOURCE_DIR}/test/test_kdtree.cpp
        ${CMAKE_SOURCE_DIR}/test/test_linkedarray.cpp ${CMAKE_SOURCE_DIR}/test/test_linkedlist.cpp ${CMAKE_SOURCE_DIR}/test/test_literals.cpp ${CMAKE_SOURCE_DIR}/test/test_lockless.cpp ${CMAKE_SOURCE_DIR}/test/test_locklessqueue.cpp
        ${CMAKE_SOURCE_DIR}/test/test_map.cpp ${CMAKE_SOURCE_DIR}/test/test_os.cpp ${CMAKE_SOURCE_DIR}/test/test_priorityqueue.cpp ${CMAKE_SOURCE_DIR}/test/test_profile.cpp ${CMAKE_SOURCE_DIR}/test/test_queue.cpp ${CMAKE_SOURCE_DIR}/test/test_randomqueue.cpp
        ${CMAKE_SOURCE_DIR}/test/test_rational.cpp ${CMAKE_SOURCE_DIR}/test/test_refcounter.cpp ${CMAKE_SOURCE_DIR}/test/test_rwlock.cpp ${CMAKE_SOURCE_DIR}/test/test_scheduler.cpp ${CMAKE_SOURCE_DIR}/test/test_serializer.cpp ${CMAKE_SOURCE_DIR}/test/test_singleton.cpp
        ${CMAKE_SOURCE_DIR}/test/test_smartptr.cpp ${CMAKE_SOURCE_DIR}/test/test_stack.cpp ${CMAKE_SOURCE_DIR}/test/test_str.cpp ${CMAKE_SOURCE_DIR}/test/test_stream.cpp ${CMAKE_SOURCE_DIR}/test/test_strtable.cpp ${CMAKE_SOURCE_DIR}/test/test_thread.cpp ${CMAKE_SOURCE_DIR}/test/test_threadpool.cpp
        ${CMAKE_SOURCE_DIR}/test/test_toml.cpp ${CMAKE_SOURCE_DIR}/test/test_trbtree.cpp ${CMAKE_SOURCE_DIR}/test/test_trie.cpp ${CMAKE_SOURCE_DIR}/test/test_ubjson.cpp ${CMAKE_SOURCE_DIR}/test/test_variant.cpp ${CMAKE_SOURCE_DIR}/test/test_xml.cpp ${CMAKE_SOURCE_DIR}/test/util.cpp ${CMAKE_SOURCE_DIR}/test/test_bitstream.cpp)

    add_executable(bss-util_tests ${TESTS_SRC} ${CMAKE_SOURCE_DIR}/test/test.rc)
    target_link_libraries(bss-util_tests ${LIBRARY_NAME})
    set_target_properties(bss-util_tests PROPERTIES DEBUG_POSTFIX "_d" CXX_STANDARD 17)
endif()
