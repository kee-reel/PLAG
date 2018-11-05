#ifndef MENUITEM_H
#define MENUITEM_H

#include <QPushButton>
#include <QResizeEvent>

class UniquePushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit UniquePushButton(int m_id, QString name, QWidget *parent = nullptr);

    int getId();

private:
    int m_id;

signals:
    void OnMenuItemSelected(UniquePushButton *);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    //    void resizeEvent(QResizeEvent *event) override;
};

#endif // MENUITEM_H
