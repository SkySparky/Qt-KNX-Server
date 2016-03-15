// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//shutter is always on the screen but it's hidden

Item {
    id: btnShutter
    width: (parent.width > parent.height) ? parent.height - 10 : parent.width - 10;
    height: width

    property int size: 0                // 0: size small, 1: size large
    property int devIndex
    property string shGroupAddrStep     //shutter current group addr
    property string shGroupAddrVal

    signal btnClicked(string shGroupAddr, string shValue);
    signal sendExitReq();
    signal sendSettingsReq();

    //button image
    Image {
        id: imgShutter
        height: btnShutter.width
        width: btnShutter.height
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        smooth: true
        source: resourceBase + "shutters_N.png"
        //button mouse area
        MouseArea {
            id: shutterFU
            anchors.right: imgShutter.right
            anchors.top: imgShutter.top
            width: imgShutter.width/2
            height: imgShutter.height/2
            onPressed: {
                imgShutter.source = resourceBase + "shutters_FU.png";
                btnClicked(shGroupAddrVal, "00");
            }
            onReleased: {
                imgShutter.source = resourceBase + "shutters_N.png";
            }
        }
        MouseArea {
            id: shutterFD
            anchors.right: imgShutter.right
            anchors.bottom: imgShutter.bottom
            anchors.top: shutterFU.bottom
            width: imgShutter.width/2
            onPressed: {
                imgShutter.source = resourceBase + "shutters_FD.png";
                btnClicked(shGroupAddrVal, "01");
            }
            onReleased: {
                imgShutter.source = resourceBase + "shutters_N.png";
            }
        }
        MouseArea {
            id: shutterU
            anchors.left: imgShutter.left
            anchors.top: imgShutter.top
            width: imgShutter.width/2
            height: imgShutter.height/2
            onPressed: {
                imgShutter.source = resourceBase + "shutters_U.png";
                btnClicked(shGroupAddrStep, "00");
            }
            onReleased: {
                imgShutter.source = resourceBase + "shutters_N.png";
            }
        }
        MouseArea {
            id:shutterD
            anchors.left: imgShutter.left
            anchors.bottom: imgShutter.bottom
            anchors.top: shutterU.bottom
            width: imgShutter.width/2
            onPressed: {
                imgShutter.source = resourceBase + "shutters_D.png";
                btnClicked(shGroupAddrStep, "01");
            }
            onReleased: {
                imgShutter.source = resourceBase + "shutters_N.png";
            }
        }
    }

    //button for return to list
    Image {
        id: exit
        height: 80
        width: 80
        source: resourceBase + "back" + resourceResolution
        anchors.left: btnShutter.left
        anchors.top: btnShutter.bottom
        anchors.topMargin: 10

        MouseArea {
            anchors.fill: parent
            onPressed: {
                sendExitReq();
            }
        }
    }

    //button for edit the object
    Image {
        id: options
        height: 80
        width: 80
        source: resourceBase + "settings" + resourceResolution
        anchors.right: btnShutter.right
        anchors.top: btnShutter.bottom
        anchors.topMargin: 10

        MouseArea {
            anchors.fill: parent
            onPressed: {
                sendSettingsReq();
            }
        }
    }

}
