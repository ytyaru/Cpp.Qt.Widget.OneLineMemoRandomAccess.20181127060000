#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString filePath = QDir(QApplication::applicationDirPath()).filePath(tr("memo.tsv"));
    QFile file(filePath);
    //if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::information(this, tr("ファイルが開けませんでした"), file.errorString());
        return;
    }
    file.seek(0);

    QDateTime dt = QDateTime::currentDateTime();
    QString line = dt.toString("yyyy-MM-dd HH:mm:ss.zzz") + tr("\t") + ui->lineEdit->text();
    QTextStream out(&file);
    out.seek(0);
    out << line << endl;
    qDebug() << line;
    file.close();
}
