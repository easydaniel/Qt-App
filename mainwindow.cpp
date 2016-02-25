#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qdir>
#include <QFileInfo>
#include <QFile>
#include <QDesktopServices>
#include <QRegExp>
#include <QMessageBox>
#include <QUrl>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("ACME - Inventory Uploader Maker");
    changeStatus("Step 1: Click Settings");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeStatus(QString text) {
    ui->status->setText(text);
}

QStringList MainWindow::createList(QString path) {
    QStringList list;
    QFile input(path);
    input.open(QIODevice::ReadOnly);
    QTextStream in(&input);

    while (!in.atEnd()) {
        list.append(in.readLine());
    }
    input.close();
    if (list.size() == 1) {
        return list.at(0).split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    } else {
        return list;
    }
}

QString MainWindow::generate(QString line, int quantity, float d1, float d2, float d3, float d4, float d5, float d6, int nvlts, int ohlts, int allts, int galts, QStringList stocklist, QStringList pricelist) {
    QString result = "TMP";
    if (stocklist.empty()) {

    }
    return result;
}



void MainWindow::on_generate_clicked()
{
    QString format = "sku,product-id,product-id-type,price,minimum-seller-allowed-price,maximum-seller-allowed-price,item-condition,quantity,add-delete,will-ship-internationally,expedited-shipping,standard-plus,item-note,fulfillment-center-id,product-tax-code,leadtime-to-ship,date,real-leadtime-to-ship";
    if (output.isEmpty()) {
        output = QDir::homePath();
    }

    if (input.size()) {

        QFile outFile(output + "/ACME Inventory Loader.csv");
        outFile.open(QIODevice::ReadWrite);
        QTextStream out(&outFile);
        out << format << endl;

        QStringList list = createList(input);
        QStringList stocklist = createList(stock);
        QStringList pricelist = createList(price);
        foreach (QString line, list) {
            out << generate(line, qty, d1, d2, d3, d4, d5, d6, nvlts, ohlts, allts, galts, stocklist, pricelist) << endl;
            //qDebug(line.toLatin1());
            fflush(stderr);
        }
        outFile.close();
        QDesktopServices::openUrl(QUrl::fromLocalFile(output));
    } else {
        QMessageBox::warning(this,
                             tr("Warning"),
                             tr("Input Not Selected")
                             );
    }
    changeStatus("Step 1: Click Settings");
}

void MainWindow::on_setting_clicked()
{
    setting = new settings;
    // Setup default value
    base = QDir::homePath();

    d1 = 100.0;
    d2 = 100.0;
    d3 = 100.0;
    d4 = 100.0;
    d5 = 100.0;
    d6 = 100.0;

    qty = 5;

    nvlts = 4;
    allts = 9;
    ohlts = 9;
    galts = 9;


    setting->setMainWindow(this);
    setting->show();
}
