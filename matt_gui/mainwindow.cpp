#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MattDaemon)
{
    ui->setupUi(this);

    connect(ui->inputField, &QLineEdit::returnPressed,
            this, &MainWindow::on_sendButton_clicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);


    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 4242);

    if (!socket->waitForConnected(1000)) {
        QMessageBox::critical(this, "Error", "Unable to connect to the daemon !");
    }

    this->setWindowTitle("Matt Daemon");
    this->setMinimumWidth(400);
    this->setFixedHeight(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString message = ui->inputField->text();
    if (message.isEmpty()) return;

    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(message.toUtf8());
        socket->write("\n");
        socket->flush();
        ui->inputField->clear();
    } else {
        QMessageBox::warning(this, "Error", "Connection not established.");
    }

    if (message.trimmed().toLower() == "quit") {
        close();
        return;
    }
}
