#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>


class MainWindow;

namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    void setMainWindow(MainWindow*);
    ~settings();

private slots:
    void on_cancel_clicked();

    void on_stock_clicked();

    void on_input_clicked();

    void on_imap_clicked();

    void on_save_clicked();

private:
    Ui::settings *ui;
};

#endif // SETTINGS_H
