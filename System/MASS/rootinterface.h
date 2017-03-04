#ifndef ROOTINTERFACES_H
#define ROOTINTERFACES_H

class QObject;
class QWidget;
class QJsonObject;

class IRootModelPlugin
{
public:
    virtual ~IRootModelPlugin() {}
    virtual void AddPlugin(QObject* instance, QJsonObject* meta) = 0;
    virtual void Open(QWidget* parentWidget) = 0;
};
Q_DECLARE_INTERFACE(IRootModelPlugin, "IRootModelPlugin v0.1")
#endif // ROOTINTERFACES_H
