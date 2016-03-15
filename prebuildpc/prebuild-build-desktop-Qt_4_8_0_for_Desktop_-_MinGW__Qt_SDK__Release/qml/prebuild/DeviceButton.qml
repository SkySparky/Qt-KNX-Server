import QtQuick 1.1

//DEV_SWITCH    : 0
//DEV_DIMMER    : 1
//DEV_RGB       : 2
//DEV_SHUTTER   : 3
//DEV_TAGBTN    : 4

Rectangle {
    id: deviceButton
    color: "#6b5e5e"
    border.color: "silver"
    radius: 10
    gradient: mouseOut

    property alias btnWidth: deviceButton.width
    property alias btnHeight: deviceButton.height

    property int devType        //keeps device type
    property string devAddress  //keeps device address
    property string devStatusAddress
    property string devValue
    property string devDescription
    property string devTheme

    signal updateDeviceValue()      //immediate value update without calling switch object
    signal deviceButtonClicked()    //signal to send to parent
    signal updateDevValue(string value)

    onDevAddressChanged: {} //if device address has changed externally

    onDevStatusAddressChanged: {} //if status address has changed externally

    onDevDescriptionChanged: {
        txtDescription.text = devDescription
    }

    //if the value is changed then update the thumbnail
    onDevValueChanged: {
        if (devType == 0) {
            if (devValue === "00") imgIcon.source = devTheme + "/switch_off.png";
            else imgIcon.source = devTheme + "/switch_on.png";
        }
        //else if (devType == 1) imgIcon.source = devTheme + "/dimmer.png";
        //else if (devType == 2) imgIcon.source = devTheme + "/rgb.png";
        else if (devType == 3) {
            if (devValue === "00") imgIcon.source = devTheme + "/shutters_up.png";
            else imgIcon.source = devTheme + "/shutters_up.png";
        }
    }

    //if the device type is changed then update the thumbnail
    onDevTypeChanged : {
        if (devType == 0) imgIcon.source = devTheme + "/switch_off.png";
        else if (devType == 1) imgIcon.source = devTheme + "/dimmer.png";
        else if (devType == 2) imgIcon.source = devTheme + "/rgb.png";
        else if (devType == 3) imgIcon.source = devTheme + "/shutters_dn.png";
        else if (devType == 4) imgIcon.source = devTheme + "/folder.png";
    }


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
            deviceButton.deviceButtonClicked(); //send signal to parent (Stage.qml?)
        }
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
        source: devTheme + "/switch_off.png"
        MouseArea {
             id: mouseAreaSmall
             hoverEnabled: false
             anchors.fill: parent
             onClicked: {
                 if (devType === 0) {
                     devValue = (devValue === "00") ? "01" : "00";  //toggle value
                     updateDevValue(devValue);
                 }
                 else
                     deviceButton.deviceButtonClicked(); //send signal to parent (Stage.qml?)
             }
        }
    }
    Text {
        id: txtDescription
        color: "silver"
        anchors.left: imgIcon.right
        anchors.leftMargin: 10
        anchors.verticalCenter: imgIcon.verticalCenter
        font.pointSize: 24
        text: qsTr("Description")
    }
//    Text {
//        id: txtValue
//        color: "silver"
//        anchors.right: deviceButton.right
//        width: deviceButton.height
//        anchors.leftMargin: 10
//        anchors.verticalCenter: imgIcon.verticalCenter
//        font.pointSize: 24
//        text: qsTr("ON")
//        onTextChanged: {
//            if (text == "ON") color = "green";
//            else if (text == "OFF") color = "red";
//            else color = "silver";
//        }
//    }

}

