#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
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
    controlsLayout->addStretch(); // чтобы кнопки слева, статистика справа

    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(table_view);

    connect(start_stop_button, &QPushButton::clicked,
            this, &MainWindow::onStartStopClicked);

    setMinimumSize(800, 600);
}

MainWindow::~MainWindow() {}


void MainWindow::onStartStopClicked()
{
    if (start_stop_button->isChecked()) {
        start_stop_button->setText("Стоп");
        // тут будет вызов generator->start()
        // statisticsCalculator->start();
    } else {
        start_stop_button->setText("Старт");
        // generator->stop()
        // statisticsCalculator->stop()
    }
}
