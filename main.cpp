#include <QtWidgets/QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QTimer>
#include <cmath>
#include <QStyle>

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);
    
    QSplineSeries *series1 = new QSplineSeries();
    series1->setName("sin(x)");
    QSplineSeries *series2 = new QSplineSeries();
    series2->setName("cos(x)");
    QSplineSeries *series3 = new QSplineSeries();
    series3->setName("3cos(3x)sin(x)^2");
    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->createDefaultAxes();
    chart->setTitle("Динамическое обновление графика");
    
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        static qreal x = 0;
        x += 0.02;
        series1->append(x, std::sin(x));
        series2->append(x, std::cos(x));
        series3->append(x, std::cos(3*x)*sin(x)*sin(x)*3);
        
        if(x > 12){
            series1->remove(0);
            series2->remove(0);
            series3->remove(0);
        }
        
        chart->axes(Qt::Horizontal).first()->setRange(x - 12, x+0.1);
        chart->axes(Qt::Vertical).first()->setRange(-3, 3);
        
    });
    timer->start(10);
    
    chartView->resize(1000, 1000);
    chartView->setBackgroundBrush(QBrush(QColor(30,30,30)));
    
    chart->setBackgroundBrush(QBrush(QColor(30,30,30)));
    chart->setTitleBrush(QBrush(QColor(255,255,255)));
    
    chart->axes(Qt::Horizontal).first()->setLinePenColor(QColor(60,60,60));
    chart->axes(Qt::Horizontal).first()->setGridLineColor(QColor(60,60,60));
    chart->axes(Qt::Vertical).first()->setLinePenColor(QColor(60,60,60));
    chart->axes(Qt::Vertical).first()->setGridLineColor(QColor(60,60,60));
    
    chart->legend()->setLabelColor(QColor(255,255,255));
    
    chartView->show();
    
    /* 
     * same result
     * 
    QWidget win;
    chartView->setParent(&win);
    win.show();
    */ 
    
    return app.exec();
}
