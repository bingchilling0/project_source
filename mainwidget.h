#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "widget.h"
#include <QPushButton>
#include <QComboBox>
#include <QColorDialog>
#include <QLabel>
#include <QVideoWidget>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

protected slots:
    void buttonClick();
    void boxClick();
    void colorClick();
    void cpcl();
    void saveClick();
    void startClick();
    void loadClick();
    void penClick();
    void eraserClick();

private:
    Ui::MainWidget *ui;
    Widget* widget;
    QPushButton* button;
    QComboBox* sizeBox;
    QPushButton* colorChoose;
    QColorDialog* colorPicker;
    QPushButton* save;
    QPushButton *start;
    QComboBox* mode;
    QLabel *bgimage;
    QSize screenSize;
    QPushButton* loadBg;
    int margin = 162;
    QPushButton* pen;
    QPushButton* eraser;
};
#endif // MAINWIDGET_H
