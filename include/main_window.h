#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QSortFilterProxyModel>
#include "detector_data_model.h"

class MainWindow : public QWidget {
private:
    QTableView *table_view;
    DetectorDataModel *data_model;
    QSortFilterProxyModel *sort_filter_model;

    QLabel *statistics_label;
    QPushButton *start_stop_button;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartStopClicked();
};