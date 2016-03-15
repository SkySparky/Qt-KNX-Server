// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: dimmer
    width: 360
    height: 360

    property int dimmerValue : 0;       // int value
    property string dimVal : "00 00";   // 2 bytes for knx
    property string theme

    signal sendValue(int value);
    signal sendExitReq();
    signal sendSettingsReq();

    function rotateKnob(posX, posY) {
        var centerX = width/2;
        var centerY = height/2;
        var angle = Math.atan(Math.abs(posY - centerY)/Math.abs(centerX - posX)) * 180 / Math.PI;
        if (posX <= centerX && posY <= centerY) {
            angle = 180 - angle;
        }
        else if (posX < centerX && posY > centerY) {
            angle = 180 + angle;
        }
        else if (posX >= centerX && posY >= centerY) {
            angle = 360 - angle;
        }
        return angle;
    }

    Image {
        id: imgPlate
        height: dimmer.height
        width: dimmer.height
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        fillMode: Image.PreserveAspectFit
        smooth: true
        source: theme + "/dimmer_plate.png"
    }

    Image {
        id: imgKnob
        height: dimmer.height
        width: dimmer.height
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        fillMode: Image.PreserveAspectFit
        smooth: true
        source: theme + "/dimmer_knob.png"
    }

    MouseArea {
        id: knobArea
        width: dimmer.width
        height: dimmer.height
        anchors.left: dimmer.left
        anchors.top: dimmer.top

        onPressed: {
            textBox.visible = true;
        }
        onPositionChanged: {
            var tmpRot = rotateKnob(mouseX, mouseY);

            if (tmpRot > 0 && tmpRot < 240) {
                imgKnob.rotation = 240 - tmpRot;
                dimmerValue = 240 - tmpRot;
            }
            else if (tmpRot >= 240) {
                if (tmpRot >= 343) {
                    imgKnob.rotation = 240 + 360 - tmpRot;
                    dimmerValue = 240 + 360 - tmpRot;
                    if(dimmerValue > 255) dimmerValue = 255;
                }
            }
            var result = dimmerValue * 100 / 255
            txtValue.text = result.toFixed(0) + "%";
        }
        onReleased: {
            var hex = dimmerValue.toString(16).toUpperCase();
            dimVal = "00 " + ((dimmerValue < 16) ? "0" + hex : hex);
            console.log("dimVal: " + dimVal);
            sendValue(dimVal);
            textBox.visible = false;
        }
    }

    Rectangle {
        id: textBox
        x: 20
        y: 25

        width: imgPlate.height / 3
        height: imgPlate.width / 8
        color: "silver"
        radius: 10
        smooth: true
        border.width: 2
        border.color: "black"
        visible: false
        Text {
            id: txtValue
            font.pointSize: imgPlate.width*30/360
            anchors.horizontalCenter: textBox.horizontalCenter
            anchors.verticalCenter: textBox.verticalCenter
        }
    }

    Image {
        id: exit
        height: 60
        width: 60
        source: theme + "/back.png"
        anchors.left: dimmer.left
        anchors.bottom: dimmer.bottom

        MouseArea {
            anchors.fill: parent
            onPressed: {
                sendExitReq();
            }
        }
    }

    Image {
        id: options
        height: 60
        width: 60
        source: theme + "/settings.png"
        anchors.right: dimmer.right
        anchors.bottom: dimmer.bottom

        MouseArea {
            anchors.fill: parent
            onPressed: {
                sendSettingsReq();
            }
        }
    }

}
