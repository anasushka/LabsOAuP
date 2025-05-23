#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QHeaderView>
#include <QSplitter>
#include <QRandomGenerator>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), centralWidget(nullptr)
{
    tableSizes = {16, 64, 128, 2048};

    // Создаем хеш-таблицы с мультипликативным методом по умолчанию
    for (int size : tableSizes) {
        tables.append(new HashTable(size, HashTable::Multiplicative));
    }

    setupUI();
    setupCharts();
    updateStatistics();
}

MainWindow::~MainWindow()
{
    for (HashTable* table : tables) {
        delete table;
    }
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Основной layout - горизонтальный сплиттер
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal);

    // Левая панель управления
    QWidget *leftPanel = new QWidget();
    leftPanel->setMaximumWidth(350);
    leftPanel->setMinimumWidth(300);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    // Блок управления
    QGroupBox *controlGroup = new QGroupBox("Управление");
    QVBoxLayout *controlLayout = new QVBoxLayout(controlGroup);

    // Выбор метода хеширования
    QHBoxLayout *methodLayout = new QHBoxLayout();
    methodLayout->addWidget(new QLabel("Метод хеширования:"));
    hashMethodCombo = new QComboBox();
    hashMethodCombo->addItems({"Мультипликативное", "Модульное"});
    methodLayout->addWidget(hashMethodCombo);
    controlLayout->addLayout(methodLayout);

    // Ввод ключа
    QHBoxLayout *keyLayout = new QHBoxLayout();
    keyInput = new QLineEdit();
    keyInput->setPlaceholderText("Введите ключ");
    insertButton = new QPushButton("Вставить");
    searchButton = new QPushButton("Найти");
    keyLayout->addWidget(keyInput);
    keyLayout->addWidget(insertButton);
    keyLayout->addWidget(searchButton);
    controlLayout->addLayout(keyLayout);

    // Заполнение
    QHBoxLayout *fillLayout = new QHBoxLayout();
    fillCountSpinBox = new QSpinBox();
    fillCountSpinBox->setRange(50, 500);
    fillCountSpinBox->setValue(100);
    fillButton = new QPushButton("Заполнить случайно");
    fillLayout->addWidget(new QLabel("Количество:"));
    fillLayout->addWidget(fillCountSpinBox);
    fillLayout->addWidget(fillButton);
    controlLayout->addLayout(fillLayout);

    // Кнопки действий
    QHBoxLayout *actionLayout = new QHBoxLayout();
    clearButton = new QPushButton("Очистить");
    analyzeButton = new QPushButton("Анализ времени");
    actionLayout->addWidget(clearButton);
    actionLayout->addWidget(analyzeButton);
    controlLayout->addLayout(actionLayout);

    leftLayout->addWidget(controlGroup);

    // Таблица статистики (компактная)
    QGroupBox *statsGroup = new QGroupBox("Статистика");
    QVBoxLayout *statsLayout = new QVBoxLayout(statsGroup);
    statsTable = new QTableWidget();
    statsTable->setColumnCount(5);
    statsTable->setHorizontalHeaderLabels({"Размер", "Элементов", "Коллизии", "Загрузка", "Макс.пробы"});
    statsTable->horizontalHeader()->setStretchLastSection(true);
    statsTable->setMaximumHeight(150);
    statsLayout->addWidget(statsTable);
    leftLayout->addWidget(statsGroup);

    // Лог (компактный)
    QGroupBox *logGroup = new QGroupBox("Последние операции");
    QVBoxLayout *logLayout = new QVBoxLayout(logGroup);
    logOutput = new QTextEdit();
    logOutput->setMaximumHeight(120);
    logOutput->setFont(QFont("Consolas", 9));
    logLayout->addWidget(logOutput);
    leftLayout->addWidget(logGroup);

    leftLayout->addStretch();

    // Правая панель с графиками
    QWidget *rightPanel = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    // Графики в вертикальном сплиттере
    QSplitter *chartSplitter = new QSplitter(Qt::Vertical);

    // График времени поиска
    searchTimeChart = new QChart();
    searchTimeChart->setTitle("Время поиска в зависимости от размера таблицы");
    searchTimeChart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    searchTimeChartView = new QChartView(searchTimeChart);
    searchTimeChartView->setRenderHint(QPainter::Antialiasing);
    chartSplitter->addWidget(searchTimeChartView);

    // График коллизий
    collisionChart = new QChart();
    collisionChart->setTitle("Количество коллизий по размерам таблиц");
    collisionChart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    collisionChartView = new QChartView(collisionChart);
    collisionChartView->setRenderHint(QPainter::Antialiasing);
    chartSplitter->addWidget(collisionChartView);

    rightLayout->addWidget(chartSplitter);

    // Добавляем панели в основной сплиттер
    mainSplitter->addWidget(leftPanel);
    mainSplitter->addWidget(rightPanel);
    mainSplitter->setStretchFactor(0, 0); // Левая панель фиксированной ширины
    mainSplitter->setStretchFactor(1, 1); // Правая панель растягивается

    mainLayout->addWidget(mainSplitter);

    // Подключение сигналов
    connect(insertButton, &QPushButton::clicked, this, &MainWindow::insertKey);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::searchKey);
    connect(fillButton, &QPushButton::clicked, this, &MainWindow::fillWithCollisions);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearTables);
    connect(analyzeButton, &QPushButton::clicked, this, &MainWindow::runTimeAnalysis);
    connect(hashMethodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), [this]() {
        HashTable::HashMethod method = (hashMethodCombo->currentIndex() == 0) ?
                                           HashTable::Multiplicative : HashTable::Modular;

        for (int i = 0; i < tables.size(); i++) {
            delete tables[i];
            tables[i] = new HashTable(tableSizes[i], method);
        }
        updateStatistics();
        generateCollisionChart();
        log("Метод хеширования: " + hashMethodCombo->currentText());
    });

    // Включаем обработку Enter в поле ввода
    connect(keyInput, &QLineEdit::returnPressed, this, &MainWindow::insertKey);

    setWindowTitle("Исследование хеш-таблиц - Мультипликативное хеширование");
    resize(1200, 800);
}

