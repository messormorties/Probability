#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
   void updateRedBalls1();
   void updateRedBalls2();
   void moveBall1to2();
   void moveBall2to1();
   void take2Balls();


private:
    Ui::MainWindow *ui;
    int totalBalls1=0, blueBalls1=0, redBalls1=0;
    int totalBalls2=0, blueBalls2=0, redBalls2=0;

    void updateProbabilitis();
    void initRandom();
    void updateText();
    int getRandom(int min, int max);
};

#endif // MAINWINDOW_H
