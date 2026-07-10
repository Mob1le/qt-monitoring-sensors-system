#pragma once
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <QElapsedTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QApplication>
#include <QCheckBox>
#include "detector_table_model.h"
#include "detector_data_generator.h"
#include "proxy_model/detectors_proxy_model.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartClicked();
    void onStopClicked();
    void onDetectorsInitialized(int count);
    void onValuesUpdated(const QVector<float> &newValues);
    void updateStatistics();
    void onFilterChanged();

private:
    void setupUI();
    void setupThread();

    // UI
    QTableView *m_tableView;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    
    // Статистика
    QLabel *m_totalLabel;
    QLabel *m_avgLabel;
    QLabel *m_minLabel;
    QLabel *m_maxLabel;

    // Данные и поток
    DetectorTableModel *m_model;
    QThread *m_workerThread;
    DetectorDataGenerator *m_generator;

    // Фильтрация и сортировка
    DetectorsProxyModel *proxyModel;
    QLabel filtrationLabel;
    QCheckBox *m_filterCheckBox;
};