#ifndef USOCKET_H
#define USOCKET_H

#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class USocket;
}

class USocket : public QMainWindow
{
    Q_OBJECT

public:
    explicit USocket(QWidget *parent = nullptr);
    ~USocket();


public slots:
//    void sendMsg();
    void processPendingMeg();


private slots:
    void on_pushButton_clicked();

private:
    Ui::USocket *ui;

    QUdpSocket *socket;
};

#endif // USOCKET_H
