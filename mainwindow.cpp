#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <ctime>
#include <cstdlib>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->totalballs1, &QLineEdit::textChanged, this, &MainWindow::updateRedBalls1);
    connect(ui->blueBalls1, &QLineEdit::textChanged, this, &MainWindow::updateRedBalls1);
    connect(ui->totalballs2, &QLineEdit::textChanged, this, &MainWindow::updateRedBalls2);
    connect(ui->blueBalls2, &QLineEdit::textChanged, this, &MainWindow::updateRedBalls2);

    connect(ui->totalballs1, &QLineEdit::textChanged, this, &MainWindow::updateProbabilitis);
    connect(ui->blueBalls1, &QLineEdit::textChanged, this, &MainWindow::updateProbabilitis);
    connect(ui->totalballs2, &QLineEdit::textChanged, this, &MainWindow::updateProbabilitis);
    connect(ui->blueBalls2, &QLineEdit::textChanged, this, &MainWindow::updateProbabilitis);

    connect(ui->move1to2, &QPushButton::clicked, this, &MainWindow::moveBall1to2);
    connect(ui->move2to1, &QPushButton::clicked, this, &MainWindow::moveBall2to1);
    connect(ui->extract2balls, &QPushButton::clicked, this, &MainWindow::take2Balls);

    updateProbabilitis();
}

void MainWindow::updateRedBalls1() {
    totalBalls1=ui->totalballs1->text().toInt();
    blueBalls1 = ui->blueBalls1->text().toInt();
    redBalls1 = totalBalls1-blueBalls1;
    if (redBalls1<0) {
        ui->redBalls1->setText(0);
        QMessageBox::critical(this, "Отрицательное значение", "Введите корректные значения количества шаров");
        ui->blueBalls1->clear();
    }
    else {
    ui->redBalls1->setText(QString::number(redBalls1));
    }
}

void MainWindow::updateRedBalls2() {
    totalBalls2=ui->totalballs2->text().toInt();
    blueBalls2 = ui->blueBalls2->text().toInt();
    redBalls2 = totalBalls2-blueBalls2;
    if (redBalls2<0) {
        ui->redBalls2->setText(0);
        QMessageBox::critical(this, "Отрицательное значение", "Введите корректные значения количества шаров");
        ui->blueBalls2->clear();
    }
    else {
    ui->redBalls2->setText(QString::number(redBalls2));
    }
}


void MainWindow::updateText() {
    ui->blueBalls1->setText(QString::number(blueBalls1));
    ui->blueBalls2->setText(QString::number(blueBalls2));
    ui->redBalls1->setText(QString::number(redBalls1));
    ui->redBalls2->setText(QString::number(redBalls2));
}

//void MainWindow::updatetotalBalls1() {

//}

//void MainWindow::updatetotalBalls2() {

//}

void MainWindow::initRandom(){
    std::srand(std::time(nullptr));
}

int MainWindow::getRandom(int min, int max) {
    return min+std::rand()%(max-min+1);
}

void MainWindow::moveBall1to2() {
    if (totalBalls1) {
        int color = getRandom(0,1); //0-blue, 1 - red
        if (color==0 &&blueBalls1>0) {
            blueBalls1--;
            ui->blueBalls1->setText(QString::number( blueBalls1));
            blueBalls2++;
            ui->blueBalls2->setText(QString::number(blueBalls2));
        } else {
            redBalls1--;
            ui->redBalls1->setText(QString::number(redBalls1));
            redBalls2++;
            ui->redBalls2->setText(QString::number(redBalls2));
        }
        totalBalls1--;
        totalBalls2++;
        ui->totalballs1->setText(QString::number(totalBalls1));
        ui->totalballs2->setText(QString::number(totalBalls2));
        updateProbabilitis();
    }
    else {
        QMessageBox::critical(this, "Корзина №1 пуста!", "Введите количесвто шаров в корзине");
    }

}


