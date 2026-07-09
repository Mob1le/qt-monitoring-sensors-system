// MainWindow.cpp
#include "main_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupThread();
    setWindowTitle("10000 Detectors Monitor");
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
    m_stopButton->setEnabled(false);
    
    m_startButton->setMinimumHeight(40);
    m_stopButton->setMinimumHeight(40);
    
    btnLayout->addWidget(m_startButton);
    btnLayout->addWidget(m_stopButton);
    btnLayout->addStretch();
    mainLayout->addLayout(btnLayout);

    // Статистика
    QGroupBox *statsGroup = new QGroupBox("Статистика системы", this);
    QFormLayout *statsLayout = new QFormLayout(statsGroup);
    
    m_totalLabel = new QLabel("0", this);
    m_avgLabel = new QLabel("0.000", this);
    m_minLabel = new QLabel("0.000", this);
    m_maxLabel = new QLabel("0.000", this);
    m_updateRateLabel = new QLabel("0 Hz", this);
    
    // Стилизация статистики
    QFont boldFont;
    boldFont.setBold(true);
    m_totalLabel->setFont(boldFont);
    m_avgLabel->setFont(boldFont);
    m_minLabel->setFont(boldFont);
    m_maxLabel->setFont(boldFont);
    m_updateRateLabel->setFont(boldFont);
    
    statsLayout->addRow("Активных датчиков:", m_totalLabel);
    statsLayout->addRow("Среднее значение:", m_avgLabel);
    statsLayout->addRow("Минимальное значение:", m_minLabel);
    statsLayout->addRow("Максимальное значение:", m_maxLabel);
    statsLayout->addRow("Частота обновления:", m_updateRateLabel);
    
    mainLayout->addWidget(statsGroup);

    // Таблица
    m_tableView = new QTableView(this);
    m_model = new DetectorTableModel(this);
    m_tableView->setModel(m_model);
    m_tableView->setAlternatingRowColors(true);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_tableView->verticalHeader()->setVisible(false);  // Скрываем номера строк
    
    // Оптимизация для большого количества строк
    m_tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    
    mainLayout->addWidget(m_tableView);

    setCentralWidget(central);

    connect(m_startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(m_stopButton, &QPushButton::clicked, this, &MainWindow::onStopClicked);
    connect(m_model, &DetectorTableModel::dataChanged, this, &MainWindow::updateStatistics);
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
    
    // Очищаем старые данные
    m_model->clearData();
    
    // Сбрасываем счетчик FPS
    m_updateCounter = 0;
    m_fpsTimer.start();
    
    // Запускаем генерацию 10000 датчиков с обновлением каждые 50 мс
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
    setWindowTitle(QString("10000 Detectors Monitor - Initialized %1 detectors").arg(count));
}

void MainWindow::onValuesUpdated(const QVector<float> &newValues) {
    m_model->updateValues(newValues);
    
    // Подсчет FPS
    m_updateCounter++;
    if (m_fpsTimer.elapsed() >= 1000) {
        float fps = m_updateCounter * 1000.0f / m_fpsTimer.elapsed();
        m_updateRateLabel->setText(QString::number(fps, 'f', 1) + " Hz");
        m_updateCounter = 0;
        m_fpsTimer.restart();
    }
}

void MainWindow::updateStatistics() {
    m_totalLabel->setText(QString::number(m_model->totalCount()));
    m_avgLabel->setText(QString::number(m_model->averageValue(), 'f', 3));
    m_minLabel->setText(QString::number(m_model->minValue(), 'f', 3));
    m_maxLabel->setText(QString::number(m_model->maxValue(), 'f', 3));
}