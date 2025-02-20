#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <ctime>
#include <cstdlib>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIntValidator *validator = new QIntValidator(0, 9999, this);
    ui->totalballs1->setValidator(validator);
    ui->blueBalls1->setValidator(validator);
    ui->totalballs2->setValidator(validator);
    ui->blueBalls2->setValidator(validator);
    ui->redBalls2->setValidator(validator);
    ui->redBalls1->setValidator(validator);

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
    QTimer::singleShot(100, this, SLOT(showStartupInfo()));
    updateProbabilitis();
}

void MainWindow::showStartupInfo() {
    QMessageBox::information(this, "Внимание", "Введите общее количество шаров и число синих шаров для корзин, число красных шаров будет расчитано автоматически");
}

void MainWindow::updateText() {
    ui->totalballs1->blockSignals(true);
    ui->blueBalls1->blockSignals(true);
    ui->redBalls1->blockSignals(true);

    ui->totalballs2->blockSignals(true);
    ui->blueBalls2->blockSignals(true);
    ui->redBalls2->blockSignals(true);

    ui->totalballs1->setText(QString::number(totalBalls1));
    ui->blueBalls1->setText(QString::number(blueBalls1));
    ui->redBalls1->setText(QString::number(redBalls1));

    ui->totalballs2->setText(QString::number(totalBalls2));
    ui->blueBalls2->setText(QString::number(blueBalls2));
    ui->redBalls2->setText(QString::number(redBalls2));

    ui->totalballs1->blockSignals(false);
    ui->blueBalls1->blockSignals(false);
    ui->redBalls1->blockSignals(false);

    ui->totalballs2->blockSignals(false);
    ui->blueBalls2->blockSignals(false);
    ui->redBalls2->blockSignals(false);

}

