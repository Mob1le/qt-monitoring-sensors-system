#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupThread();
    setWindowTitle("СИСТЕМА МОНИТОРИНГА 10000 ДАТЧИКОВ");
    resize(800, 600);
}

MainWindow::~MainWindow() {
    QMetaObject::invokeMethod(m_generator, "stopGeneration", Qt::QueuedConnection);
    m_workerThread->quit();
    m_workerThread->wait(5000);
}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Кнопки
    QHBoxLayout *btnLayout = new QHBoxLayout();
    m_startButton = new QPushButton("Старт", this);
    m_stopButton = new QPushButton("Стоп", this);
    m_filterCheckBox = new QCheckBox("Фильтрация (> 50)", this);
    m_stopButton->setEnabled(false);
    
    btnLayout->addWidget(m_startButton);
    btnLayout->addWidget(m_stopButton);
    btnLayout->addWidget(m_filterCheckBox);
    btnLayout->addStretch();
    mainLayout->addLayout(btnLayout);

    // Статистика
    QGroupBox *statsGroup = new QGroupBox("Статистика системы", this);
    QFormLayout *statsLayout = new QFormLayout(statsGroup);
    
    m_totalLabel = new QLabel("0", this);
    m_avgLabel = new QLabel("0.000", this);
    m_minLabel = new QLabel("0.000", this);
    m_maxLabel = new QLabel("0.000", this);
    
    statsLayout->addRow("Активных датчиков:", m_totalLabel);
    statsLayout->addRow("Среднее значение:", m_avgLabel);
    statsLayout->addRow("Минимальное значение:", m_minLabel);
    statsLayout->addRow("Максимальное значение:", m_maxLabel);
    
    mainLayout->addWidget(statsGroup);

    // Таблица
    m_tableView = new QTableView(this);
    m_model = new DetectorTableModel(this);

    proxyModel = new DetectorsProxyModel(this);

    proxyModel->setSourceModel(m_model);
    proxyModel->setDynamicSortFilter(true);  // Автоматическая пересортировка при изменении данных
    
    // Устанавливаем прокси-модель в таблицу
    m_tableView->setModel(proxyModel);
    m_tableView->setAlternatingRowColors(true);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_tableView->verticalHeader()->setVisible(false);
    m_tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_tableView->setSortingEnabled(true);
    
    mainLayout->addWidget(m_tableView);

    setCentralWidget(central);

    connect(m_startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(m_stopButton, &QPushButton::clicked, this, &MainWindow::onStopClicked);
    connect(m_model, &DetectorTableModel::dataChanged, this, &MainWindow::updateStatistics);
    connect(m_filterCheckBox, &QCheckBox::toggled, this, &MainWindow::onFilterChanged);
}

void MainWindow::setupThread() {
    m_workerThread = new QThread(this);
    m_generator = new DetectorDataGenerator();
    m_generator->moveToThread(m_workerThread);

    connect(m_generator, &DetectorDataGenerator::detectorsInitialized,
            this, &MainWindow::onDetectorsInitialized, Qt::QueuedConnection);
    connect(m_generator, &DetectorDataGenerator::valuesUpdated,
            this, &MainWindow::onValuesUpdated, Qt::QueuedConnection);
    connect(m_workerThread, &QThread::finished,
            m_generator, &QObject::deleteLater);

    m_workerThread->start();
}

void MainWindow::onStartClicked() {
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
    
    m_model->clearData();
    
    // Запускаем генерацию
    QMetaObject::invokeMethod(m_generator, "startGeneration",
                             Qt::QueuedConnection,
                             Q_ARG(int, 10000),   // количество датчиков
                             Q_ARG(int, 250));     // интервал обновления в мс
}

void MainWindow::onStopClicked() {
    m_stopButton->setEnabled(false);
    QMetaObject::invokeMethod(m_generator, "stopGeneration", Qt::QueuedConnection);
    m_startButton->setEnabled(true);
}

void MainWindow::onDetectorsInitialized(int count) {
    m_model->initDetectors(count);
}

void MainWindow::onValuesUpdated(const QVector<float> &newValues) {
    m_model->updateValues(newValues);
}

void MainWindow::updateStatistics() {
    m_totalLabel->setText(QString::number(m_model->totalCount()));
    m_avgLabel->setText(QString::number(m_model->averageValue(), 'f', 3));
    m_minLabel->setText(QString::number(m_model->minValue(), 'f', 3));
    m_maxLabel->setText(QString::number(m_model->maxValue(), 'f', 3));
}

void MainWindow::onFilterChanged()
{
    proxyModel->enableFiltration(m_filterCheckBox->isChecked());   
}