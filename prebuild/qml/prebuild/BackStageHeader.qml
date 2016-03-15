// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id:rect1
    property alias hdrText: text1.text
    x:0; y:2; z: 10
    border.width: 2
    radius: 5
    color: clr_header_back; border.color: clr_header_border; height: scrollOffsetY - 5; width: parent.width - 5

    Text {
        id: text1
        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 40
        font.bold: true; font.italic: true
        font.pixelSize: buttonCaptionSize; color: clr_header_text
        text: qsTr(hdrText)
    }
}
