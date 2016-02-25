#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <settings.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void changeStatus(QString);
    QStringList createList(QString);
    QString generate(QString, int, float, float, float, float, float, float, int, int, int, int, QStringList, QStringList);
    ~MainWindow();

private slots:
    void on_generate_clicked();

    void on_setting_clicked();

private:
    Ui::MainWindow *ui;
    settings *setting;
    friend class settings;
    int qty;
    int nvlts;
    int allts;
    int galts;
    int ohlts;
    QString output;
    QString base;
    QString price;
    QString stock;
    QString input;
    float d1;
    float d2;
    float d3;
    float d4;
    float d5;
    float d6;

};

#endif // MAINWINDOW_H