void MainWindow::setupCharts()
{
    // Инициализация графиков выполняется в setupUI()
}

void MainWindow::insertKey()
{
    bool ok;
    int key = keyInput->text().toInt(&ok);
    if (!ok || key <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите положительное число");
        return;
    }

    int successCount = 0;
    for (int i = 0; i < tables.size(); i++) {
        bool inserted = tables[i]->insert(key);
        if (inserted) successCount++;
    }

    if (successCount > 0) {
        log(QString("Ключ %1 вставлен в %2 таблиц").arg(key).arg(successCount));
        keyInput->clear();
    } else {
        log(QString("Ключ %1 уже существует или таблицы заполнены").arg(key));
    }

    updateStatistics();
    generateCollisionChart();
}

void MainWindow::searchKey()
{
    bool ok;
    int key = keyInput->text().toInt(&ok);
    if (!ok || key <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите положительное число");
        return;
    }

    QString result = QString("Поиск %1: ").arg(key);
    for (int i = 0; i < tables.size(); i++) {
        int comparisons;
        bool found = tables[i]->search(key, comparisons);
        result += QString("T%1(%2) ").arg(tableSizes[i]).arg(found ? "+" : "-");
    }

    log(result);
}

void MainWindow::fillWithCollisions()
{
    int count = fillCountSpinBox->value();
    QRandomGenerator *rng = QRandomGenerator::global();

    for (int i = 0; i < count; i++) {
        int key = rng->bounded(1, 5000); // Меньший диапазон для большего количества коллизий
        for (HashTable* table : tables) {
            table->insert(key);
        }
    }

    log(QString("Добавлено %1 случайных ключей").arg(count));
    updateStatistics();
    generateCollisionChart();
}

