#include "playscene.h"
#include"mypushbutton.h"
#include"mycoin.h"
#include"dataconfig.h"

#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QString>
#include<QPropertyAnimation>
#include<QSoundEffect>

PlayScene::PlayScene(int levelNum)
{
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("游戏中...");
    //创建菜单栏
    QMenuBar* menubar = menuBar();
    this->setMenuBar(menubar);
    //创建开始菜单
    QMenu* startMenu = menubar->addMenu("开始");
    QAction* exitAction = startMenu->addAction("退出");
    connect(exitAction, &QAction::triggered, [=](){
        this->close();
    });

    //返回按钮音效
    QSoundEffect* backSound = new QSoundEffect();
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    backSound->setParent(this);
    backSound->setLoopCount(1); //设置播放循环，-1表示无限

    /*返回按钮*/
    myPushButton* backBtn = new myPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height() - backBtn->height());
    //点击返回标题
    connect(backBtn, &myPushButton::clicked, this, [=](){
        //返回主场景 主场景监听返回按钮 自定义信号-槽
        backSound->play();
        QTimer::singleShot(300, this, [=](){
            emit this->chooseSceneBack();
        });
    });

    //左下角 显示当前关卡数
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    font.setBold(10);
    QString lstr = QString("Level: %1").arg(this->levelIndex);
    label->setText(lstr);
    label->setFont(font);
    label->setGeometry(10, this->height() - 50, 120, 50);

    //初始化关卡数据
    dataConfig config;
    for(int r = 0; r < 4; r++)
    {
       for(int c = 0; c < 4; c++)
       {
           this->gameArray[r][c] = config.mData[this->levelIndex][r][c];
       }
    }

    //翻金币音效
    QSoundEffect* flipSound = new QSoundEffect();
    flipSound->setParent(this);
    flipSound->setLoopCount(1);
    flipSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    //胜利音效
    QSoundEffect* winSound = new QSoundEffect();
    winSound->setParent(this);
    winSound->setLoopCount(1);
    winSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    //胜利图片设置
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width())*0.5, -tmpPix.height());

    //显示金币游戏背景图
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            //绘制背景图
            QLabel* label = new QLabel;
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57 + r*50, 200 + c*50);
            //创建金币/银币
            MyCoin* coin;
            if(this->gameArray[r][c] == 1) coin = new MyCoin(":/res/Coin0001.png");
            else coin = new MyCoin(":/res/Coin0008.png");
            coin->setParent(this);
            coin->move(59 + r*50, 204 + c*50);

            //赋值金币属性
            coin->posX = c;
            coin->posY = r;
            coin->flag = this->gameArray[r][c]; //1正面；2反面
            coin->changable = true;
            coin->isWin = false;

            //将金币放入二维数组
            coins[r][c] = coin;

            //点击金币 进行翻转
            connect(coin, &MyCoin::clicked, [=](){
                //禁止翻转所有硬币-防止迅速翻多个金币
                for(int r = 0; r < 4; r++)
                {
                    for(int c = 0; c < 4; c++)
                    {
                        coins[r][c]->changable = false;
                    }
                }

               coin->changeFlag();
               flipSound->play();

               //翻转周围硬币
               QTimer::singleShot(300, this, [=](){
                   if(coin->posX + 1 < 4)
                   {
                       coins[coin->posY][coin->posX+1]->changeFlag();
                       this->gameArray[coin->posY][coin->posX+1] = !this->gameArray[coin->posY][coin->posX+1];
                   }
                   if(coin->posX - 1 >= 0)
                   {
                       coins[coin->posY][coin->posX-1]->changeFlag();
                       this->gameArray[coin->posY][coin->posX-1] = !this->gameArray[coin->posY][coin->posX-1];
                   }
                   if(coin->posY + 1 < 4)
                   {
                       coins[coin->posY+1][coin->posX]->changeFlag();
                       this->gameArray[coin->posY+1][coin->posX] = !this->gameArray[coin->posY+1][coin->posX];
                   }
                   if(coin->posY - 1 >= 0)
                   {
                       coins[coin->posY-1][coin->posX]->changeFlag();
                       this->gameArray[coin->posY-1][coin->posX] = !this->gameArray[coin->posY-1][coin->posX];
                   }

                   //允许翻转所有硬币-防止迅速翻多个金币
                   for(int r = 0; r < 4; r++)
                   {
                       for(int c = 0; c < 4; c++)
                       {
                           coins[r][c]->changable = true;
                       }
                   }

                   //判断是否胜利
                    this->isWin = true;
                   for(int r = 0; r < 4; r++)
                   {
                       for(int c = 0; c < 4; c++)
                       {
                           if(coins[r][c]->flag == false)
                           {
                               this->isWin = false;
                               break;
                           }
                       }
                   }
                   if(this->isWin)  //胜利了！
                   {
                        //将所有按钮的胜利标志更改为true，禁用按钮
                        for(int r = 0; r < 4; r++)
                        {
                            for(int c = 0; c < 4; c++)
                            {
                                coins[r][c]->isWin = true;
                            }
                        }
                        qDebug() << "胜利了！";
                        winSound->play();
                        //显示胜利图片
                        QPropertyAnimation* animation = new QPropertyAnimation(winLabel, "geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(), winLabel->y()+114, winLabel->width(), winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                   }
               });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent*)
{
    /*绘制背景图片*/
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    /*绘制背景上图标*/
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);  //图片缩放
    painter.drawPixmap(10, 30, pix);
}
