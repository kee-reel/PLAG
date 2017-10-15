#include "parentwindow.h"

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
    JNINativeMethod methods[] {
        { "OnAndroidAlarmRecieved", // const char* function name;
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

ParentWindow::ParentWindow(QWidget *parent) : QWidget(parent)
{
#ifdef Q_OS_ANDROID
    RegisterNativeMethods();
#endif

//    childsJoint = new QWidget(this);
    layout = new QVBoxLayout();
    this->setLayout(layout);
    setWindowIcon(QIcon("://Resources/Logo512.png"));
    // Headless window mode
//    Qt::WindowFlags flags = windowFlags();
//    flags |= Qt::FramelessWindowHint;
//    setWindowFlags(flags);

    pluginManager = new PluginLoader(this);
#ifdef Q_OS_ANDROID
    QScreen *screen = QApplication::primaryScreen();
    this->resize(screen->size().width(),
        screen->size().height());
#else
    QScreen *screen = QApplication::primaryScreen();
    this->resize(screen->size().width()/3,
        screen->size().height()/2);
#endif
    pluginManager->SetupPlugins();
}

ParentWindow::~ParentWindow()
{
    delete pluginManager;
    //delete childsJoint;
    delete layout;
}

void ParentWindow::resizeEvent(QResizeEvent *event)
{
    layout->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
}

////void SetFibonacciResult(JNIEnv *, jobject, jint n)
////{
////    qDebug() << "SUCCESS!!!!!!";
////}

//// step 2
//// create a vector with all our JNINativeMethod(s)
//static JNINativeMethod methods[] = {
//    { "SetFibonacciResult", // const char* function name;
//        "(I)V", // const char* function signature
//        (void *)SetFibonacciResult // function pointer
//    }
//};

//// step 1
//// this method is called automatically by Java VM
//// after the .so file is loaded
//JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
//{
//    JNIEnv* env;
//    qDebug() << "~1" << vm;

//    // get the JNIEnv pointer.
//    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6)
//           != JNI_OK) {
//        return JNI_ERR;
//    }
//    qDebug() << "~2";
//    // step 3
//    // search for Java class which declares the native methods
//    jclass javaClass = env->FindClass("com/mass/mainapp/QtActivityExtention");
//    if (!javaClass)
//        return JNI_ERR;
//    qDebug() << "~3" << javaClass;
//    // step 4
//    // register our native methods
//    if (env->RegisterNatives(javaClass, methods,
//                            sizeof(methods) / sizeof(methods[0])) < 0) {
//        return JNI_ERR;
//    }
//    qDebug() << "~4";
//    return JNI_VERSION_1_6;
//}
