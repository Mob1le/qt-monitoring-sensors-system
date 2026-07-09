#include <QApplication>
#include "main_window.h"
#include "detector_table_model.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    qRegisterMetaType<DetectorData>("DetectorData");
    qRegisterMetaType<QVector<DetectorData>>("QVector<DetectorData>");
    qRegisterMetaType<QVector<float>>("QVector<float>");
    
    app.setStyle("Fusion");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}