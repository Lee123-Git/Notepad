# Qt 记事本应用

一个基于 Qt6 开发的现代化记事本应用程序，提供了丰富的文本编辑功能和用户友好的界面。

## 功能特性

### 📝 文本编辑
- 新建、打开、保存文本文件
- 撤销/重做操作
- 完整的文本编辑功能
- 自动检测未保存更改

### 🔍 查找与替换
- 查找文本内容
- 替换指定文本
- 支持全局替换操作

### 🎨 字体管理
- 自定义字体选择
- 字体大小调整
- 字体放大/缩小快捷键
- 实时字体大小显示

### ⌨️ 快捷键支持
- `Ctrl+N` - 新建文件
- `Ctrl+O` - 打开文件
- `Ctrl+S` - 保存文件
- `Ctrl+Z` - 撤销
- `Ctrl+Y` - 重做
- `Ctrl+F` - 查找
- `Ctrl+H` - 替换
- `Ctrl+Q` - 退出
- `Ctrl+=` - 增大字体
- `Ctrl+-` - 减小字体
- `Ctrl+Shift+S` - 设置字体大小

### 📊 日志系统
- 使用 spdlog 记录操作日志
- 自动记录程序启动和关闭
- 记录用户操作和错误信息

## 构建说明

### 环境要求
- CMake 3.19 或更高版本
- Qt 6.9.1 或更高版本
- C++17 兼容编译器
- vcpkg 包管理器

### 构建步骤

1. 克隆项目到本地
```bash
git clone <repository-url>
cd Notepad
```

2. 配置构建环境
```bash
# 设置 vcpkg 路径（根据你的实际安装路径修改）
set VCPKG_ROOT=D:/vcpkg

# 创建构建目录并配置
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake
```

3. 编译项目
```bash
cmake --build . --config Release
```

4. 运行应用程序
```bash
./Release/Notepad.exe  # Windows
./Notepad              # Linux/macOS
```

## 项目结构

```
Notepad/
├── CMakeLists.txt          # 项目构建配置
├── main.cpp               # 应用程序入口点
├── notepad.h              # 主窗口类声明
├── notepad.cpp            # 主窗口类实现
├── notepad.ui             # 主窗口UI设计
├── filemanager.h          # 文件管理功能
├── filemanager.cpp        # 文件管理实现
├── editmanager.h          # 编辑管理功能
├── editmanager.cpp        # 编辑管理实现
├── fontmanager.h          # 字体管理功能
├── fontmanager.cpp        # 字体管理实现
├── shortcutmanager.h      # 快捷键管理
├── shortcutmanager.cpp    # 快捷键实现
├── res.qrc                # 资源文件
└── README.md              # 项目说明文档
```

## 依赖项

- **Qt6**: Core, Widgets 模块
- **spdlog**: 高性能日志库
- **fmt**: 现代字符串格式化库
- **OpenSSL**: 加密支持（可选）

## 使用说明

1. **基本操作**:
   - 使用菜单栏或快捷键进行文件操作
   - 文本编辑区支持常规文本编辑操作
   - 状态栏显示当前字体大小信息

2. **字体调整**:
   - 使用 `Ctrl+=` 和 `Ctrl+-` 快速调整字体大小
   - 通过菜单选择特定字体和大小
   - 状态栏会显示当前字体大小变化

3. **查找替换**:
   - 使用 `Ctrl+F` 打开查找对话框
   - 使用 `Ctrl+H` 打开替换对话框
   - 支持全文查找和替换操作

4. **日志查看**:
   - 应用程序运行日志保存在 `notepad.log` 文件中
   - 包含操作记录和错误信息

## 开发说明

此项目采用模块化设计，将不同功能分离到独立的管理器类中：

- **FileManager**: 处理文件操作
- **EditManager**: 处理文本编辑和查找替换
- **FontManager**: 处理字体相关功能
- **ShortcutManager**: 管理所有快捷键

这种设计使得代码结构清晰，易于维护和扩展。
