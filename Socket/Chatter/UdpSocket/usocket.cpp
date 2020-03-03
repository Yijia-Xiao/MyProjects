#include "usocket.h"
#include "ui_usocket.h"

USocket::USocket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::USocket)
{
    ui->setupUi(this);
    socket = new QUdpSocket;
    socket->bind(1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(processPendingMeg()));
}

USocket::~USocket()
{
    delete ui;
}
void USocket::processPendingMeg()
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

void USocket::on_pushButton_clicked()
{
    QByteArray datagram;
    datagram.clear();
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << this->ui->textEdit_2->toPlainText();
    QHostAddress adr;
    adr.setAddress(QHostAddress::LocalHost);
    socket->writeDatagram(datagram, adr, 2468);
}
