#ifndef EDITMANAGER_H
#define EDITMANAGER_H

#include <QObject>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class QTextEdit;
class QMainWindow;

class EditManager : public QObject
{
    Q_OBJECT
public:
    explicit EditManager(QTextEdit *textEdit, QMainWindow *parent = nullptr);
    ~EditManager();

    void undo();
    void redo();
    void showFindDialog();
    void showReplaceDialog();

private slots:
    void onFindNextClicked();
    void onReplaceAllClicked();

private:
    void findNext(const QString &text);
    void replaceAll(const QString &from, const QString &to);

    QTextEdit *textEdit;
    QMainWindow *parentWindow;

    // 查找对话框相关
    QDialog *findDialog;
    QLineEdit *findEdit;
    QPushButton *findBtn;

    // 替换对话框相关
    QDialog *replaceDialog;
    QLineEdit *replaceFindEdit;
    QLineEdit *replaceWithEdit;
    QPushButton *replaceBtn;

    void createFindDialog();
    void createReplaceDialog();
};

#endif // EDITMANAGER_H
