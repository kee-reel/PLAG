#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::AddNewButton(int id, QString task)
{
    DraggableButton* moduleButton = new DraggableButton(this, id, task);
    QSize parentSize = parentWidget()->size();
    int size = parentSize.width() < parentSize.height() ? parentSize.width() : parentSize.height();
    size /= 5;
    moduleButton->setGeometry(0, 0, size, size);
    modulesButtons.append(moduleButton);
    connect(moduleButton, SIGNAL(OnClicked(int)), this, SIGNAL(OnButtonPressed(int)));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing);

    QFont m_font;
    m_font.setBold(true);
    p.setFont(QFont("Corbel", width()/20));
    p.drawText(rect(), Qt::AlignCenter, "Multiple\nApplication\nSupport\nSystem");

    p.end();
}

void MainWindow::WipeAllButtons()
{
    for(int i = 0; i < modulesButtons.count(); i++)
    {
        disconnect(modulesButtons[i], SIGNAL(OnClicked(int)), this, SIGNAL(OnButtonPressed(int)));
        delete modulesButtons[i];
    }
    modulesButtons.clear();
}
