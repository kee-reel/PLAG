#include "qextendedtimer.h"

QExtendedTimer::QExtendedTimer(QObject *parent) : QTimer(parent)
{
    connect(this, SIGNAL(timeout()), SLOT(OnTimeout()));
}

void QExtendedTimer::OnTimeout()
{
    emit timeout(this);
}