void MainWindow::moveBall2to1() {
    if (totalBalls2) {
        int color = getRandom(0,1); //0-blue, 1 - red
        if (color==0 &&blueBalls2>0) {
            blueBalls2--;
            ui->blueBalls2->setText(QString::number( blueBalls2));
            blueBalls1++;
            ui->blueBalls1->setText(QString::number(blueBalls1));
        } else {
            redBalls2--;
            ui->redBalls2->setText(QString::number(redBalls2));
            redBalls1++;
            ui->redBalls1->setText(QString::number(redBalls1));
        }
        totalBalls2--;
        totalBalls1++;
        ui->totalballs1->setText(QString::number(totalBalls1));
        ui->totalballs2->setText(QString::number(totalBalls2));
        updateProbabilitis();
    }
    else {
        QMessageBox::critical(this, "Корзина №1 пуста!", "Введите количесвто шаров в корзине");
    }

}

void MainWindow::take2Balls() {
    if (totalBalls1+totalBalls2 < 2) {
            QMessageBox::warning(this, "Ошибка", "Недостаточно шаров для извлечения.");
            return;
        }

        int count = 2;
        while (count > 0) {
            bool takeFromBasket1 = (blueBalls1 + redBalls1 > 0) &&
                                   ((blueBalls2 + redBalls2 == 0) || getRandom(0, 1) == 0);

            if (takeFromBasket1) {
                bool isBlue = getRandom(0, blueBalls1 + redBalls1 - 1) < blueBalls1;
                if (isBlue) {blueBalls1--;
                totalBalls1--;}
                else {redBalls1--;
                totalBalls1--;}
            } else {
                bool isBlue = getRandom(0, blueBalls2 + redBalls2 - 1) < blueBalls2;
                if (isBlue) {blueBalls2--;
                    totalBalls2--;
                }
                else {redBalls2--;
                totalBalls2--;
                }
            }
            count--;
        }
        ui->totalballs1->setText(QString::number(totalBalls1));
        ui->totalballs2->setText(QString::number(totalBalls2));
        ui->blueBalls1->setText(QString::number(blueBalls1));
        ui->blueBalls2->setText(QString::number(blueBalls2));
       // ui->redBalls1->setText(QString::number(redBalls1));
        //ui->redBalls2->setText(QString::number(redBalls2));

        updateProbabilitis();
}

void::MainWindow::updateProbabilitis() {
    auto probability = [](double total, double color) -> double {
           return (total > 0) ? (color / total) : 0.0;
       };

       // Обновляем вероятности достать конкретный цвет из каждой корзины
       ui->blueProb1->setText(QString::number(probability(totalBalls1, blueBalls1) * 100.0, 'f', 3) + "%");
       ui->redProb1->setText(QString::number(probability(totalBalls1, redBalls1) * 100.0, 'f', 3) + "%");

       ui->blueProb2->setText(QString::number(probability(totalBalls2, blueBalls2) * 100.0, 'f', 3) + "%");
       ui->redProb2->setText(QString::number(probability(totalBalls2, redBalls2) * 100.0, 'f', 3) + "%");

       // Проверяем, есть ли вообще шары в корзинах
       if (totalBalls1 + totalBalls2 < 2) {
           ui->probTwoBlue->setText("0.00%");
           ui->probTwoRed->setText("0.00%");
           ui->probMixed->setText("0.00%");
           return;
       }



       // Общие вероятности
       double total = totalBalls1+totalBalls2;

       // Вероятность достать два синих шара
       double pBlueBlue = ((blueBalls1+blueBalls2)/(total))*((blueBalls1+blueBalls2-1)/(total-1));
       double pRedRed = ((redBalls1+redBalls2)/(total))*((redBalls1+redBalls2-1)/(total-1));
       double pMixed =1.0-pBlueBlue-pRedRed;

       // Обновление интерфейса
       ui->probTwoBlue->setText(QString::number(pBlueBlue * 100.0, 'f', 2) + "%");
       ui->probTwoRed->setText(QString::number(pRedRed * 100.0, 'f', 2) + "%");
       ui->probMixed->setText(QString::number(pMixed * 100.0, 'f', 2) + "%");
}

MainWindow::~MainWindow()
{
    delete ui;
}
