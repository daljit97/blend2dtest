#include "tabletwindow.h"
#include <QScreen>

// we need a standard reference dpi to make device independent pixels
constexpr double REFERENCE_DPI = 140.0;

TabletWindow::TabletWindow()
{
}

DrawingCanvas *TabletWindow::tabletCanvas() const
{
    return m_tabletCanvas;
}

double TabletWindow::dp(double value)
{
    return value * m_scaleFactor;
}

void TabletWindow::setTabletCanvas(DrawingCanvas *tabletCanvas)
{
    if (m_tabletCanvas == tabletCanvas)
        return;

    m_tabletCanvas = tabletCanvas;
    emit tabletCanvasChanged(m_tabletCanvas);
}

void TabletWindow::tabletEvent(QTabletEvent *event)
{
    if(m_tabletCanvas != nullptr){
        // send tablet events to canvas
    }
}
