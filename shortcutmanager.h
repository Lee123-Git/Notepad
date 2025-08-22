#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H

#include <QObject>
#include <QShortcut>
#include <QWidget>
#include <functional>

class ShortcutManager : public QObject
{
    Q_OBJECT
public:
    explicit ShortcutManager(QWidget *parent,
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
                             std::function<void()> decreaseFontSizeFunc);

    ~ShortcutManager() override;

private:
    QList<QShortcut*> shortcuts;
};

#endif // SHORTCUTMANAGER_H
