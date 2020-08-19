import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import Drawing 1.0
import TabletWindow 1.0

TabletWindow {
    visible: true
    width: 2000
    height: 1000
    title: qsTr("Hello World")
    tabletCanvas: canvas

    DrawingCanvas{
        id: canvas
        width: 2000; height: 1000
        Component.onCompleted: canvas.initiateBuffer()
    }
}
