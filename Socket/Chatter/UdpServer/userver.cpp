#include "userver.h"
#include "ui_userver.h"

UServer::UServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UServer)
{
    ui->setupUi(this);
    socket = new QUdpSocket;
    socket->bind(2468);
    connect(socket, SIGNAL(readyRead()), this, SLOT(processPendingMeg()));
}

UServer::~UServer()
{
    delete ui;
}
void UServer::processPendingMeg()
{
    QByteArray datagram;
    do{
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
    }while (socket->hasPendingDatagrams());
    QDataStream in(&datagram, QIODevice::ReadOnly);
    QString textComing;
    in >> textComing;
    this->ui->textEdit->append(textComing);
}

void UServer::on_pushButton_clicked()
{
    QByteArray datagram;
    datagram.clear();
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << this->ui->textEdit_2->toPlainText();
    QHostAddress adr;
    adr.setAddress(QHostAddress::LocalHost);
    socket->writeDatagram(datagram, adr, 1234);
}
