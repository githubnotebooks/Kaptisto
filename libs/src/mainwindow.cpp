#include "mainwindow.hpp"
#include "screen_shot_widget.hpp"
#include "size.hpp"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(kaptisto::width, kaptisto::height);
    auto widget_ = new kaptisto::ScreenshotWidget(this);
    setCentralWidget(widget_);
}

MainWindow::~MainWindow()
{
    delete ui;
}
