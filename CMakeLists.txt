cmake_minimum_required(VERSION 3.5)
project(myproject)

# 建立 foo 函示庫
#add_library(foo STATIC ./System/power_manager.c)

# 加入 include 資料夾給 foo.hpp
#target_include_directories(foo PUBLIC ./src)
INCLUDE_DIRECTORIES("./")

# 建立可執行檔 main
#add_executable(main ./main/main.cpp)

# 將可執行檔和函示庫做連結
#target_link_libraries(main PUBLIC foo)

# 使用 FetchContent 模組
include(FetchContent)
# 下載和引入 Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# 建立一個測試用的可執行檔 test_foo
add_executable(link_list_test
    ./main.cpp
    ./tst_code_test.cpp
    ./src/link_list.c
    )
# 連結必要函示庫給 test_foo
target_link_libraries(link_list_test PRIVATE gtest gtest_main)

# 開啟 CMake 測試
enable_testing()

# 把 test_foo 加進命名 my_project_test 的測試
add_test(
    NAME my_project_test
    COMMAND link_list_test
)
