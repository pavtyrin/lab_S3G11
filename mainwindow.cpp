#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> // Для обработки ошибок
#include <cmath> // Для математических операций
#include <QInputDialog> // Для отображения диалоговых окон


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Соединение кнопок цифр
        connect(ui->button0, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button1, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button2, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button3, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button4, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button5, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button6, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button7, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button8, &QPushButton::clicked, this, &MainWindow::digitClicked);
        connect(ui->button9, &QPushButton::clicked, this, &MainWindow::digitClicked);

        // Соединение кнопок операций
        connect(ui->buttonAdd, &QPushButton::clicked, this, &MainWindow::operationClicked);
        connect(ui->buttonSubtract, &QPushButton::clicked, this, &MainWindow::operationClicked);
        connect(ui->buttonMultiply, &QPushButton::clicked, this, &MainWindow::operationClicked);
        connect(ui->buttonDivide, &QPushButton::clicked, this, &MainWindow::operationClicked);
        connect(ui->buttonAbs, &QPushButton::clicked, this, &MainWindow::absClicked);
        connect(ui->buttonSin, &QPushButton::clicked, this, &MainWindow::sinClicked);
        connect(ui->buttonLog, &QPushButton::clicked, this, &MainWindow::logClicked);
        connect(ui->buttondB, &QPushButton::clicked, this, &MainWindow::dbClicked);

        // Кнопка "="
        connect(ui->buttonEquals, &QPushButton::clicked, this, &MainWindow::equalsClicked);

        // Кнопка "C"
        connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::clearClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digitClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    QString newText = ui->lineEdit_display->text() + button->text();
    ui->lineEdit_display->setText(newText);
}

void MainWindow::operationClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    currentValue = ui->lineEdit_display->text().toDouble();
    pendingOperation = button->text();
    ui->lineEdit_display->clear();
}

void MainWindow::equalsClicked()
{
    double secondValue = ui->lineEdit_display->text().toDouble();
    double result = 0;

    if (pendingOperation == "+") result = currentValue + secondValue;
    else if (pendingOperation == "-") result = currentValue - secondValue;
    else if (pendingOperation == "*") result = currentValue * secondValue;
    else if (pendingOperation == "/") {
        if (secondValue == 0) {
            QMessageBox::warning(this, "Ошибка", "Деление на ноль невозможно!");
            return;
        }
        result = currentValue / secondValue;
    }

    ui->lineEdit_display->setText(QString::number(result));
    currentValue = result; // Сохраняем результат для следующей операции
}

void MainWindow::clearClicked()
{
    ui->lineEdit_display->clear();
    currentValue = 0;
    pendingOperation.clear();
}

void MainWindow::absClicked()
{
    double value = ui->lineEdit_display->text().toDouble();
    double result = std::abs(value);
    ui->lineEdit_display->setText(QString::number(result));
}

void MainWindow::sinClicked()
{
    double value = ui->lineEdit_display->text().toDouble();
    double result = std::sin(value); // В радианах
    ui->lineEdit_display->setText(QString::number(result));
}

void MainWindow::logClicked()
{
    bool ok;
    double base = QInputDialog::getDouble(this, "Основание логарифма",
                                          "Введите основание (n):", 10, 0.0001, 100, 4, &ok);
    if (!ok) return;

    double value = ui->lineEdit_display->text().toDouble();
    if (value <= 0 || base <= 0 || base == 1) {
        QMessageBox::warning(this, "Ошибка", "Некорректные значения для логарифма.");
        return;
    }
    double result = std::log(value) / std::log(base);
    ui->lineEdit_display->setText(QString::number(result));
}

void MainWindow::dbClicked()
{
    double value = ui->lineEdit_display->text().toDouble();
    if (value <= 0) {
        QMessageBox::warning(this, "Ошибка", "Значение должно быть положительным.");
        return;
    }
    double result = 20 * std::log10(value);
    ui->lineEdit_display->setText(QString::number(result));
}
