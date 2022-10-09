#include "chooselevelscene.h"

#include<QMenuBar>
#include<QPainter>
#include<QLabel>
#include<QTimer>
#include<QSoundEffect>

#include"mypushbutton.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择关卡场景
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar* menubar = menuBar();
    this->setMenuBar(menubar);
    //创建开始菜单
    QMenu* startMenu = menubar->addMenu("开始");
    QAction* exitAction = startMenu->addAction("退出");
    connect(exitAction, &QAction::triggered, [=](){
        this->close();
    });

    //选择关卡音效
    QSoundEffect* chooseSound = new QSoundEffect();
    chooseSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    chooseSound->setParent(this);
    chooseSound->setLoopCount(1);

    //返回按钮音效
    QSoundEffect* backSound = new QSoundEffect();
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    backSound->setParent(this);
    backSound->setLoopCount(1);

    /*返回按钮*/
    myPushButton* backBtn = new myPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height() - backBtn->height());
    //点击返回标题
    connect(backBtn, &myPushButton::clicked, [=](){
        //返回主场景 主场景监听返回按钮 自定义信号-槽
        emit this->chooseSceneBack();
        backSound->play();
    });

    /*创建选择关卡的按钮*/
    for(int i = 0; i < 20; i++)
    {
        myPushButton* menuBtn = new myPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        //起始值25/170，间距70，二维矩阵布局
        menuBtn->move((25 + (i % 4) * 70), (170 + (i / 4) * 70));

        //监听每个按钮的点击事件
        connect(menuBtn, &myPushButton::clicked, [=](){
            //按压特效
            menuBtn->press_zoom();
            //弹起特效
            menuBtn->release_zoom();
            chooseSound->play();

            //延时进入选择关卡 目的：完整显示按钮弹起特效
            //延迟特定事件后执行一个函数
            QTimer::singleShot(300, this, [=](){
                play = new PlayScene(i+1);
                //保持窗口位置一致
                play->setGeometry(this->geometry());
                //进入到游戏场景
                this->hide();
                play->show();
                //监听游戏场景退出按钮，代码放置于此处，play指针正确对应到游戏场景对象
                connect(play, &PlayScene::chooseSceneBack, this, [=](){
                    this->setGeometry(play->geometry());
                    delete play;
                    play = nullptr;
                    this->show();
                });
            });
        });

        //使用标签控件标注数字
        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move((25 + (i % 4) * 70), (170 + (i / 4) * 70));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标穿透 避免labe挡住按钮无法被点击
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    /*绘制背景图片*/
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    /*绘制背景上图标*/
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width(), pix.height());  //图片缩放
    painter.drawPixmap(10, 30, pix);
}
