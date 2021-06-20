//
// Created by jafar on 7/29/17.
//

#ifndef AGARTEST1_GAMEPAGE_H
#define AGARTEST1_GAMEPAGE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QString>

class GamePage : public QGraphicsView
{
    Q_OBJECT
public:
    GamePage(int, int, QString, int , QGraphicsView * = 0);

protected:
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    bool bot_flag;
    bool viewer_flag;
    QString username;
    QGraphicsScene* graphicsScene;
    QPushButton* exit;
    QColor* user_color;
    QGraphicsEllipseItem *user_cell;
    int number;

public slots:
    void recieve(QString);
//    void omit_user(QString);

signals:
    void sendMessage(QString);

};

#endif //AGARTEST1_GAMEPAGE_H
