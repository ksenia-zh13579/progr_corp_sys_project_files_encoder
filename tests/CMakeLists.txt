cmake_minimum_required(VERSION 3.16)
project(tests VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(tests
    ../include/cipherbase.h
    ../include/decoder.h
    ../include/encoder.h
    ../src/cipherbase.cpp
    ../src/decoder.cpp
    ../src/encoder.cpp
    main.cpp
    test_cipherbase.cpp
    test_decoder.cpp
    test_encoder.cpp
    test_scenarios.cpp
)
target_include_directories(tests PRIVATE
    ../include
    C:/msys64/ucrt64/include
)

target_link_libraries(tests PRIVATE
    C:/msys64/ucrt64/lib/libcrypto.dll.a
    C:/msys64/ucrt64/lib/libssl.dll.a
    Qt::Core
    Qt::Gui
    Qt::Widgets
    crypt32
)

if(NOT GTEST_SRCDIR_ISEMPTY)
    target_sources(tests PUBLIC
        /src/gtest-all.cc
    )

    target_include_directories(tests PRIVATE
        /include
    )
endif()

if(NOT GMOCK_SRCDIR_ISEMPTY)
    target_sources(tests PUBLIC
        /src/gmock-all.cc
    )

    target_include_directories(tests PRIVATE
        /include
    )
endif()

install(TARGETS tests
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET tests
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
