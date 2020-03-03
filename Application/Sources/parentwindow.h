#pragma once


#include <QWidget>
#include <QScreen>
#include <QPainter>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QLabel>

class PluginLoader;

//! \brief Main application widget class.
class ParentWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ParentWindow(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent* event) override;

public:
    void start();

private:
    void init();

private Q_SLOTS:
	void onReadyToStart();
	void onStartFailed();

private:
    QSharedPointer<PluginLoader> m_pluginManager;
    QVBoxLayout *layout{nullptr};
};

