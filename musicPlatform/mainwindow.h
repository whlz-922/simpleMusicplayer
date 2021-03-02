#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    //添加音乐文件
    void addSong();
    //播放音乐
    void playSong();
    //暂停音乐
    void suspendSong();
    //上一曲
    void preSong();
    //下一曲
    void nextSong();
    //歌词显示
    void showWords(QString &name);


private:
    //播放列表
    QMediaPlaylist *Playlist;
    //初始化音乐
    QMediaPlayer *music;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
