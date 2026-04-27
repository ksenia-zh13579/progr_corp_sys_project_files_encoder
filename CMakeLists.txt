cmake_minimum_required(VERSION 3.16)
project(Progr_Corp_Sys_project_Files_encoder VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 OPTIONAL_COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(Progr_Corp_Sys_project_Files_encoder WIN32 MACOSX_BUNDLE
    include/cipherbase.h
    include/decodedialog.h
    include/decoder.h
    include/encodedialog.h
    include/encoder.h
    include/mainwindow.h
    src/cipherbase.cpp
    src/decodedialog.cpp
    src/decoder.cpp
    src/encodedialog.cpp
    src/encoder.cpp
    src/main.cpp
    src/mainwindow.cpp
    ui/decodedialog.ui
    ui/encodedialog.ui
    ui/mainwindow.ui
)
target_include_directories(Progr_Corp_Sys_project_Files_encoder PRIVATE
    C:/msys64/ucrt64/include
    include
)

target_link_libraries(Progr_Corp_Sys_project_Files_encoder PRIVATE
    C:/msys64/ucrt64/lib
    Qt::Core
    Qt::Gui
    crypto
    ssl
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(Progr_Corp_Sys_project_Files_encoder PRIVATE
        Qt::Widgets
    )
endif()

install(TARGETS Progr_Corp_Sys_project_Files_encoder
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET Progr_Corp_Sys_project_Files_encoder
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
