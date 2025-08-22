#ifndef NOTEPAD_H
#define NOTEPAD_H

#include "shortcutmanager.h"
#include "filemanager.h"
#include "editmanager.h"
#include "fontmanager.h"

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // 文件操作
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionExit_triggered();

    // 编辑操作
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionFind_triggered();
    void on_actionReplace_triggered();

    // 字体操作
    void on_actionFont_triggered();
    void on_actionSize_Triggered();
    void on_actionSizeIncrease_Triggered();
    void on_actionSizeDecrease_Triggered();

private:
    Ui::Notepad *ui;
    ShortcutManager* shortcutManager;

    // 管理器类
    FileManager *fileManager;
    EditManager *editManager;
    FontManager *fontManager;
};

#endif // NOTEPAD_H
