#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QObject>

class QTextEdit;
class QMainWindow;

class FontManager : public QObject
{
    Q_OBJECT
public:
    explicit FontManager(QTextEdit *textEdit, QMainWindow *parent = nullptr);

    void setFont();
    void setFontSize();
    void increaseFontSize();
    void decreaseFontSize();

    int getCurrentFontSize() const { return currentFontSize; }

private:
    void updateFontSize();

    QTextEdit *textEdit;
    QMainWindow *parentWindow;
    int currentFontSize;
};

#endif // FONTMANAGER_H
