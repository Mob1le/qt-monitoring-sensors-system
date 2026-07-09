#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    qRegisterMetaType<Detector>("Detector");
    data_model = new DetectorDataModel(this);

    sort_filter_model = new QSortFilterProxyModel(this);
    sort_filter_model->setSourceModel(data_model);

    table_view = new QTableView(this);
    table_view->setModel(sort_filter_model);
    table_view->setSortingEnabled(true);

    statistics_label = new QLabel("Датчиков: 0 | Ср. знач: 0.00 | Мин: 0.00 | Макс: 0.00", this); // ЗАГЛУШКА
    statistics_label->setFixedHeight(24);

    start_stop_button = new QPushButton("Старт", this);
    start_stop_button->setCheckable(true);
    start_stop_button->setFixedWidth(120);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *controlsLayout = new QHBoxLayout();

    controlsLayout->addWidget(start_stop_button);
    controlsLayout->addWidget(statistics_label);
    controlsLayout->addStretch();

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(table_view);

    

    detector_generator.moveToThread(&gen_thread);
    connect(&gen_thread, &QThread::started, &detector_generator, &DetectorGenerator::process);
    connect(&detector_generator, &DetectorGenerator::finished, &gen_thread, &QThread::quit);
    connect(&gen_thread, &QThread::finished, &gen_thread, &QObject::deleteLater);

    connect(start_stop_button, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(&detector_generator, &DetectorGenerator::sendDetector, data_model, &DetectorDataModel::addData, Qt::QueuedConnection);
    
    setMinimumSize(800, 600);
}

MainWindow::~MainWindow() 
{
    if (gen_thread.isRunning()) {
        detector_generator.setRunning(false);
        gen_thread.quit();                     // Запрос на выход из event loop
        gen_thread.wait();                     // Ждём завершения (безопасно)
    }
}

void MainWindow::onStartStopClicked()
{
    if (start_stop_button->isChecked())
    {
        start_stop_button->setText("Стоп");
        detector_generator.setRunning(true);
        gen_thread.start();
        // statisticsCalculator->start();
    }
    else
    {
        start_stop_button->setText("Старт");
        detector_generator.setRunning(false);
        // statisticsCalculator->stop()
    }
}
