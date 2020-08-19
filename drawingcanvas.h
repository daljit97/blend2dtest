#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>
#include <QElapsedTimer>

#include <blend2d.h>


#include <iostream>

class DrawingCanvas : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(bool drawing READ drawing WRITE setDrawing NOTIFY drawingChanged)
public:
    explicit DrawingCanvas(QQuickItem *parent = nullptr);
    bool drawing() const;

    Q_INVOKABLE void initiateBuffer();

public slots:
    void setDrawing(bool drawing);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paint(QPainter *painter);

signals:
    void drawingChanged(bool drawing);

private:
    void drawOnBuffer(QPointF pos);
    bool m_drawing;
    QImage m_buffer;
    QPointF m_lastPoint;
    QRect m_updateRect;
    BLImage m_buffer2d;
    QPolygonF m_points;
    QElapsedTimer timer;
};
#endif // DRAWINGCANVAS_H
