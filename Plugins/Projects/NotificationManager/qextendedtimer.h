#ifndef QTIMERWITHID_H
#define QTIMERWITHID_H

#include <QTimer>

class QExtendedTimer : public QTimer
{
    Q_OBJECT
public:
    explicit QExtendedTimer(QObject *parent = nullptr);

signals:
    void timeout(QExtendedTimer*);

private slots:
    void OnTimeout();
};

#endif // QTIMERWITHID_H
