#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sessiondata.h"

#include <QDateTime>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

private slots:
    void on_pushButton_clicked();
    void on_timeNeedToWork_userTimeChanged(const QTime &time);

    void on_timeWorkDayEnd_userTimeChanged(const QTime &time);

private:
    Ui::MainWindow *ui;

    // Notification.
    QString username;
    QSystemTrayIcon notification;

    // Stats.
    QFile statsFile;
    QList<SessionData> sessionDataList;

    enum PomodoroState
    {
        Lesure,
        Working,
    } pomodoroState;

    // Time.
    QTimer workTimer;
    QTimer timeNeedToWorkTimer;
    QTime timeWorkStarted;
    QTime timeWorkedToday;
    QTime timeWorkLeft;
    QTime timeNeedToWorkToday;
    QTime timeEndOfTheDay;

    QString GetCurrentTimeString();

    void UpdateStats();
    void ShowMessage(QString message);
    void StartWorkTimer();
    void StopWorkTimer();
    void ReadStatsFromFile();
    void SetupNotification();
    void SetupTiming();
    void NextPomodoroState();
    void UpdateWorkEveryHour();
    void SaveStatsToFile();
};

#endif // MAINWINDOW_H
