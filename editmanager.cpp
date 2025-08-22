#include "EditManager.h"
#include <QTextEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextCursor>
#include <spdlog/spdlog.h>

EditManager::EditManager(QTextEdit *textEdit, QMainWindow *parent)
    : QObject(parent), textEdit(textEdit), parentWindow(parent),
    findDialog(nullptr), replaceDialog(nullptr)
{
    // 创建对话框
    createFindDialog();
    createReplaceDialog();
}

EditManager::~EditManager()
{
    delete findDialog;
    delete replaceDialog;
}

void EditManager::createFindDialog()
{
    // 创建查找对话框
    findDialog = new QDialog(parentWindow);
    findDialog->setWindowTitle(tr("查找"));
    findDialog->setMinimumWidth(300);

    // 初始化控件
    auto *findLabel = new QLabel(tr("查找内容:"), findDialog);
    findEdit = new QLineEdit(findDialog);
    findEdit->setPlaceholderText(tr("输入要查找的文本..."));

    findBtn = new QPushButton(tr("查找下一个"), findDialog);
    findBtn->setDefault(true);

    // 设置布局
    auto *layout = new QGridLayout(findDialog);
    layout->addWidget(findLabel, 0, 0, 1, 2);
    layout->addWidget(findEdit, 1, 0, 1, 2);
    layout->addWidget(findBtn, 2, 1);
    layout->setContentsMargins(15, 15, 15, 15);
    findDialog->setLayout(layout);

    // 绑定按钮点击事件 - 使用 lambda 表达式确保正确的连接
    connect(findBtn, &QPushButton::clicked, this, [this]() {
        this->onFindNextClicked();
    });

    // 输入框按Enter也触发查找
    connect(findEdit, &QLineEdit::returnPressed, this, [this]() {
        this->onFindNextClicked();
    });
}

void EditManager::createReplaceDialog()
{
    // 创建替换对话框
    replaceDialog = new QDialog(parentWindow);
    replaceDialog->setWindowTitle(tr("替换"));
    replaceDialog->setMinimumWidth(300);

    // 初始化控件
    auto *findLabel = new QLabel(tr("查找内容:"), replaceDialog);
    replaceFindEdit = new QLineEdit(replaceDialog);
    replaceFindEdit->setPlaceholderText(tr("输入要替换的文本..."));

    auto *replaceLabel = new QLabel(tr("替换为:"), replaceDialog);
    replaceWithEdit = new QLineEdit(replaceDialog);
    replaceWithEdit->setPlaceholderText(tr("输入替换后的文本..."));

    replaceBtn = new QPushButton(tr("全部替换"), replaceDialog);
    replaceBtn->setDefault(true);

    // 设置布局
    auto *layout = new QGridLayout(replaceDialog);
    layout->addWidget(findLabel, 0, 0, 1, 2);
    layout->addWidget(replaceFindEdit, 1, 0, 1, 2);
    layout->addWidget(replaceLabel, 2, 0, 1, 2);
    layout->addWidget(replaceWithEdit, 3, 0, 1, 2);
    layout->addWidget(replaceBtn, 4, 1);
    layout->setContentsMargins(15, 15, 15, 15);
    replaceDialog->setLayout(layout);

    // 绑定按钮点击事件 - 使用 lambda 表达式确保正确的连接
    connect(replaceBtn, &QPushButton::clicked, this, [this]() {
        this->onReplaceAllClicked();
    });

    // 输入框按Enter也触发替换
    connect(replaceWithEdit, &QLineEdit::returnPressed, this, [this]() {
        this->onReplaceAllClicked();
    });
}

void EditManager::undo()
{
    textEdit->undo();
    spdlog::debug("执行撤销操作");
}

void EditManager::redo()
{
    textEdit->redo();
    spdlog::debug("执行重做操作");
}

void EditManager::showFindDialog()
{
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
    spdlog::info("显示查找对话框");
}

void EditManager::showReplaceDialog()
{
    replaceDialog->show();
    replaceDialog->raise();
    replaceDialog->activateWindow();
    spdlog::info("显示替换对话框");
}

void EditManager::onFindNextClicked()
{
    QString text = findEdit->text().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(findDialog, tr("提示"), tr("请输入查找内容"));
        findEdit->setFocus();
        return;
    }
    findNext(text);
}

void EditManager::onReplaceAllClicked()
{
    QString findText = replaceFindEdit->text().trimmed();
    if (findText.isEmpty()) {
        QMessageBox::warning(replaceDialog, tr("提示"), tr("请输入要替换的内容"));
        replaceFindEdit->setFocus();
        return;
    }
    replaceAll(findText, replaceWithEdit->text());
}

void EditManager::findNext(const QString &text)
{
    QTextCursor cursor = textEdit->textCursor();
    bool found = textEdit->find(text);

    if (!found) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            parentWindow,
            tr("查找完成"),
            tr("已到达文档末尾。是否从开头重新查找？"),
            QMessageBox::Yes | QMessageBox::No
            );
        if (reply == QMessageBox::Yes) {
            textEdit->moveCursor(QTextCursor::Start);
            if (!textEdit->find(text)) {
                QMessageBox::information(
                    parentWindow,
                    tr("查找"),
                    tr("未找到\"%1\"").arg(text)
                    );
            }
        }
    } else {
        spdlog::debug("找到内容: {}", text.toStdString());
    }
}

void EditManager::replaceAll(const QString &from, const QString &to)
{
    QString text = textEdit->toPlainText();
    int count = text.count(from);

    if (count == 0) {
        QMessageBox::information(
            parentWindow,
            tr("替换"),
            tr("未找到\"%1\"").arg(from)
            );
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        parentWindow,
        tr("确认替换"),
        tr("是否将所有 %1 处\"%2\"替换为\"%3\"？")
            .arg(count).arg(from).arg(to),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        text.replace(from, to);
        textEdit->setPlainText(text);
        textEdit->document()->setModified(true);

        spdlog::info(
            "已替换 {} 处\"{}\"为\"{}\"",
            count, from.toStdString(), to.toStdString()
            );
        QMessageBox::information(
            parentWindow,
            tr("替换完成"),
            tr("已替换 %1 处").arg(count)
            );
    }
}
