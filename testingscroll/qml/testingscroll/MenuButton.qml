// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: menuButton

    property alias btnWidth: menuButton.width
    property alias btnHeight: menuButton.height
    property alias btnLabel: btnText.text
    property alias btnImage: btnImage.source

    signal clicked

    color: "#6b5e5e"
    border.color: "silver"
    radius: 10

    gradient: mouseOut

    Gradient {
        id: mouseOver
        GradientStop { position: 0.0; color: "black" }
        GradientStop { position: 1.0; color: "#6b5e5e" }
    }
    Gradient {
        id: mouseOut
        GradientStop { position: 0.0; color: "#6b5e5e" }
        GradientStop { position: 1.0; color: "black" }
    }
    Gradient {
        id: mousePress
        GradientStop { position: 0.0; color: "steelblue" }
        GradientStop { position: 1.0; color: "#6b5e5e" }
    }

    Image {
        id: btnImage
        height: menuButton.height
        width: menuButton.height
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        fillMode: Image.PreserveAspectFit
        smooth: true

        //rotation: 10
    }
    Text {
        id: btnText
        color: "silver"
        anchors.left: btnImage.right
        anchors.leftMargin: 10
        anchors.verticalCenter: btnImage.verticalCenter
        font.pointSize: 32
        text: qsTr("Action")
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onEntered: {
           menuButton.gradient = mouseOver
        }
        onExited: {
            menuButton.gradient = mouseOut
        }
        onPressed: {
            menuButton.gradient = mousePress
        }
        onReleased: {
            menuButton.gradient = mouseOver
        }
        onClicked: {
            menuButton.clicked();
        }
    }
}
