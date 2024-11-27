#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    double currentValue;        // Текущее значение
    QString pendingOperation;  // Ожидаемая операция

private slots:
    void digitClicked();        // Обработка нажатия на цифру
    void operationClicked();    // Обработка нажатия на операцию
    void clearClicked();        // Сброс данных
    void equalsClicked();       // Вычисление результата
    void absClicked();
    void sinClicked();
    void logClicked();
    void dbClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
