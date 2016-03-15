// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: menuBtn
    height: 40
    width: 100
    color: "#6b5e5e"
    border.color: "silver"
    radius: 5

    property alias thumbnail : imgIcon.source
    property alias title : txtTitle.text
    signal btnClicked();

    Image {
        id: imgIcon
        height: menuBtn.height
        width: menuBtn.height
        anchors.top: menuBtn.top
        anchors.topMargin: 3
        anchors.left: menuBtn.left
        anchors.leftMargin: 3
        anchors.bottom: menuBtn.bottom
        anchors.bottomMargin: 3
        fillMode: Image.PreserveAspectFit
        smooth: true
    }

    Text {
        id: txtTitle
        color: "silver"
        anchors.left: imgIcon.right
        anchors.leftMargin: 1
        anchors.verticalCenter: imgIcon.verticalCenter
        font.pointSize: (16*menuBtn.height)/60
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            menuBtn.color = "#D3CFCF";
        }
        onReleased: {
            menuBtn.color = "#6b5e5e";
        }

        onClicked: {
            menuBtn.btnClicked(); //send signal to parent (Stage.qml?)
        }
    }
}
