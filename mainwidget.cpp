#include "mainwidget.h"
#include "qpainter.h"
#include "ui_mainwidget.h"
#include <QBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QPicture>
#include <QMovie>
#include <QDebug>
#include <QScreen>
#include <QGraphicsEffect>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    screenSize = QGuiApplication::primaryScreen()->size();
    resize(screenSize);


    bgimage = new QLabel(this);
    QMovie *mov = new QMovie(":/img/img/giphy.gif");      //PLACEHOLDER
    mov->setScaledSize(QSize(rect().width(),rect().height()));
    //mov->setSpeed(20);
    bgimage->setMovie(mov);
    mov->start();

    mode = new QComboBox(this);
    mode->setFixedSize(300,50);
    mode->move(500, screenSize.height()/2-margin/2);
    mode->addItems(QStringList() << "9:16 single"
                                 << "1:1 single"
                                 << "9:16 double");

    start = new QPushButton(this);
    start->setFixedSize(120,50);
    start->move(screenSize.width()/2, screenSize.height()/2-margin/2);
    start->setText("Start from scratch");
    connect(start,SIGNAL(clicked()),SLOT(startClick()));

    loadBg = new QPushButton(this);
    loadBg->setFixedSize(100,50);
    loadBg->move(screenSize.width()/2+130, screenSize.height()/2-margin/2);
    loadBg->setText("Load a picture");
    connect(loadBg,SIGNAL(clicked()),SLOT(loadClick()));
    ui->setupUi(this);
}

void MainWidget::buttonClick(){
    widget->clear();
}

void MainWidget::boxClick(){
    widget->setSize(sizeBox->currentText().toInt());
}

void MainWidget::colorClick(){
    colorPicker->setVisible(1);
    colorPicker->show();
}

void MainWidget::cpcl(){
    widget->setColor(colorPicker->currentColor());
    QPixmap shiza(30,30);
    shiza.fill(colorPicker->currentColor());
    QIcon ico(shiza);
    colorChoose->setIcon(ico);
}

void MainWidget::saveClick(){
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save as"), "", tr("Png Files (*.png)"));
    widget->saveImage(fileName);
}

void MainWidget::startClick(){
    start->hide();
    mode->hide();
    loadBg->hide();

    widget = new Widget(this);
    widget->setMode(mode->currentText().toStdString());
    widget->setFixedWidth(mode->currentIndex()==0?((screenSize.height()-margin)/16*9):screenSize.height() - margin);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout* bLayout = new QHBoxLayout();
    bLayout->setAlignment(Qt::AlignLeft);

    button = new QPushButton("clear");
    button->setFixedSize(100,50);
    connect(button,SIGNAL(clicked()),SLOT(buttonClick()));
    bLayout->addWidget(button);

    sizeBox = new QComboBox();
    sizeBox->setFixedSize(100,50);
    sizeBox->addItems(QStringList() << "2"
                                    << "5"
                                    << "10"
                                    << "50"
                                    << "200");
    sizeBox->setCurrentIndex(2);
    connect(sizeBox,SIGNAL(currentIndexChanged(int)),SLOT(boxClick()));
    bLayout->addWidget(sizeBox);

    colorPicker = new QColorDialog(this);
    colorPicker->setCurrentColor(Qt::red);
    colorPicker->hide();
    connect(colorPicker,SIGNAL(colorSelected(const QColor &)),SLOT(cpcl()));

    colorChoose = new QPushButton();
    colorChoose->setFixedSize(100,50);
    QPixmap shiza(30,30);
    shiza.fill(colorPicker->currentColor());
    QIcon ico(shiza);
    colorChoose->setIcon(ico);
    connect(colorChoose,SIGNAL(clicked()),SLOT(colorClick()));
    bLayout->addWidget(colorChoose);

    save = new QPushButton();
    save->setFixedSize(100,50);
    save->setText("Save");
    connect(save,SIGNAL(clicked()),SLOT(saveClick()));
    bLayout->addWidget(save);

    QVBoxLayout *smallLayout = new QVBoxLayout();

    pen = new QPushButton();
    pen->setFixedSize(90,50);
    pen->setIcon(QIcon(QPixmap(":/img/img/pen.jpg")));
    connect(pen,SIGNAL(clicked()),SLOT(penClick()));
    pen->setEnabled(0);
    smallLayout->addWidget(pen);

    eraser = new QPushButton();
    eraser->setFixedSize(90,50);
    eraser->setIcon(QIcon(QPixmap(":/img/img/pen.jpg")));
    connect(eraser,SIGNAL(clicked()),SLOT(eraserClick()));
    smallLayout->addWidget(eraser);

    bLayout->addLayout(smallLayout);

    mainLayout->addLayout(bLayout);
    mainLayout->addWidget(widget);
    setLayout(mainLayout);
}

void MainWidget::loadClick(){
    startClick();
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open"), "", "Images (*.png *.jpeg *.jpg)");
    widget->setBgimage(fileName);
}

void MainWidget::penClick(){
    widget->setTool("pen");
    pen->setEnabled(0);
    eraser->setEnabled(1);
}

void MainWidget::eraserClick(){
    widget->setTool("eraser");
    pen->setEnabled(1);
    eraser->setEnabled(0);
}

MainWidget::~MainWidget()
{
    delete ui;
}

