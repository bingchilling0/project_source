#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    void clear();
    void setSize(int s){size = s;}
    void setColor(QColor c){color = c;}
    void saveImage(QString filename);
    void setMode(std::string s){mode = s;}
    void setBgimage(QString i){bgimage->load(i);}
    void setTool(std::string s){tool = s;}

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent*);

private:
    QPixmap* points;
    QPointF prev;
    bool isDrawing = 0;
    int size = 10;
    QColor color = Qt::red;
    std::string mode;
    QPixmap* bgimage;
    std::string tool;
};

#endif // WIDGET_H
