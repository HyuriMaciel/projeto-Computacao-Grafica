#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *event);

    int lineColorR, lineColorG, lineColorB;
    int backColorR, backColorG, backColorB;
    int lineS = 1;
    bool bresenham;
    bool reset;

private:
    QTimer timer;
};

#endif // GLWIDGET_H
