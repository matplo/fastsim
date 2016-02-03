#ifndef QOGLW_H
#define QOGLW_H

#include <qopenglfunctions.h>
#include <qopenglwidget.h>
#include <qmatrix4x4.h>

class QOGLW : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    QOGLW(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QMatrix4x4 m_projection;
};

#endif // QOGLW_H
