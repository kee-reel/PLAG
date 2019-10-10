#include "parentwindow.h"

#include <QMessageBox>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QDebug>
#include <QAndroidJniEnvironment>

void OnAndroidAlarmRecieved(JNIEnv *, jobject)
{
    qDebug() << "Native function OnAndroidAlarmRecieved not implemented.";
}

void RegisterNativeMethods()
{
    qDebug() << "~Start";
    JNINativeMethod methods[]
    {
        {
            "OnAndroidAlarmRecieved", // const char* function name;
            "()V", // const char* function signature
            (void *)OnAndroidAlarmRecieved // function pointer
        }
    };
    QAndroidJniEnvironment env;
    qDebug() << "~JVM" << env.javaVM();
    QAndroidJniObject javaClass = QtAndroid::androidActivity();// ("my/java/project/FooJavaClass");
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    qDebug() << "~objectClass" << objectClass;

    if(env->ExceptionCheck())
    {
        qDebug() << "~Exception:";
        env->ExceptionClear();
        return;
    }

    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));

    if(env->ExceptionCheck())
    {
        qDebug() << "~Exception:";
        env->ExceptionClear();
        return;
    }

    env->DeleteLocalRef(objectClass);
}
#endif

ParentWindow::ParentWindow(QWidget *parent) :
    QWidget(parent),
    triesToCloseApp(0)
{
#ifdef Q_OS_ANDROID
    RegisterNativeMethods();
#endif
    setWindowIcon(QIcon("://Resources/Logo256.png"));
    m_pluginManager = QSharedPointer<PluginLoader>(new PluginLoader(this));
}

ParentWindow::~ParentWindow()
{
}

bool ParentWindow::Init()
{
    if(m_pluginManager->setupPlugins())
    {
        SetupWidget();
        m_pluginManager->runCorePlugin();
        return true;
    }
    else
    {
        return false;
    }
}

void ParentWindow::SetupWidget()
{
    layout = new QVBoxLayout(this);
    this->setLayout(layout);
#ifdef Q_OS_ANDROID
    QScreen *screen = QApplication::primaryScreen();
    this->resize(screen->size().width(),
                 screen->size().height());
#else
    QScreen *screen = QApplication::primaryScreen();
    this->resize(screen->size().width()/3,
                 screen->size().height()/2);
#endif
}

void ParentWindow::resizeEvent(QResizeEvent *event)
{
    layout->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
}

void ParentWindow::closeEvent(QCloseEvent *event)
{
    bool needToClose = m_pluginManager->closePlugins();

    if(!needToClose)
    {
        needToClose = ++triesToCloseApp >= MAX_TRIES_TO_CLOSE_APP;
    }

    if(needToClose)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
