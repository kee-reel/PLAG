#include "datachartwidget.h"

DataChartWidget::DataChartWidget(QWidget *parent) : QChartView(parent)
{
    chart.addSeries(&currentSeries);
    chart.createDefaultAxes();
    xConstr = QPair<float, float>(0, 24 * 60 * 60);
    yConstr = QPair<float, float>(0, 8 * 60 * 60);
    chart.axisX()->setRange(xConstr.first, xConstr.second);
    chart.axisY()->setRange(yConstr.first, yConstr.second);
    QChartView::setChart(&chart);
    chart.legend()->hide();
}

void DataChartWidget::AddPoint(float x, float y)
{
    currentSeries.append(x, y);
}

void DataChartWidget::ClearChart()
{
    currentSeries.clear();
}

void DataChartWidget::SetAxisRange(DataChartWidget::AxisType type, float min, float max)
{
    switch (type)
    {
        case DataChartWidget::AxisX:
            chart.axisX()->setRange(min, max);
            break;

        case DataChartWidget::AxisY:
            chart.axisY()->setRange(min, max);
            break;
    }
}

void DataChartWidget::UpdateChartConstraints(QPair<float, float> &constr, float value)
{
    constr.first = (constr.first > value) ? value : constr.first;
    constr.second = (constr.second < value) ? value : constr.second;
}

void DataChartWidget::NormalizeAxis(QPair<float, float> &axisConstr)
{
    qDebug() << axisConstr;

    if(fabs(axisConstr.second - axisConstr.first) < 0.001)
    {
        axisConstr.first -= 0.5;
        axisConstr.second += 0.5;
    }

    if(axisConstr.first >= 0)
    {
        axisConstr.first = 0;
    }
    else if(axisConstr.second <= 0)
    {
        axisConstr.second = 0;
    }
    else
    {
        auto absFirst = fabsf(axisConstr.first);
        auto absSecond = fabsf(axisConstr.second);
        auto buf = absFirst > absSecond ? absFirst : absSecond;
        axisConstr.first = -buf;
        axisConstr.second = buf;
    }
}
