#ifndef POMODOROBUTTON_H
#define POMODOROBUTTON_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QAudioOutput>

class PomodoroButton : public QWidget
{
    Q_OBJECT
public:
    explicit PomodoroButton(QWidget *parent = 0);
    virtual ~PomodoroButton();

    QTimer *timer;
    int secsPassed;
    int secsTarget;

private:
    QFile sourceFile;
    QAudioOutput* audio;

    void PlayAudio();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void TimerTick();
    void handleStateChanged(QAudio::State newState);

signals:
    void PomodoroFinished();
};

#endif // POMODOROBUTTON_H
