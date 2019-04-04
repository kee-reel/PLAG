#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QtCore>

struct SessionData
{
    Q_GADGET

    Q_PROPERTY(QTime TimeSessionStart MEMBER timeSessionStart)
    Q_PROPERTY(int SessionLenghtSecs MEMBER sessionLenghtSecs)
    Q_PROPERTY(QString SessionType READ getSessionType WRITE setSessionType)

public:
    SessionData();
    QString getSessionType() const;
    void setSessionType(const QString &value);

    enum Type
    {
        Work,
        Lesure,
    };

    Type sessionType;
    QTime timeSessionStart;
    int sessionLenghtSecs;
};

#endif // SESSIONDATA_H
