#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMainWindow>
#include<QAction>
#include<QPainter>
#include<QTimer>
#include<QSoundEffect>

#include"mypushbutton.h"
#include"chooselevelscene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*主场景设置*/
    setFixedSize(320, 588);                     //固定窗口大小
    setWindowIcon(QIcon(":/res/Coin0001.png"));  //设置窗口标志
    setWindowTitle("FGC");                      //设置窗口标题

    /*菜单栏按钮设置*/
    connect(ui->actionExit, &QAction::triggered, [=]()->void{
        this->close();
    });

    //进入选择关卡场景 实例化选择关卡场景
    ChooseScene = new ChooseLevelScene;

    /*监听关卡选择界面返回按钮*/
    //监听选择关卡界面返回按钮信号
    connect(ChooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]()->void{
        //延时返回
        QTimer::singleShot(250, this, [=](){
            //保持窗口位置一致
            this->setGeometry(ChooseScene->geometry());
            //隐藏选择关卡
            ChooseScene->hide();
            //重新显示主场景
            this->show();
        });
    });

    //准备开始按钮音效
    QSoundEffect* startSound = new QSoundEffect;
    startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    startSound->setLoopCount(1);
    startSound->setParent(this);
    /*开始按钮*/
    myPushButton* startBtn = new myPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5, this->height()*0.7);
    //监听click信号 制作点击弹起特效
    connect(startBtn, &myPushButton::clicked, [=](){
        //按压特效
        startBtn->press_zoom();
        //弹起特效
        startBtn->release_zoom();
        startSound->play();

        //延时进入选择关卡 目的：完整显示按钮弹起特效
        //延迟特定事件后执行一个函数
        QTimer::singleShot(100, this, [=](){
            //保持新窗口与本窗口矩形位置一致
            ChooseScene->setGeometry(this->geometry());
            //隐藏自身场景，显示选择关卡场景
            this->hide();
            ChooseScene->show();
        });

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* )
{
    /*绘制背景图片*/
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    /*绘制背景上图标*/
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);  //图片缩放
    painter.drawPixmap(10, 30, pix);
}
