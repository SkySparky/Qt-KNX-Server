// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//Switch is always on the screen but it's hidden

Item {
    id: btnSwitch
    width: (parent.width > parent.height) ? parent.height - 10 : parent.width - 10;
    height: width
    state: "off"

    property int size: 0         // 0: size small, 1: size large
    property string swGroupAddr     //switch current group addr
    property string swValue         //switch current value
    property int devIndex

    signal updateSwValue(string value);
    signal sendExitReq();
    signal sendSettingsReq();

    Component.onCompleted: {
        if (swValue === "00") {
            state = "off";
        }
        else state = "on";
    }

    // When value is changed from external
    //
    onSwValueChanged: {
        if (swValue === "00") {
            state = "off";
        }
        else state = "on";
    }

    function toggle() {      //toggle function
        if (state === "on") {
            state = "off";
            swValue = "00";
        }
        else {
            state = "on";
            swValue = "01";
        }
        updateSwValue(swValue); //send update to parent qml (stage.qml)
    }

    //button image
    Image {
        id: imgSwitch
        height: btnSwitch.width
        width: btnSwitch.height
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        fillMode: Image.PreserveAspectFit
        smooth: true
    }
    //button mouse area
    MouseArea {
        id: switchArea
        anchors.fill: parent
        onPressed: {
            toggle();
        }
    }

    //button for return to list
    Image {
        id: exit
        height: 80
        width: 80
        source: resourceBase + "back" + resourceResolution
        anchors.left: btnSwitch.left
        anchors.top: btnSwitch.bottom
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
        anchors.right: btnSwitch.right
        anchors.top: btnSwitch.bottom
        anchors.topMargin: 10

        MouseArea {
            anchors.fill: parent
            onPressed: {
                sendSettingsReq();
            }
        }
    }

    //On/Off states
    states: [
         State {
             name: "off"
             PropertyChanges {target: imgSwitch;
                 source: (size===0) ? resourceBase + "switch_off" + resourceResolution : resourceBase + "switch_off.png"
             }
         },
         State {
             name: "on"
             PropertyChanges { target: imgSwitch;
                 source: (size===0) ? resourceBase + "switch_on" + resourceResolution : resourceBase + "switch_on.png"
             }
         }
     ]

}
