#include "drawingcanvas.h"

#include <QPainterPath>

DrawingCanvas::DrawingCanvas(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
}

bool DrawingCanvas::drawing() const
{
    return m_drawing;
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    if (!m_drawing) {
        m_drawing = true;

    }
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (m_drawing) {
        auto pos = event->pos();
        drawOnBuffer(pos);
        m_lastPoint = pos;
        m_points.append(pos);
    }
}

void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_drawing && event->buttons() == Qt::NoButton)
        m_drawing = false;
}

void DrawingCanvas::paint(QPainter *painter)
{
    painter->drawImage(this->boundingRect(), m_buffer, this->boundingRect());
    m_updateRect = QRect();
}

void DrawingCanvas::setDrawing(bool drawing)
{
    if (m_drawing == drawing)
        return;

    m_drawing = drawing;
    emit drawingChanged(m_drawing);
}


void DrawingCanvas::initiateBuffer()
{
    qDebug() << "initiating buffer";
    m_buffer = QImage(width(), height()*2, QImage::Format_ARGB32_Premultiplied);
    m_buffer.fill(Qt::transparent);

    m_buffer2d.createFromData(m_buffer.width(),
                              m_buffer.height(),
                              BL_FORMAT_PRGB32,
                              m_buffer.bits(),
                              m_buffer.bytesPerLine());
}

void DrawingCanvas::drawOnBuffer(QPointF pos)
{
    QPainter bufferPainter;
    if(!bufferPainter.begin(&m_buffer)){
        return;
    }

    BLPath path;
    BLContext ctx(m_buffer2d);
    if(m_points.length() > 2){

        auto lastPos = m_points.last();
        auto previousPos = m_points.at(m_points.length()-2);

        auto mid1 = (lastPos + previousPos)/2;
        auto mid2 = (pos + lastPos)/2;

        path.moveTo(mid1.x(), mid1.y());
        path.quadTo(m_lastPoint.x(), m_lastPoint.y(), mid2.x(), mid2.y());
    }

    // let's draw a thicker transparent path
    ctx.setStrokeWidth(1.5);
    ctx.setStrokeAlpha(0.4);
    ctx.strokePath(path);

    // then draw the actual path
    ctx.setStrokeWidth(0.5);
    ctx.setStrokeAlpha(1);
    ctx.strokePath(path);

    m_updateRect =boundingRect().toRect();

    update(m_updateRect);
}
