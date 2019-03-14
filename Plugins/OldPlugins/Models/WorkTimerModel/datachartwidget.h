#ifndef DATACHARTWIDGET_H
#define DATACHARTWIDGET_H

#include <QtCharts>
#include <QtCore>

class DataChartWidget : public QChartView
{
    Q_OBJECT
public:
    explicit DataChartWidget(QWidget *parent = nullptr);

    enum AxisType
    {
        AxisX,
        AxisY,
    };

signals:

public slots:
    void AddPoint(float x, float y);
    void ClearChart();
    void SetAxisRange(AxisType type, float min, float max);

private:
    QChart chart;
    QLineSeries currentSeries;
    QPair<float, float> xConstr;
    QPair<float, float> yConstr;

    void UpdateChartConstraints(QPair<float, float> &constr, float value);
    void NormalizeAxis(QPair<float, float> &axisConstr);
};

#endif // DATACHARTWIDGET_H
