#include "pomodorobutton.h"

PomodoroButton::PomodoroButton(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "========================Init";
    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->setTimerType(Qt::VeryCoarseTimer);
    connect(timer, SIGNAL(timeout()), SLOT(TimerTick()));
<<<<<<< HEAD
    secsTarget = secsPassed = 25 * 60;
=======
    secsTarget = 35 * 60;
>>>>>>> a2445897c806490964d364d39f2b23b415a47371
}

PomodoroButton::~PomodoroButton()
{
    delete timer;
}

void PomodoroButton::PlayAudio()
{
    sourceFile.setFileName(":/Res/alert.raw");
    sourceFile.open(QIODevice::ReadOnly);

    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    qDebug() << info.supportedCodecs();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    audio = new QAudioOutput(format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    audio->start(&sourceFile);
}

void PomodoroButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Press";
    if(!timer->isActive())
    {
        secsPassed = 0;
        repaint();
        timer->start();
    }
    else
    {
        timer->stop();
    }
}

void PomodoroButton::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing);
    QBrush brush(Qt::black);
    QPen pen(brush, 3);
    p.setBrush(brush);
    p.setPen(pen);

    QRect circleRect;
    bool isVertiacal = width() < height();
    float circleScale = 0.75;
    float size = (isVertiacal ? width() : height()) * circleScale;

    circleRect.setX(width()/2 - size/2);
    circleRect.setY(height()/2 - size/2);
    circleRect.setWidth(size);
    circleRect.setHeight(size);

    int angle = 360 * (secsPassed / (float)secsTarget) * 16;

    int startAngle = 90 * 16;
    p.drawPie(circleRect, startAngle, -angle);

    p.end();
}

void PomodoroButton::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::IdleState:
            qDebug() << "Finished playing (no more data)";
            audio->stop();
            sourceFile.close();
            delete audio;
            break;

        case QAudio::StoppedState:
            qDebug() << "Stopped for other reasons";
            if (audio->error() != QAudio::NoError) {
                qDebug() << "Error:" << audio->error();
            }
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}

void PomodoroButton::TimerTick()
{
    secsPassed++;
    repaint();
    if(secsPassed >= secsTarget)
    {
        timer->stop();
        repaint();
        PlayAudio();
        emit PomodoroFinished();
    }
}
