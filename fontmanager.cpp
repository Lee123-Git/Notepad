#include "FontManager.h"
#include <QTextEdit>
#include <QMainWindow>
#include <QFontDialog>
#include <QInputDialog>
#include <QStatusBar>
#include <spdlog/spdlog.h>

FontManager::FontManager(QTextEdit *textEdit, QMainWindow *parent)
    : QObject(parent),
    textEdit(textEdit),
    parentWindow(parent),
    currentFontSize(12)
{
    updateFontSize();
}

void FontManager::setFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(
        &ok,
        textEdit->font(),
        parentWindow
        );
    if (ok) {
        textEdit->setFont(font);
        spdlog::info(
            "字体已更改: {}",
            font.toString().toStdString()
            );
    } else {
        spdlog::info("用户取消字体选择");
    }
}

void FontManager::setFontSize()
{
    int currentSize = textEdit->currentFont().pointSize();

    bool ok;
    int newSize = QInputDialog::getInt(
        parentWindow,
        tr("设置字体大小"),
        tr("请输入字体大小(6-72):"),
        currentSize,
        6,
        72,
        1,
        &ok
        );

    if (ok) {
        QFont font = textEdit->currentFont();
        font.setPointSize(newSize);
        textEdit->setFont(font);
        spdlog::info("字体大小已设置为: {}pt", newSize);
    }
}

void FontManager::increaseFontSize()
{
    currentFontSize += 2;

    if (currentFontSize > 72) {
        currentFontSize = 72;
    }

    updateFontSize();
}

void FontManager::decreaseFontSize()
{
    currentFontSize -= 2;

    if (currentFontSize < 6) {
        currentFontSize = 6;
    }

    updateFontSize();
}

void FontManager::updateFontSize()
{
    QFont font = textEdit->font();
    font.setPointSize(currentFontSize);
    textEdit->setFont(font);

    parentWindow->statusBar()->showMessage(tr("The size of font: %1").arg(currentFontSize), 2000);
}
