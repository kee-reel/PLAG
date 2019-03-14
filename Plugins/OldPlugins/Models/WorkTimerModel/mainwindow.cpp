#include "mainwindow.h"
#include "sessiondata.h"
#include "ui_mainwindow.h"

#include <QJsonSerializer>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReadStatsFromFile();
    SetupTiming();
    SetupNotification();
    pomodoroState = PomodoroState::Lesure;
}

MainWindow::~MainWindow()
{
    workTimer.stop();
    SaveStatsToFile();
    delete ui;
}

void MainWindow::ReadStatsFromFile()
{
    statsFile.setFileName("PomodoroStats.txt");

    if (statsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto str = statsFile.readAll();
        QJsonParseError err;
        QJsonDocument statsJsonDoc = QJsonDocument::fromJson(str, &err);

        if(err.error == QJsonParseError::NoError)
        {
            QJsonArray statsJsonArr = statsJsonDoc.array();
            auto serializer = new QJsonSerializer(this);

            try
            {
                foreach(auto jsonData, statsJsonArr)
                {
                    SessionData data = serializer->deserialize<SessionData>(jsonData.toObject());
                    sessionDataList.append(data);
                }
            }
            catch(QJsonSerializerException &e)
            {
                qDebug() << e.what();
            }

            int secsWorked = 0;

            foreach (auto data, sessionDataList)
            {
                auto time = data.timeSessionStart.msecsSinceStartOfDay() / 1000;
                ui->chartWidget->AddPoint(time,
                                          secsWorked);
                secsWorked += data.sessionLenghtSecs;
                ui->chartWidget->AddPoint(time + data.sessionLenghtSecs,
                                          secsWorked);
            }

            timeWorkedToday = QTime(0, 0, 0);
            timeWorkedToday = timeWorkedToday.addSecs(secsWorked);
            ui->lcdWorkedToday->display(timeWorkedToday.toString("hh:mm:ss"));
        }
        else
        {
            qDebug() << err.errorString();
        }
    }

    statsFile.close();
}

void MainWindow::SetupNotification()
{
    username = "Kirill";
    notification.setIcon(QIcon("://rsc/pomodoro.png"));
    notification.show();
}

void MainWindow::UpdateWorkEveryHour()
{
    QTime curTime = QTime::currentTime();
    int msecsLeftToDayEnd = curTime.msecsTo(timeEndOfTheDay);
    float msecsNeedToWorkEveryHour = (float) timeNeedToWorkToday.msecsSinceStartOfDay() / msecsLeftToDayEnd;
    QString displayString;

    // Need to work
    if(msecsNeedToWorkEveryHour <= 1.0f)
    {
        msecsNeedToWorkEveryHour *= 60 * 60;
        QTime timeNeedToWorkEveryHour = QTime(0, 0, 0).addSecs((int)msecsNeedToWorkEveryHour);
        displayString = timeNeedToWorkEveryHour.toString("hh:mm:ss");
    }
    else
    {
        displayString = "01:00:00";
        msecsNeedToWorkEveryHour -= (int)msecsNeedToWorkEveryHour;
        msecsNeedToWorkEveryHour *= 60 * 60;
    }

    ui->lcdWorkEveryHour->display(displayString);
}

