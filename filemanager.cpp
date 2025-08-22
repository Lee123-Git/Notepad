#include "FileManager.h"
#include <QTextEdit>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <spdlog/spdlog.h>

FileManager::FileManager(QTextEdit *textEdit, QMainWindow *parent)
    : QObject(parent), textEdit(textEdit), parentWindow(parent)
{
}

bool FileManager::maybeSave()
{
    if (textEdit->document()->isModified()) {
        spdlog::debug("检测到未保存的更改");
        auto ret = QMessageBox::warning(
            parentWindow,
            tr("保存文档"),
            tr("文档尚未保存。是否要保存它？"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
            );

        if (ret == QMessageBox::Save) {
            spdlog::info("用户选择保存文件");
            return saveFile();
        } else if (ret == QMessageBox::Discard) {
            spdlog::info("用户选择放弃更改");
            return true;
        } else {
            spdlog::info("用户取消操作");
            return false;
        }
    }
    return true;
}

void FileManager::newFile()
{
    spdlog::info("用户触发新建文件操作");

    if (!maybeSave()) {
        spdlog::warn("新建文件操作取消");
        return;
    }

    textEdit->clear();
    currentFile.clear();
    emit windowTitleChanged(tr("记事本"));
    spdlog::info("创建新的空白文档");
}

void FileManager::openFile()
{
    spdlog::info("用户触发打开文件操作");

    if (!maybeSave()) {
        spdlog::warn("打开文件操作取消（存在未保存内容）");
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(
        parentWindow,
        tr("打开文件"),
        QDir::homePath(),
        tr("文本文件 (*.txt);;所有文件 (*)")
        );

    if (fileName.isEmpty()) {
        spdlog::info("用户取消文件选择");
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString error = file.errorString();
        spdlog::error(
            "打开文件失败: {} (错误: {})",
            fileName.toStdString(),
            error.toStdString()
            );
        QMessageBox::warning(
            parentWindow,
            tr("错误"),
            tr("无法打开文件:\n%1\n错误: %2").arg(fileName).arg(error)
            );
        return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();

    currentFile = fileName;
    emit windowTitleChanged(QFileInfo(fileName).fileName());
    textEdit->document()->setModified(false);
    spdlog::info("成功打开文件: {}", fileName.toStdString());
}

bool FileManager::saveFile()
{
    if (currentFile.isEmpty()) {
        spdlog::debug("执行另存为操作");
        QString fileName = QFileDialog::getSaveFileName(
            parentWindow,
            tr("保存文件"),
            QDir::homePath(),
            tr("文本文件 (*.txt);;所有文件 (*)")
            );

        if (fileName.isEmpty()) {
            spdlog::info("用户取消保存操作");
            return false;
        }
        currentFile = fileName;
    }

    QFile file(currentFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString error = file.errorString();
        spdlog::error(
            "保存文件失败: {} (错误: {})",
            currentFile.toStdString(),
            error.toStdString()
            );
        QMessageBox::warning(
            parentWindow,
            tr("错误"),
            tr("无法保存文件:\n%1\n错误: %2").arg(currentFile).arg(error)
            );
        return false;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();

    textEdit->document()->setModified(false);
    emit windowTitleChanged(QFileInfo(currentFile).fileName());
    spdlog::info("文件保存成功: {}", currentFile.toStdString());
    return true;
}

void FileManager::exitApp()
{
    spdlog::info("用户触发退出操作");
    parentWindow->close();
}
