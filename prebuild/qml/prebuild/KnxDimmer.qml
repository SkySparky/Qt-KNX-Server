// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

// File version 0.2
// Added properties for limits
//
import QtQuick 1.0
Item {
    id: dimmer
    width: (parent.width > parent.height) ? parent.height - 10 : parent.width - 10;
    height: width

    property int devIndex
    property string dimGroupAddr     //switch current group addr
    property int dimmerValue : 0;       // int value
    property string dimVal : "00 00";   // 2 bytes for knx
    property int size: 0
    property int minDegrees : 30        // No les than this value (full off position)
    property int maxDegrees : 330       // No more than this value (full ON position)
    property int neutralPositionDegrees : 0 // The position than is half way between ON and OFF position in absolute world orientation // TODO

    signal sendValue(int value);
    signal sendExitReq();
    signal sendSettingsReq();

    onDimValChanged: {
        var strVal = dimVal;
        var rVal = strVal.split(" ");
        dimmerValue = parseInt(rVal[1], 16);
        setPos(dimmerValue);
    }

    function setPos(value) {
        imgKnob.rotation =( 360 - minDegrees  - ( 360 - maxDegrees)) * value / 255 + minDegrees;
    }

    function rotateKnob(posX, posY) {
        var centerX = width/2;
        var centerY = height/2;

        // Get Cartesian coordinates
        //
        var cartX = posX - centerX;
        var cartY = centerY - posY;

        // Convert to polar coordinates
        //
        var polAngle = (Math.atan2(cartX, cartY) * 180 / Math.PI) + 180 ;   // 0 to 360 degrees
        return polAngle;
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
        source: resourceBase + "dimmer_plate.png"
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
        source: resourceBase + "dimmer_knob.png"
    }

    MouseArea {
        id: knobArea
        x: 0
        y: 0
        width: dimmer.width
        height: dimmer.height
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.left: dimmer.left
        anchors.top: dimmer.top

        onPressed: {
            textBox.visible = true;
        }
        onPositionChanged: {
            var tmpRot = rotateKnob(mouseX, mouseY);

            // Select operation based on rotation angle
            //
            // Off position:  0 - minDegrees
            //
            if (tmpRot < minDegrees ) {
                imgKnob.rotation = minDegrees;
                // dimmerValue = 240 - tmpRot;
            }
            // ON position : 0 - maxDegrees
            //
            else if (tmpRot > maxDegrees ) {
                imgKnob.rotation = maxDegrees;
            }
            // Operational position min - max degrees
            //
            else {
                imgKnob.rotation = tmpRot;
            }

            dimmerValue = 255 * ( imgKnob.rotation - minDegrees ) / ( maxDegrees - minDegrees );

            var result = dimmerValue * 100 / 255
            txtValue.text = result.toFixed(0) + "%";
        }
        onReleased: {
            var hex = dimmerValue.toString(16).toUpperCase();
            dimVal = "00 " + ((dimmerValue < 16) ? "0" + hex : hex);
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
        source: resourceBase + "back" + resourceResolution
        anchors.left: dimmer.left
        anchors.top: dimmer.bottom
        anchors.topMargin: 10

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
        source: resourceBase + "settings" + resourceResolution
        anchors.right: dimmer.right
        anchors.top: dimmer.bottom
        anchors.topMargin: 10

        MouseArea {
            anchors.fill: parent
            onPressed: {
                sendSettingsReq();
            }
        }
    }

}
