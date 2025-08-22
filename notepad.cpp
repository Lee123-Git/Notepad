#include "notepad.h"
#include "ui_notepad.h"
#include <QCloseEvent>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Notepad),
    shortcutManager(nullptr),
    fileManager(nullptr),
    editManager(nullptr),
    fontManager(nullptr)
{
    // 初始化日志系统
    try {
        auto logger = spdlog::basic_logger_mt("file_logger", "notepad.log", true);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
        logger->flush_on(spdlog::level::warn);
        spdlog::set_default_logger(logger);
        spdlog::info("=== 记事本程序启动 ===");
    } catch (const spdlog::spdlog_ex& ex) {
        QMessageBox::critical(this, "日志错误",
                              QString("初始化日志系统失败:\n%1").arg(ex.what()));
    }

    // 初始化UI界面
    ui->setupUi(this);
    setWindowTitle(tr("记事本"));
    resize(800, 600);

    // 初始化管理器
    fileManager = new FileManager(ui->textEdit, this);
    editManager = new EditManager(ui->textEdit, this);
    fontManager = new FontManager(ui->textEdit, this);

    // 连接信号
    connect(fileManager, &FileManager::windowTitleChanged, this, &Notepad::setWindowTitle);

    // 初始化快捷键管理器
    shortcutManager = new ShortcutManager(
        this,
        [this](){ fileManager->newFile(); },
        [this](){ fileManager->openFile(); },
        [this](){ fileManager->saveFile(); },
        [this](){ editManager->showFindDialog(); },
        [this](){ editManager->showReplaceDialog(); },
        [this](){ editManager->undo(); },
        [this](){ editManager->redo(); },
        [this](){ fileManager->exitApp(); },
        [this](){ fontManager->setFontSize(); },
        [this](){ fontManager->increaseFontSize(); },
        [this](){ fontManager->decreaseFontSize(); }
        );

    // 手动连接菜单项的触发信号
    connect(ui->actionFind, &QAction::triggered, this, &Notepad::on_actionFind_triggered);
    connect(ui->actionReplace, &QAction::triggered, this, &Notepad::on_actionReplace_triggered);
    connect(ui->actionUndo, &QAction::triggered, this, &Notepad::on_actionUndo_triggered);
    connect(ui->actionRedo, &QAction::triggered, this, &Notepad::on_actionRedo_triggered);
    connect(ui->actionFont, &QAction::triggered, this, &Notepad::on_actionFont_triggered);
    connect(ui->actionSize, &QAction::triggered, this, &Notepad::on_actionSize_Triggered);
    connect(ui->actionSizeIncrease, &QAction::triggered, this, &Notepad::on_actionSizeIncrease_Triggered);
    connect(ui->actionSizeDecrease, &QAction::triggered, this, &Notepad::on_actionSizeDecrease_Triggered);
}

Notepad::~Notepad()
{
    spdlog::info("=== 记事本程序关闭 ===");
    spdlog::shutdown();

    delete ui;
    delete shortcutManager;
    delete fileManager;
    delete editManager;
    delete fontManager;
}

void Notepad::closeEvent(QCloseEvent *event)
{
    spdlog::debug("收到关闭事件");
    if (fileManager->maybeSave()) {
        event->accept();
        spdlog::info("窗口正常关闭");
    } else {
        event->ignore();
        spdlog::warn("用户取消窗口关闭");
    }
}

void Notepad::on_actionOpen_triggered()
{
    fileManager->openFile();
}

void Notepad::on_actionSave_triggered()
{
    fileManager->saveFile();
}

void Notepad::on_actionNew_triggered()
{
    fileManager->newFile();
}

void Notepad::on_actionExit_triggered()
{
    fileManager->exitApp();
}

void Notepad::on_actionUndo_triggered()
{
    editManager->undo();
}

void Notepad::on_actionRedo_triggered()
{
    editManager->redo();
}

void Notepad::on_actionFind_triggered()
{
    editManager->showFindDialog();
}

void Notepad::on_actionReplace_triggered()
{
    editManager->showReplaceDialog();
}

void Notepad::on_actionFont_triggered()
{
    fontManager->setFont();
}

void Notepad::on_actionSize_Triggered()
{
    fontManager->setFontSize();
}

void Notepad::on_actionSizeIncrease_Triggered()
{
    fontManager->increaseFontSize();
}

void Notepad::on_actionSizeDecrease_Triggered()
{
    fontManager->decreaseFontSize();
}
