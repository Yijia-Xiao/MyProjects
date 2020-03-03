#ifndef USERVER_H
#define USERVER_H

#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class UServer;
}

class UServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit UServer(QWidget *parent = nullptr);
    ~UServer();

public slots:
//    void sendMsg();
    void processPendingMeg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UServer *ui;
    QUdpSocket *socket;
};

#endif // USERVER_H
