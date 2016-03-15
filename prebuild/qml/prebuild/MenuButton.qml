// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: menuBtn
    height: menuButtonHeight
    width: menuButtonHeight
    color: clr_back

    property alias thumbnail : imgIcon.source
    signal btnClicked();

    Image {
        id: imgIcon
        width: menuGraphicHeight
        height: menuGraphicHeight
        anchors.fill: parent
        fillMode: Image.Tile
        smooth: true
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            menuBtn.color = clr_border;
        }
        onReleased: {
            menuBtn.color = clr_back;
        }

        onClicked: {
            menuBtn.btnClicked(); //send signal to parent (Stage.qml?)
        }
    }
}
