// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: dimmer
    width: 360
    height: 360
    color: "black"

    property int centerX : width/2
    property int centerY : height/2
    property int dimmerValue : 0;

    signal sendValue(int value);

    function rotateKnob(posX, posY) {
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
        source: "./dimmer_plate.png"
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
        source: "./dimmer_knob.png"
    }
    MouseArea {
        id: knobArea
        anchors.fill: parent
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
        }
        onReleased: {
            sendValue(dimmerValue);
            console.log("dimmerValue: " + dimmerValue);
        }
    }

}
