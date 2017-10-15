#ifndef MENUITEM_H
#define MENUITEM_H

#include <QPushButton>
#include <QResizeEvent>

class MenuItem : public QPushButton
{
    Q_OBJECT
public:
    explicit MenuItem(int id, QString name, QWidget *parent = 0);

private:
    int id;

signals:
    void OnMenuItemSelected(int id);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
//    void resizeEvent(QResizeEvent *event) override;
};

#endif // MENUITEM_H