void MainWindow::clearTables()
{
    for (HashTable* table : tables) {
        table->clear();
    }

    log("Все таблицы очищены");
    updateStatistics();
    generateCollisionChart();
    generateSearchTimeChart();
}

void MainWindow::runTimeAnalysis()
{
    log("Анализ времени поиска...");

    // Проверяем заполненность таблиц
    bool needFill = true;
    for (HashTable* table : tables) {
        if (table->getLoadFactor() > 0.1) {
            needFill = false;
            break;
        }
    }

    // Заполняем если нужно
    if (needFill) {
        QRandomGenerator *rng = QRandomGenerator::global();
        for (int i = 0; i < tables.size(); i++) {
            int targetKeys = tableSizes[i] / 2; // 50% заполнения
            for (int j = 0; j < targetKeys; j++) {
                int key = rng->bounded(1, 10000);
                tables[i]->insert(key);
            }
        }
        updateStatistics();
        generateCollisionChart();
    }

    generateSearchTimeChart();
    log("Анализ завершен");
}

void MainWindow::updateStatistics()
{
    statsTable->setRowCount(tables.size());

    for (int i = 0; i < tables.size(); i++) {
        statsTable->setItem(i, 0, new QTableWidgetItem(QString::number(tableSizes[i])));

        int elements = static_cast<int>(tables[i]->getLoadFactor() * tableSizes[i]);
        statsTable->setItem(i, 1, new QTableWidgetItem(QString::number(elements)));

        statsTable->setItem(i, 2, new QTableWidgetItem(QString::number(tables[i]->getCollisionsCount())));

        QString loadStr = QString::number(tables[i]->getLoadFactor() * 100, 'f', 1) + "%";
        statsTable->setItem(i, 3, new QTableWidgetItem(loadStr));

        statsTable->setItem(i, 4, new QTableWidgetItem(QString::number(tables[i]->getMaxProbes())));
    }
}

void MainWindow::generateSearchTimeChart()
{
    searchTimeChart->removeAllSeries();

    QLineSeries *series = new QLineSeries();
    series->setName("Среднее время поиска");

    QRandomGenerator *rng = QRandomGenerator::global();

    for (int i = 0; i < tables.size(); i++) {
        if (tables[i]->getLoadFactor() > 0) {
            double totalTime = 0;
            int testCount = 50;

            for (int j = 0; j < testCount; j++) {
                int testKey = rng->bounded(1, 10000);
                double time = tables[i]->measureSearchTime(testKey, 100);
                totalTime += time;
            }

            double avgTime = totalTime / testCount;
            series->append(tableSizes[i], avgTime);
        }
    }

    if (series->count() > 0) {
        searchTimeChart->addSeries(series);
        searchTimeChart->createDefaultAxes();
        searchTimeChart->axes(Qt::Horizontal).first()->setTitleText("Размер таблицы");
        searchTimeChart->axes(Qt::Vertical).first()->setTitleText("Время (нс)");
    }
}

void MainWindow::generateCollisionChart()
{
    collisionChart->removeAllSeries();

    QLineSeries *series = new QLineSeries();
    series->setName("Коллизии");

    for (int i = 0; i < tables.size(); i++) {
        series->append(tableSizes[i], tables[i]->getCollisionsCount());
    }

    collisionChart->addSeries(series);
    collisionChart->createDefaultAxes();
    collisionChart->axes(Qt::Horizontal).first()->setTitleText("Размер таблицы");
    collisionChart->axes(Qt::Vertical).first()->setTitleText("Количество коллизий");
}

void MainWindow::log(const QString &message)
{
    QTime time = QTime::currentTime();
    logOutput->append(QString("%1: %2").arg(time.toString("hh:mm:ss")).arg(message));

    // Ограничиваем количество строк в логе
    if (logOutput->document()->blockCount() > 20) {
        QTextCursor cursor = logOutput->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
    }

    logOutput->moveCursor(QTextCursor::End);
}