void MainWindow::SetupTiming()
{
    timeEndOfTheDay = ui->timeWorkDayEnd->time();
    timeNeedToWorkToday = ui->timeNeedToWork->time();
    timeWorkLeft = timeNeedToWorkToday.addMSecs(-timeWorkedToday.msecsSinceStartOfDay());
    ui->chartWidget->SetAxisRange(DataChartWidget::AxisY, 0, timeNeedToWorkToday.msecsSinceStartOfDay() / 1000);
    ui->lcdWorkedToday->display(timeWorkedToday.toString("hh:mm:ss"));
    ui->lcdWorkLeft->display(timeWorkLeft.toString("hh:mm:ss"));
    connect(&workTimer, &QTimer::timeout, this, [=]()
    {
        timeWorkedToday = timeWorkedToday.addSecs(1);
        timeNeedToWorkToday = ui->timeNeedToWork->time();
        timeWorkLeft = timeNeedToWorkToday.addMSecs(-timeWorkedToday.msecsSinceStartOfDay());
        ui->lcdWorkedToday->display(timeWorkedToday.toString("hh:mm:ss"));
        ui->lcdWorkLeft->display(timeWorkLeft.toString("hh:mm:ss"));

        if(timeWorkedToday == timeNeedToWorkToday)
        {
            ShowMessage("hey! You've completed plan for today and can have a full rest!");
        }

        auto time = QTime::currentTime().msecsSinceStartOfDay() / 1000;
        ui->chartWidget->AddPoint(time, timeWorkedToday.msecsSinceStartOfDay() / 1000);
    });
    connect(&timeNeedToWorkTimer, &QTimer::timeout, this, [=]()
    {
        UpdateWorkEveryHour();
    });
    workTimer.setSingleShot(false);
    timeNeedToWorkTimer.setSingleShot(false);
    timeNeedToWorkTimer.start(1000);
}

void MainWindow::SaveStatsToFile()
{
    if (statsFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&statsFile);

        try
        {
            auto serializer = new QJsonSerializer(this);
            QJsonArray statsJsonArr;

            try
            {
                foreach(auto statsData, sessionDataList)
                {
                    QJsonObject json = serializer->serialize(statsData);
                    statsJsonArr.append(json);
                }
            }
            catch(QJsonSerializerException &e)
            {
                qDebug() << e.what();
            }

            out << QJsonDocument(statsJsonArr).toJson();
        }
        catch(QJsonSerializerException &e)
        {
            qDebug() << e.what();
        }
    }

    statsFile.close();
}

void MainWindow::UpdateStats()
{
    SessionData object;
    object.sessionType = SessionData::Work;
    object.timeSessionStart = timeWorkStarted;
    object.sessionLenghtSecs = timeWorkStarted.msecsTo(QTime::currentTime()) / 1000;
    sessionDataList.append(object);
}
void MainWindow::ShowMessage(QString message)
{
    notification.showMessage("Pomodoro timer", QString("%1, %2").arg(username).arg(message));
}

void MainWindow::StartWorkTimer()
{
    workTimer.start(1000);
}

void MainWindow::StopWorkTimer()
{
    workTimer.stop();
}

void MainWindow::NextPomodoroState()
{
    switch (pomodoroState)
    {
        case MainWindow::Lesure:
            pomodoroState = Working;
            StartWorkTimer();
            timeWorkStarted = QTime::currentTime();
            ShowMessage("let's get things done!");
            ui->pushButton->setText("Pause work");
            break;

        case MainWindow::Working:
            pomodoroState = Lesure;
            StopWorkTimer();
            UpdateStats();
            ShowMessage(QString("%1 of work time left.").arg(timeNeedToWorkToday.toString("hh:mm")));
            ui->pushButton->setText("Resume work");
            break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    NextPomodoroState();
}
QString MainWindow::GetCurrentTimeString()
{
    return QDateTime::currentDateTime().toString("HH:mm:ss dd:MM:yyyy");
}

void MainWindow::on_timeNeedToWork_userTimeChanged(const QTime &time)
{
    timeNeedToWorkToday = time;
    timeWorkLeft = timeNeedToWorkToday.addMSecs(-timeWorkedToday.msecsSinceStartOfDay());
    ui->lcdWorkLeft->display(timeWorkLeft.toString("hh:mm:ss"));
    UpdateWorkEveryHour();
    ui->chartWidget->SetAxisRange(DataChartWidget::AxisY, 0, timeNeedToWorkToday.msecsSinceStartOfDay() / 1000);
}

void MainWindow::on_timeWorkDayEnd_userTimeChanged(const QTime &time)
{
    timeEndOfTheDay = time;
    UpdateWorkEveryHour();
}
