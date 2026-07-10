# qt-monitoring-sensors-system
ТЕСТОВОЕ ЗАДАНИЕ: СИСТЕМА МОНИТОРИНГА ДАТЧИКОВ на Qt 5.15 C++

## Инструкция по сборке
В терминале (в директории проекта `qt-monitoring-sensors-system/`)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Структура проекта

```mermaid
treeView-beta
"qt-monitoring-sensors-system/"
    "src/"
    "include/"
      "proxy_model/"
"CMakeLists.txt"
```

## Архитектура проекта

```mermaid
flowchart BT
    UI_MW[MainWindow]
    UI_Stats[StatisticsPanel]
    UI_Table[QTableView]
    
    Core_Model[(DetectorTableModel)]
    Core_Generator[DetectorDataGenerator]
    Service_Proxy[ProxyModel]

    UI_Stats --> UI_MW
    Core_Model --> Service_Proxy
    Service_Proxy --> UI_Table
    UI_Table --> UI_MW
    Core_Generator e1@--> Core_Model
    Core_Model --> UI_Stats
    
    e1@{ animation: fast }
```