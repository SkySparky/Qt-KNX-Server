import QtQuick 1.1

//DEV_SWITCH    : 0
//DEV_DIMMER    : 1
//DEV_RGB       : 2
//DEV_SHUTTER   : 3

Rectangle {
    id: deviceButton

    property alias btnWidth: deviceButton.width
    property alias btnHeight: deviceButton.height

    property int devType        //keeps device type
    property string devAddress  //keeps device address
    property string devValue
    property string devDescription
    property string devTheme

    signal clicked()

    onDevAddressChanged: {
        //console.log("new ga: " + devAddress);
    }

    onDevValueChanged: {
        txtValue.text = devValue
    }

    onDevDescriptionChanged: {
        txtDescription.text = devDescription
    }

    onDevTypeChanged : {
        if (devType == 0) imgIcon.source = "./images/" + devTheme + "/switch_off.png";
        else if (devType == 1) imgIcon.source = "./images/" + devTheme + "/dimmer.png";
        else if (devType == 2) imgIcon.source = "./images/" + devTheme + "/rgb.png";
        else if (devType == 3) imgIcon.source = "./images/" + devTheme + "/shutters_dn.png";
    }

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
        id: imgIcon
        height: deviceButton.height
        width: deviceButton.height
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        fillMode: Image.PreserveAspectFit
        smooth: true
        source: "./images/" + devTheme + "/switch_off.png"
        //rotation: 10
    }
    Text {
        id: txtDescription
        color: "silver"
        anchors.left: imgIcon.right
        anchors.leftMargin: 10
        anchors.verticalCenter: imgIcon.verticalCenter
        font.pointSize: 28
        text: qsTr("Description")
    }
    Text {
        id: txtValue
        color: "silver"
        anchors.right: deviceButton.right
        width: deviceButton.height
        anchors.leftMargin: 10
        anchors.verticalCenter: imgIcon.verticalCenter
        font.pointSize: 24
        text: qsTr("ON")
        onTextChanged: {
            if (text == "ON") color = "green";
            else if (text == "OFF") color = "red";
            else color = "silver";
        }
    }

    Loader {
        id: loader
        //anchors.fill: parent
        visible: source != ""
    }

    states: [
        State {
            name: "switch"
            PropertyChanges {
                target: loader
                source: "switch.qml"
            }
        },
        State {
            name: "knob"
            PropertyChanges {
                target: loader
                source: "knob.qml"
            }
        }
    ]

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onEntered: {
           deviceButton.gradient = mouseOver
        }
        onExited: {
            deviceButton.gradient = mouseOut
        }
        onPressed: {
            deviceButton.gradient = mousePress
        }
        onReleased: {
            deviceButton.gradient = mouseOver
        }
        onCanceled: {
            deviceButton.gradient = mouseOver
        }

        onClicked: {
            deviceButton.clicked();
            deviceButton.state = "knob";
            //control.source = "./knob.qml";
        }
    }
}

