/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qeglfswindowsurface.h"

#include <QtGui/QPlatformGLContext>

#include <QtOpenGL/private/qgl_p.h>
#include <QtOpenGL/private/qglpaintdevice_p.h>

QT_BEGIN_NAMESPACE

class QEglFSPaintDevice : public QGLPaintDevice
{
public:
    QEglFSPaintDevice(QEglFSScreen *screen, QWidget *widget)
        :QGLPaintDevice(), m_screen(screen)
    {
    #ifdef QEGL_EXTRA_DEBUG
        qWarning("QEglPaintDevice %p, %p, %p",this, screen, widget);
    #endif
    }

    QSize size() const { return m_screen->geometry().size(); }
    QGLContext* context() const { return QGLContext::fromPlatformGLContext(m_screen->platformContext());}

    QPaintEngine *paintEngine() const { return qt_qgl_paint_engine(); }

    void  beginPaint(){
        QGLPaintDevice::beginPaint();
    }
private:
    QEglFSScreen *m_screen;
    QGLContext *m_context;
};


QEglFSWindowSurface::QEglFSWindowSurface( QEglFSScreen *screen, QWidget *window )
    :QWindowSurface(window)
{
#ifdef QEGL_EXTRA_DEBUG
    qWarning("QEglWindowSurface %p, %p", window, screen);
#endif
    m_paintDevice = new QEglFSPaintDevice(screen,window);
}

void QEglFSWindowSurface::flush(QWidget *widget, const QRegion &region, const QPoint &offset)
{
    Q_UNUSED(widget);
    Q_UNUSED(region);
    Q_UNUSED(offset);
#ifdef QEGL_EXTRA_DEBUG
    qWarning("QEglWindowSurface::flush %p",widget);
#endif
    widget->platformWindow()->glContext()->swapBuffers();
}

void QEglFSWindowSurface::resize(const QSize &size)
{
    Q_UNUSED(size);
}

QT_END_NAMESPACE
