#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QAction>
#include <QtDebug>
#include <QMediaMetaData>
#include <QPushButton>
#include <windows.h>
#include <QFile>
#include <QPalette>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Playlist = new QMediaPlaylist(this);
    music = new QMediaPlayer(this);
    //背景图
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/images/BackGround.jpg")));
    setPalette(pal);
    //打开歌单
    connect(ui->actionopen, &QAction::triggered, this, &MainWindow::addSong);
    //开始播放
    connect(ui->start,&QPushButton::clicked, this, &MainWindow::playSong);
    //暂停
    connect(ui->pause,&QPushButton::clicked,this,&MainWindow::suspendSong);
    //上下一曲
    connect(ui->previous,&QPushButton::clicked, this, &MainWindow::preSong);
    connect(ui->next, &QPushButton::clicked, this, &MainWindow::nextSong);
}

//添加音乐文件到播放列表
void MainWindow::addSong(){
    //songFileName为路径加音乐名 songName为音乐名
    QString songFileName,songName;
    //音乐信息
    QFileInfo info;
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("打开文件夹"),"",tr("music(*.mp3)"));
    for(auto i = 0; i < fileNames.size(); i++){
        //播放列表显示的是音乐名，但实际存放的是文件路径
        Playlist->addMedia(QUrl::fromLocalFile(fileNames.at(i)));
        songFileName = fileNames.at(i);
        info = QFileInfo(songFileName);
        songName = info.fileName();
        ui->SongName->append(songName);
    }
    music->setPlaylist(Playlist);

}
//播放音乐
void MainWindow::playSong(){
    if(Playlist->mediaCount() == 0){
        ui->words->setText("请导入歌单...");
        return;
    }
    ui->words->clear();
    //音量设置
    music->setVolume(60);
    //播放音乐
    music->play();
    QString name = music->metaData(QMediaMetaData::Title).toString();
    QString author = music->metaData(QMediaMetaData::Author).toString();
    ui->words->append("正在播放：" + name + "-" + author);
    showWords(name);
}
//暂停音乐
void MainWindow::suspendSong(){
    music->stop();
}
//下一曲
void MainWindow::nextSong(){
    int currentIndex = Playlist->currentIndex();
    if(++currentIndex == Playlist->mediaCount()){
        currentIndex = 0;
    }
    Playlist->setCurrentIndex(currentIndex);
    music->play();
}
//上一曲
void MainWindow::preSong(){
    Playlist->previous();
    music->play();
}
//歌词
void MainWindow::showWords(QString &name){
    QString WordsOfSong;
    if(name == "梦想天空分外蓝"){
        QString road = ":/files/dream.txt";
        QFile file(road);

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "Can't open the file!" << endl;
        }
        while(!file.atEnd()){
            QByteArray line = file.readLine();
            QString str(line);
            qDebug() << str;
            WordsOfSong.append(str);
        }
        ui->words->append(WordsOfSong);
    }
    else{
        ui->words->append("no words");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

