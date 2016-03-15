// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//Switch is always on the screen but it's hidden

Item {
    id: btnSwitch
    width: 360
    height: 360
    state: "off"

    property string swGroupAddr     //switch current group addr
    property string swValue         //switch current value
    property string theme : "default"   // switch theme

    signal updateSwValue(string value);
    signal sendExitReq();
    signal sendSettingsReq();

    Component.onCompleted: {
        if (swValue === "00") {
            state = "off";
        }
        else state = "on";
        console.log("swValue: " + swValue);
    }


    function toggle() {      //toggle function
        if (state === "on") {
            state = "off";
            swValue = "00";
            //console.log("on -> off");
        }
        else {
            state = "on";
            swValue = "01";
            //console.log("off -> on");
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
        source: theme + "/back.png"
        anchors.left: btnSwitch.left
        anchors.bottom: btnSwitch.bottom

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
        source: theme + "/settings.png"
        anchors.right: btnSwitch.right
        anchors.bottom: btnSwitch.bottom

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
             PropertyChanges { target: imgSwitch; source: theme + "/switch_off.png"}
         },
         State {
             name: "on"
             PropertyChanges { target: imgSwitch; source: theme + "/switch_on.png"}
         }
     ]

}
