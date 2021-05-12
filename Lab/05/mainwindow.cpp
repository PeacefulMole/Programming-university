#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>

void MainWindow::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Допустимые форматы (*.png)"));

    if(!fileName.size()){
        return;
    }
    if (!image.load(fileName)){
            ui->label->setText("Изображение не загружено");
            return;
        }
    image.convertTo(QImage::Format_ARGB32);
    ui->label->setText("Изображение успешно загружено");

}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image "), "", tr("Допустимые форматы (*.png)"));
    if (!image.save(fileName, ".png")){
        ui->label->setText("Изображение успешно сохранено");
        return;
    }
    ui->label->setText("Изображение не сохранено");
}

void MainWindow::encodeMsg()
{

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadImgButton, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(ui->saveImgButton, &QPushButton::clicked, this, &MainWindow::saveImage);
    connect(ui->encodeTxtButton, &QPushButton::clicked, this, &MainWindow::encodeMsg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

