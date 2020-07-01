#include "parentwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QApplication>

#include <QtAndroid>
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

void ParentWindow::init()
{
	RegisterNativeMethods();

	layout = new QVBoxLayout(this);
	QScreen *screen = QApplication::primaryScreen();
	this->resize(screen->size().width(), screen->size().height());
}
