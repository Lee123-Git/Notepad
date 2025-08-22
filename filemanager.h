#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>

class QTextEdit;
class QMainWindow;

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QTextEdit *textEdit, QMainWindow *parent = nullptr);

    bool maybeSave();
    void newFile();
    void openFile();
    bool saveFile();
    void exitApp();

    QString getCurrentFile() const { return currentFile; }
    void setCurrentFile(const QString &file) { currentFile = file; }

signals:
    void windowTitleChanged(const QString &title);
    void documentModified(bool modified);

private:
    QTextEdit *textEdit;
    QMainWindow *parentWindow;
    QString currentFile;
};

#endif // FILEMANAGER_H
