#include "shortcutmanager.h"

ShortcutManager::ShortcutManager(QWidget *parent,
                                 std::function<void()> newFunc,
                                 std::function<void()> openFunc,
                                 std::function<void()> saveFunc,
                                 std::function<void()> findFunc,
                                 std::function<void()> replaceFunc,
                                 std::function<void()> undoFunc,
                                 std::function<void()> redoFunc,
                                 std::function<void()> exitFunc,
                                 std::function<void()> setFontSizeFunc,
                                 std::function<void()> increaseFontSizeFunc,
                                 std::function<void()> decreaseFontSizeFunc)
    : QObject(parent)
{
    // 1. 新建文件：Ctrl+N
    auto* shortcutNew = new QShortcut(QKeySequence("Ctrl+N"), parent);
    connect(shortcutNew, &QShortcut::activated, parent, newFunc);
    shortcuts.append(shortcutNew);

    // 2. 打开文件：Ctrl+O
    auto* shortcutOpen = new QShortcut(QKeySequence("Ctrl+O"), parent);
    connect(shortcutOpen, &QShortcut::activated, parent, openFunc);
    shortcuts.append(shortcutOpen);

    // 3. 保存文件：Ctrl+S
    auto* shortcutSave = new QShortcut(QKeySequence("Ctrl+S"), parent);
    connect(shortcutSave, &QShortcut::activated, parent, saveFunc);
    shortcuts.append(shortcutSave);

    // 4. 查找：Ctrl+F
    auto* shortcutFind = new QShortcut(QKeySequence("Ctrl+F"), parent);
    connect(shortcutFind, &QShortcut::activated, parent, findFunc);
    shortcuts.append(shortcutFind);

    // 5. 替换：Ctrl+H
    auto* shortcutReplace = new QShortcut(QKeySequence("Ctrl+H"), parent);
    connect(shortcutReplace, &QShortcut::activated, parent, replaceFunc);
    shortcuts.append(shortcutReplace);

    // 6. 撤销：Ctrl+Z
    auto* shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), parent);
    connect(shortcutUndo, &QShortcut::activated, parent, undoFunc);
    shortcuts.append(shortcutUndo);

    // 7. 重做：Ctrl+Y
    auto* shortcutRedo = new QShortcut(QKeySequence("Ctrl+Y"), parent);
    connect(shortcutRedo, &QShortcut::activated, parent, redoFunc);
    shortcuts.append(shortcutRedo);

    // 8. 退出：Ctrl+Q
    auto* shortcutExit = new QShortcut(QKeySequence("Ctrl+Q"), parent);
    connect(shortcutExit, &QShortcut::activated, parent, exitFunc);
    shortcuts.append(shortcutExit);

    // 9. 字体大小设置：Ctrl+Shift+S
    auto* shortcutSetFontSize = new QShortcut(QKeySequence("Ctrl+Shift+S"), parent);
    connect(shortcutSetFontSize, &QShortcut::activated, parent, setFontSizeFunc);
    shortcuts.append(shortcutSetFontSize);

    // 10. 增大字体：Ctrl+=
    auto* shortcutIncreaseFont = new QShortcut(QKeySequence("Ctrl+="), parent);
    connect(shortcutIncreaseFont, &QShortcut::activated, parent, increaseFontSizeFunc);
    shortcuts.append(shortcutIncreaseFont);

    // 11. 减小字体：Ctrl+-
    auto* shortcutDecreaseFont = new QShortcut(QKeySequence("Ctrl+-"), parent);
    connect(shortcutDecreaseFont, &QShortcut::activated, parent, decreaseFontSizeFunc);
    shortcuts.append(shortcutDecreaseFont);
}

ShortcutManager::~ShortcutManager()
{
    qDeleteAll(shortcuts);
    shortcuts.clear();
}
