// MainWindow.h
#pragma once
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <QElapsedTimer>
#include "detector_table_model.h"
#include "detector_data_generator.h"

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
    QLabel *m_updateRateLabel;  // Частота обновления

    // Данные и поток
    DetectorTableModel *m_model;
    QThread *m_workerThread;
    DetectorDataGenerator *m_generator;
    
    // Для измерения производительности
    QElapsedTimer m_fpsTimer;
    int m_updateCounter = 0;
};