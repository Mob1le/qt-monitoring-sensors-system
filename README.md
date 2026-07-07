# qt-monitoring-sensors-system
ТЕСТОВОЕ ЗАДАНИЕ: СИСТЕМА МОНИТОРИНГА ДАТЧИКОВ


## План работ

1. Создать проект (QMainWindow) и класс датчика (Detector)
2. Создать реализацию Model-View. (DetectorModel наследованный от QAbstractTableModel)
3. Подключить БД к модели DetectorModel с тестовым набором данных (Например SQLite)
4. Реализовать сортировку (через БД для уменьшения нагрузки)
5. TODO

## Структура проекта

```mermaid
treeView-beta
"qt-monitoring-sensors-system/"
    "build/"
    "src/"
    "include/"
    "tests/"
        "CMakeLists.txt"
"CMakeLists.txt"
```

## Архитектура проекта

```mermaid
architecture-beta
    group app(cloud)["Приложение"]

    service db(database)[SQLite] in app
    service main_window(cloud)[MainWindow] in app
    service model(server)[DetectorModel] in app

    db:L -- R:model
    main_window:R -- L:model
```