cmake_minimum_required(VERSION 3.19)

# ================= MSVC / MinGW 运行时配置 =================
if(MSVC)
    cmake_policy(SET CMP0091 NEW)
    # MultiThreaded DLL，Debug 自动加 Debug 后缀
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
elseif(MINGW)
    add_compile_options(-mthreads)
endif()

# ================= vcpkg 工具链 =================
if(NOT VCPKG_ROOT)
    set(VCPKG_ROOT "D:/vcpkg")  # 修改为你的 vcpkg 路径
endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain" FORCE)

project(Notepad LANGUAGES CXX)

# ================= C++ 标准 =================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制要求支持 C++17

# ================= Qt6Core =================
list(APPEND CMAKE_PREFIX_PATH
    "${VCPKG_ROOT}/installed/x64-windows"
    "D:/Qt/6.9.1/msvc2022_64/lib/cmake/Qt6"  # 修改为你的 Qt6 路径
)
find_package(Qt6 6.9 REQUIRED COMPONENTS Core Widgets)

# ================= 第三方库 =================
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

# ================= 可执行文件 =================
qt_add_executable(Notepad
    WIN32 MACOSX_BUNDLE
    main.cpp
    notepad.ui
    notepad.h
    notepad.cpp
    notepad.ui
    shortcutmanager.h shortcutmanager.cpp


    res.qrc
    res.qrc

    res.qrc
    res.qrc
    res.qrc
    filemanager.h filemanager.cpp
    editmanager.h editmanager.cpp
    fontmanager.h fontmanager.cpp
)

# 添加资源文件

target_sources(Notepad PRIVATE ${Notepad_RESOURCES})
set_target_properties(Notepad PROPERTIES
    AUTOMOC ON  # 确保开启 自动处理 Q_OBJECT 宏（信号槽依赖）
    AUTOUIC ON  # 确保开启 自动处理 .ui 文件
    AUTORCC ON  # 确保开启 自动处理 .qrc 资源文件
)
# ================= 链接库 =================
target_link_libraries(Notepad PRIVATE
    Qt6::Core
    Qt6::Widgets
    fmt::fmt-header-only          # header-only，避免 Debug/Release 冲突
    spdlog::spdlog_header_only    # header-only
    OpenSSL::SSL
    OpenSSL::Crypto
)
target_link_libraries(Notepad PRIVATE Qt6::Core)
target_link_libraries(Notepad PRIVATE Qt6::Core)
target_link_libraries(Notepad PRIVATE Qt6::Core)
target_link_libraries(Notepad PRIVATE Qt6::Core)
target_link_libraries(Notepad PRIVATE Qt6::Core)

# ================= Windows 控制台 UTF-8 =================
if(WIN32)
    target_compile_definitions(Notepad PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
