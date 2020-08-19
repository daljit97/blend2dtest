#pragma once

#include <QObject>
#include <QQuickWindow>

#include "drawingcanvas.h"
///
/// \brief The TabletWindow class delivers tablet events to the canvas.
/// In order to get the tablet events from the device and then
/// deliver them to our wet canvas, we need to manually handle them
/// in a QQuickWindow. This should be solved in Qt 6, where the events
/// can be handled directly within a QQuickItem.
///
class TabletWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(DrawingCanvas* tabletCanvas READ tabletCanvas WRITE setTabletCanvas NOTIFY tabletCanvasChanged)

public:
    TabletWindow();

    DrawingCanvas* tabletCanvas() const;
    /**
     * @brief dp
     * @param value is the value in pixels
     * @return a device independent pixel based on the dpi of the screen
     */
    Q_INVOKABLE double dp(double value);

public slots:
    void setTabletCanvas(DrawingCanvas* tabletCanvas);

signals:
    void tabletCanvasChanged(DrawingCanvas* tabletCanvas);

protected:
    void tabletEvent(QTabletEvent *event) override;
private:
    DrawingCanvas* m_tabletCanvas = nullptr;
    double m_scaleFactor = 1.0;
};
