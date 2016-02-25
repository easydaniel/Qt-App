#include "settings.h"
#include "ui_settings.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

MainWindow* mw;

settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    // Init UI
    this->setWindowTitle(tr("Settings"));

    // Discount Section
    ui->d1->setPlaceholderText("Default 100");
    ui->d2->setPlaceholderText("Default 100");
    ui->d3->setPlaceholderText("Default 100");
    ui->d4->setPlaceholderText("Default 100");
    ui->d5->setPlaceholderText("Default 100");
    ui->d6->setPlaceholderText("Default 100");

    // Quantity Section
    ui->quantity->setPlaceholderText("Default 5");

    // LeadTime Section
    ui->vnvlts->setPlaceholderText("Default 4");
    ui->vallts->setPlaceholderText("Default 9");
    ui->vgalts->setPlaceholderText("Default 9");
    ui->vohlts->setPlaceholderText("Default 9");

    //Status Init
    ui->settingStep->setText("Step 1: Select Stock File");

}

settings::~settings()
{
    delete ui;
}

void settings::setMainWindow(MainWindow* p)
{
    mw = p;
}

void settings::on_cancel_clicked()
{
    this->hide();
}

void settings::on_stock_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Stock List"),
                                                mw->base,
                                                tr("csv file (*.csv)"));
    if (path.size()) {
        ui->settingStep->setText("Step 2: Select Input");
        mw->base = path;
        mw->stock = path;
        qDebug(path.toLatin1());
    }
}

void settings::on_input_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Input List"),
                                                mw->base,
                                                tr("csv file (*.csv)"));
    if (path.size()) {
        ui->settingStep->setText("Step 3: Select Price");
        mw->base = path;
        mw->input = path;
        qDebug(path.toLatin1());
    }
}

void settings::on_imap_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Price List"),
                                                mw->base,
                                                tr("csv file (*.csv)"));
    if (path.size()) {
        ui->settingStep->setText("Step 4: Save Settings");
        mw->base = path;
        mw->price = path;
        qDebug(path.toLatin1());
    }
}

void settings::on_save_clicked()
{

    if (!mw->input.size()) {
        QMessageBox::warning(this,
                             tr("Warning"),
                             tr("Input Not Selected")
                             );
        return;
    }

    QString path = QFileDialog::getExistingDirectory(this,
                                                     tr("Select Output Directory"),
                                                     mw->base);
    if (path.size()) {

        mw->base = path;
        mw->output = path;

        if (ui->vnvlts->isModified() && ui->vnvlts->text().toInt() > 0) {
            mw->nvlts = ui->vnvlts->text().toInt();
            qDebug(QString("NVLTS: " + QString::number(mw->nvlts)).toLatin1());
        }
        if (ui->vallts->isModified() && ui->vallts->text().toInt() > 0) {
            mw->allts = ui->vallts->text().toInt();
            qDebug(QString("ALLTS: " + QString::number(mw->allts)).toLatin1());
        }
        if (ui->vohlts->isModified() && ui->vohlts->text().toInt() > 0) {
            mw->ohlts = ui->vohlts->text().toInt();
            qDebug(QString("OHLTS: " + QString::number(mw->ohlts)).toLatin1());
        }
        if (ui->vgalts->isModified() && ui->vgalts->text().toInt() > 0) {
            mw->galts = ui->vgalts->text().toInt();
            qDebug(QString("GALTS: " + QString::number(mw->galts)).toLatin1());
        }

        if (ui->d1->isModified() && ui->d1->text().toFloat() > 65) {
            mw->d1 = ui->d1->text().toFloat();
            qDebug(QString("d1: " + QString::number(mw->d1)).toLatin1());
        }

        if (ui->d2->isModified() && ui->d2->text().toFloat() > 65) {
            mw->d2 = ui->d2->text().toFloat();
            qDebug(QString("d2: " + QString::number(mw->d2)).toLatin1());
        }

        if (ui->d3->isModified() && ui->d3->text().toFloat() > 65) {
            mw->d3 = ui->d3->text().toFloat();
            qDebug(QString("d3: " + QString::number(mw->d3)).toLatin1());
        }

        if (ui->d4->isModified() && ui->d4->text().toFloat() > 65) {
            mw->d4 = ui->d4->text().toFloat();
            qDebug(QString("d4: " + QString::number(mw->d4)).toLatin1());
        }

        if (ui->d5->isModified() && ui->d5->text().toFloat() > 65) {
            mw->d5 = ui->d5->text().toFloat();
            qDebug(QString("d5: " + QString::number(mw->d5)).toLatin1());
        }

        if (ui->d6->isModified() && ui->d6->text().toFloat() > 65) {
            mw->d6 = ui->d6->text().toFloat();
            qDebug(QString("d6: " + QString::number(mw->d6)).toLatin1());
        }

        qDebug(QString("Stock: " + mw->stock).toLatin1());
        qDebug(QString("Input: " + mw->input).toLatin1());
        qDebug(QString("Price: " + mw->price).toLatin1());
        qDebug(QString("Output: " + mw->output).toLatin1());



        fflush(stderr);

        this->hide();
        mw->changeStatus("Step 2: Generate");
        QMessageBox::information(this,
                                 tr("Settings"),
                                 tr("Settings Saved"));
    }
}
