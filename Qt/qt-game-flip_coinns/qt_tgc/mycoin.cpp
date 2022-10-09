#include "mycoin.h"
#include<QPixmap>
#include<QIcon>


MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    if(!pix.load(btnImg)) return;
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    //初始化定时器对象
    timer = new QTimer(this);

    //监听时钟，进行翻面
    connect(timer, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str;
        if(this->flag == 0) str = QString(":/res/Coin000%1").arg(this->min++);
        else str = QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);
        //规范格式
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //如果翻转完毕
        if(this->flag == 0 && min > max)
        {
            min = 1;
            timer->stop();
            this->changable = 1;
        }
        else if(this->flag == 1 && max < min)
        {
            max = 8;
            timer->stop();
            this->changable = 1;
        }
    });
}

//改变正反面标志的方法
void MyCoin::changeFlag()
{
    this->flag = !this->flag;
    this->changable = 0;
    timer->start(30);
}

void MyCoin::mousePressEvent(QMouseEvent* e)
{
    if(!this->changable || this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
