#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QThread>

#include "detector_data_model.h"
#include "detector_generator.h"

class MainWindow : public QWidget {
    Q_OBJECT
private:
    QTableView *table_view;
    DetectorDataModel *data_model;
    QSortFilterProxyModel *sort_filter_model;

    QLabel *statistics_label;
    QPushButton *start_stop_button;

    QThread gen_thread;
    DetectorGenerator detector_generator;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartStopClicked();
};