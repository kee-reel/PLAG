#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QImage>
#include <QPicture>
#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QBuffer>

//! \addtogroup TaskSketchView_imp
//! \{
class PaintWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue)

public:
    explicit PaintWidget(QWidget *parent = nullptr);
    virtual ~PaintWidget() override;
    QVariant value() const;
    void setValue(const QVariant value);
private:
    QImage image;
    bool isPressed;
    bool isDefaultCanvasChanged;
    QPoint mousePos, prevMousePos;
    QPen pen;

public slots:
    void Clean();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

};
//! \}
#endif // PAINTWIDGET_H
