#include "qoglw.h"

QOGLW::QOGLW(QWidget *parent) : QOpenGLWidget(parent)
{
    //QSurfaceFormat format;
    //format.setDepthBufferSize(24);
    //setFormat(format);
}

void QOGLW::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void QOGLW::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(60.0f, w / float(h), 0.01f, 1000.0f);
}

void QOGLW::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //...
}
