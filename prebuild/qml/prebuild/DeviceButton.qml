import QtQuick 1.1

//DEV_SWITCH    : 0
//DEV_DIMMER    : 1
//DEV_RGB       : 2
//DEV_SHUTTER   : 3
//DEV_TAGBTN    : 4

Rectangle {
    id: deviceButton
    height: stage.buttonHeight
    width: stage.width - 6
    radius: 2
    x: 0
    y: 0
    color: clr_back; border.color: clr_border

    property alias btnWidth: deviceButton.width
    property alias btnHeight: deviceButton.height
    property alias btnX: deviceButton.x
    property alias btnY: deviceButton.y
    property alias btnImage: btn_Image.source
    property alias btnImageBack : btn_ImageBack.source

    property int devIndex
    property string devDescription
    property int devType        //keeps device type
    property string devAddress  //keeps device address
    property string devAddress1  //keeps device address
    property string devAddress2  //keeps device address
    property string devAddress3  //keeps device address
    property string devAddress4  //keeps device address
    property string devStatusAddress
    property string devStatusAddress1
    property string devStatusAddress2
    property string devStatusAddress3
    property string devStatusAddress4
    property string devValue
    property string devValue1
    property string devValue2
    property string devValue3
    property string devValue4

    signal updateDeviceValue()      //immediate value update without calling switch object
    signal deviceButtonClicked()    //signal to send to parent
    signal updateDevValue(string newVal)

    function onValueChange() {
        if (devType == 0) {
            if (devValue == "00")
                btn_Image.source = resourceBase + "switch_off" + resourceResolution;
            else
                btn_Image.source = resourceBase + "switch_on" + resourceResolution;
        }
        //else if (devType == 1) btn_Image.source = devTheme + "/dimmer.png";
        //else if (devType == 2) btn_Image.source = devTheme + "/rgb.png";
    }

    //if the device type is changed then update the thumbnail
    onDevTypeChanged : {
        if (devType == 0)
            btn_Image.source = resourceBase + "switch_off" + resourceResolution;
        else if (devType == 1)
            btn_Image.source = resourceBase + "dimmer" + resourceResolution;
        else if (devType == 2)
            btn_Image.source = resourceBase + "rgb" + resourceResolution;
        else if (devType == 3)
            btn_Image.source = resourceBase + "shutters_N" + resourceResolution;
        else if (devType == 4)
            btn_Image.source = resourceBase + "folder" + resourceResolution;
        else if (devType == 5)
            btn_Image.source = resourceBase + "temp" + resourceResolution;
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: parent.btnImageBack = resourceBase + "btn1dn"  + resourceResolution
        onExited: parent.btnImageBack = resourceBase + "btn1up"  + resourceResolution
        onCanceled: parent.btnImageBack = resourceBase + "btn1up"  + resourceResolution
        onClicked: {
            deviceButton.deviceButtonClicked(); //send signal to parent (Stage.qml?)
        }
    }
    Image{
        id: btn_ImageBack
        height: deviceButton.height
        source: resourceBase + "btn1up" + resourceResolution
        fillMode: Image.Tile
        anchors.fill: parent
        anchors.margins: 1;
    }

    Image {
        id: btn_Image
        height: stage.graphicHeight
        width: stage.graphicHeight
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin:  stage.buttonHeight - stage.graphicHeight
        MouseArea {
             id: mouseAreaSmall
             hoverEnabled: false
             anchors.fill: parent
             onClicked: {
                 if (devType == 0) {    //catch thumbnail click for switches only
                     updateDevValue(devValue == "00"? "01":"00");
                 }
                 else
                     deviceButton.deviceButtonClicked(); //send signal to parent (Stage.qml?)
             }
        }
    }
    Text {
        id: btn_text
        x: parent.height + 5
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width; color: clr_text
        text: devDescription;
        font.pixelSize: buttonCaptionSize
    }
}