void MainWindow::updateRedBalls1() {
    // для работы программы нужно ввести общее число шаров и число синих шариков, красные будут вычислены
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
     // для работы программы нужно ввести общее число шаров и число синих шариков, красные будут вычислены
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


void MainWindow::initRandom(){
    std::srand(std::time(nullptr));
}

int MainWindow::getRandom(int min, int max) {
    return min+std::rand()%(max-min+1);
}

void MainWindow::moveBall1to2() {
    QString extractedFrom1="Был извлечен ";
    QString extractedFrom2="Был добавлен ";
    if (totalBalls1) {
        int color = getRandom(0,1); //0-blue, 1 - red
        if (color==0 &&blueBalls1>0) {
            blueBalls1--;
            extractedFrom1.append("синий шар");
            blueBalls2++;
        } else {
            redBalls1--;
            redBalls2++;
            extractedFrom2.append("красный шар");
        }
        totalBalls1--;
        totalBalls2++;
        updateText();
        updateProbabilitis();
        if (extractedFrom1=="Был извлечен синий шар") {
            ui->lastAction1->setText(extractedFrom1);
            ui->lastAction2->setText(extractedFrom2+"синий шар");
        }
        else {
            ui->lastAction1->setText(extractedFrom1+"красный шар");
            ui->lastAction2->setText(extractedFrom2);
        }
    }
    else {
        QMessageBox::critical(this, "Корзина №1 пуста!", "Введите количество шаров в корзине");
    }

}


void MainWindow::moveBall2to1() {
    QString extractedFrom1="Был извлечен ";
    QString extractedFrom2="Был добавлен ";
    if (totalBalls2) {
        int color = getRandom(0,1); //0-blue, 1 - red
        if (color==0 &&blueBalls2>0) {
            blueBalls2--;
            extractedFrom1.append("синий шар");
            blueBalls1++;
        } else {
            redBalls2--;
            redBalls1++;
            extractedFrom2.append("красный шар");
        }
        totalBalls2--;
        totalBalls1++;
        updateText();
        updateProbabilitis();

        if (extractedFrom1=="Был извлечен синий шар") {
            ui->lastAction2->setText(extractedFrom1);
            ui->lastAction1->setText(extractedFrom2+"синий шар");
        }
        else {
            ui->lastAction2->setText(extractedFrom1+"красный шар");
            ui->lastAction1->setText(extractedFrom2);
        }
    }
    else {
        QMessageBox::critical(this, "Корзина №2 пуста!", "Введите количество шаров в корзине");
    }

}

void MainWindow::take2Balls() {
    if (totalBalls1+totalBalls2 < 2) {
            QMessageBox::critical(this, "Не хватает шаров для извлечения!", "Добавьте шары в корзины");
            return;
        }
        QStringList extractedFrom1;
        QStringList extractedFrom2;
        int count = 2;
        while (count > 0) {
            bool takeFromBasket1 = (blueBalls1 + redBalls1 > 0) &&
                                   ((blueBalls2 + redBalls2 == 0) || getRandom(0, 1) == 0); //0-1 корзина, 1- 2 корзина

            if (takeFromBasket1) {
                if (totalBalls1==0) continue;
                bool isBlue =(blueBalls1>0)? (getRandom(0, blueBalls1 + redBalls1 - 1) < blueBalls1):false;
                if (isBlue) {blueBalls1--;
                totalBalls1--;
                extractedFrom1.append("синий");}
                else if(redBalls1>0) {
                    redBalls1--;
                    totalBalls1--;
                    extractedFrom1.append("красный");
                }
            } else {
                 if (blueBalls2 + redBalls2 == 0) continue;
                 bool isBlue = (blueBalls2 > 0) ? (getRandom(0, blueBalls2 + redBalls2 - 1) < blueBalls2) : false;
                if (isBlue) {
                    blueBalls2--;
                    totalBalls2--;
                    extractedFrom2.append("синий");
                }
                else if (redBalls2 > 0){
                redBalls2--;
                totalBalls2--;
                extractedFrom2.append("красный");
                }
            }
            count--;
        }
        updateText();
        updateProbabilitis();

        auto formatExtractionMessage = [](const QStringList& extracted) -> QString {
                if (extracted.isEmpty()) {
                    return "Шары не извлекались";
                } else if (extracted.size() == 1) {
                    return "Был извлечён " + extracted.first() + " шар";
                } else if (extracted.size() == 2 && extracted[0] == extracted[1]) {
                    return "Были извлечены 2 " + extracted[0] + "х шара";
                } else {
                    return "Были извлечены " + extracted[0] + " и " + extracted[1] + " шар";
                }
            };

            ui->lastAction1->setText(formatExtractionMessage(extractedFrom1));
            ui->lastAction2->setText(formatExtractionMessage(extractedFrom2));
}

void::MainWindow::updateProbabilitis() {
    auto probability = [](double total, double color) -> double {
           return (total > 0) ? (color / total) : 0.0;
       };

       // Обновляем вероятности достать конкретный цвет из каждой корзины
       ui->blueProb1->setText(QString::number(probability(totalBalls1, blueBalls1) * 100.0, 'f', 2) );
       ui->redProb1->setText(QString::number(probability(totalBalls1, redBalls1) * 100.0, 'f', 2) );

       ui->blueProb2->setText(QString::number(probability(totalBalls2, blueBalls2) * 100.0, 'f', 2) );
       ui->redProb2->setText(QString::number(probability(totalBalls2, redBalls2) * 100.0, 'f', 2) );

       // Проверяем, есть ли вообще шары в корзинах
       if (totalBalls1 + totalBalls2 < 2) {
           ui->probTwoBlue->setText("0.00");
           ui->probTwoRed->setText("0.00");
           ui->probMixed->setText("0.00");
           return;
       }

       // Общие вероятности
       double total = totalBalls1+totalBalls2;

       // Вероятность достать два синих шара
       double pBlueBlue = ((blueBalls1+blueBalls2)/(total))*((blueBalls1+blueBalls2-1)/(total-1));
       double pRedRed = ((redBalls1+redBalls2)/(total))*((redBalls1+redBalls2-1)/(total-1));
       double pMixed =1.0-pBlueBlue-pRedRed;

       // Обновление интерфейса
       ui->probTwoBlue->setText(QString::number(pBlueBlue * 100.0, 'f', 2) );
       ui->probTwoRed->setText(QString::number(pRedRed * 100.0, 'f', 2) );
       ui->probMixed->setText(QString::number(pMixed * 100.0, 'f', 2));
}

MainWindow::~MainWindow()
{
    delete ui;
}
