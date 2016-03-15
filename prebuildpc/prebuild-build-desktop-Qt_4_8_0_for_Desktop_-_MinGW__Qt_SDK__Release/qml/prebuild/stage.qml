// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//DEV_SWITCH    : 0
//DEV_DIMMER    : 1
//DEV_RGB       : 2
//DEV_SHUTTER   : 3
//DEV_TAGBTN    : 4

//MENU_BACKSTAGE    : 0
//MENU_MANAGE       : 1
//MENU_ADD          : 2
//MENU_ITEM_OPTIONS : 3
//MENU_RESET        : 4
//MENU_IMPEXPORT    : 5
//MENU_SETTINGS     : 6
//MENU_ABOUT        : 7

Rectangle {
    id: mainMenu
    width: 480
    height: 600
    color: "black"

    signal back();
    signal updateScreen(string tag);
    signal updateValue(int type, string address, string value); //updates a value in stage.cpp
    signal exit(int status);
    signal quit();


    Component {
        id: listDelegate
        Item {
            width: listView.width; height: 105
            Row {
                Column {
                    DeviceButton {
                        btnHeight: 100
                        devDescription: description   //button description [string]
                        devType: type           //device type [int] (see: en_en_devType in GroupAddrObject)
                        devValue: value         //the group address value [string]
                        devAddress: groupAddr   //this is the group address and it's a hidden property [string]
                        btnWidth: mainMenu.width - 20
                        devTheme: "./images/default"

                        onDeviceButtonClicked: {    //when a list object is pressed
                            if (devType == 0) { //DEV_SWITCH
                                knxSwitch.swGroupAddr = devAddress; //update switch with the obj ga
                                knxSwitch.swValue = devValue;   //update switch with the obj value
                                getSwitch.start();
                            }
                            else if (devType == 1) { //DEV_DIMMER
                                //knxDimmer.
                                getDimmer.start();
                            }
                            else if (devType == 4) {    //DEV_TAGBTN
                                //update screen with the "group address" of the tag button
                                //the ga contains the tag that will be show on screen
                                updateScreen(devAddress);
                            }
                        }

                        onUpdateDevValue: {
                            if (devType == 0) {
                                //knxSwitch.swValue = devValue;
                                updateValue(devType, groupAddr, devValue);
                            }
                            else if (devType == 1) {
                                //knxDimmer
                            }
                        }

                    } //:~ MenuButton
                } //~:Column
            } //~: Row
            //ListView.onAdd: console.log("item added");
        } //~: Item
    } //~: Component

    Rectangle {
        color: "black"
        id: listRow
        anchors.top: mainMenu.top
        anchors.bottom: menuBar.top
        anchors.left: mainMenu.left
        anchors.right: mainMenu.right
        ListView {
              id: listView
              //anchors.top: menuBar.bottom
              //anchors.top: mainMenu.top
              //anchors.bottom: mainMenu.bottom
              anchors.fill: listRow;
              anchors.margins: 5
              model: screenModel    //screenModel is referenced in C++
              delegate: listDelegate
              focus: true
              opacity: 100
              visible:  true
        } //~: ListView



        ScrollBar {
            scrollArea: listView; height: listView.height; width: 8
            anchors.right: listView.right
        }

        KnxSwitch {
            id: knxSwitch
            width: mainMenu.width
            height: width
            anchors.left: listRow.left
            anchors.verticalCenter: parent.verticalCenter
            theme: "images/default"
            opacity: 0

    //        onSendStatus: { //report value changes back to qt
    //            var value = (switchStatus === 0) ? "00" : "01"
    //            updateValue(0, groupAddr, value);   //0= switch type
    //        }
            onUpdateSwValue: {  //if value has changed from the switch its self
                updateValue(0, swGroupAddr, swValue);
            }
            onSendExitReq: {
                getListFromSwitch.start();  //animate device list return
            }
            onSendSettingsReq: {
                exit(3);
            }
        }

        KnxDimmer {
            id: knxDimmer
            width: mainMenu.width
            height: width
            anchors.left: listRow.left
            anchors.verticalCenter: parent.verticalCenter
            dimmerValue: 0
            theme: "images/default"
            opacity: 0
            onSendExitReq: {
                getListFromDimmer.start();
            }
            onSendSettingsReq: {
                exit(3);
            }
        }
    }

    //Main menu
    Rectangle {
        color: "black"
        id: menuBar
        width: mainMenu.width
        height: 60
        anchors.bottom: mainMenu.bottom
        anchors.bottomMargin: 5
        anchors.left: mainMenu.left
        anchors.right: mainMenu.right
        //anchors.left: mainMenu.left
        MenuButton {
            id: menuBack
            anchors.left:  menuBar.left //anchor to main screen
            anchors.leftMargin: 10
            height: 60
            width: (mainMenu.width/3) - 10
            title: "Back"
            thumbnail: "./images/default/back.png";
            onBtnClicked: {
                back(); //send back signal to c++
            }
        }
        MenuButton {
            id: menuMain
            anchors.left:  menuBack.right
            anchors.right:  menuSettings.left
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            height: 60
            width: (mainMenu.width/3) - 10
            title: "Main"
            thumbnail: "./images/default/home.png";
            onBtnClicked: {
                updateScreen("./");
            }
        }

        //anchors.right: mainMenu.right
        MenuButton {
            id: menuSettings
            anchors.right:  menuBar.right   //anchor to main screen
            anchors.rightMargin: 10
            height: 60
            width: (mainMenu.width/3) - 10
            title: "Settings"
            thumbnail: "./images/default/settings.png";
            onBtnClicked: {
                exit(3);
            }
        }
    }

    ParallelAnimation {
        id: getSwitch
        NumberAnimation { target: knxSwitch; property: "opacity"
            from: 0; to: 1.0
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: listView; property: "opacity"
            from: 1.0; to: 0
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: menuBar; property: "opacity"
            from: 1; to: 0
            duration: 750; easing.type: Easing.InOutSine }
    }

    ParallelAnimation {
        id: getDimmer
        NumberAnimation { target: knxDimmer; property: "opacity"
            from: 0; to: 1.0
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: listView; property: "opacity"
            from: 1.0; to: 0
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: menuBar; property: "opacity"
            from: 1; to: 0
            duration: 750; easing.type: Easing.InOutSine }
    }

    ParallelAnimation {
        id: getListFromSwitch
        NumberAnimation { target: knxSwitch; property: "opacity"
            from: 1.0; to: 0
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: listView; property: "opacity"
            from: 0; to: 1
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: menuBar; property: "opacity"
            from: 0; to: 1
            duration: 750; easing.type: Easing.InOutSine }
    }

    ParallelAnimation {
        id: getListFromDimmer
        NumberAnimation { target: knxDimmer; property: "opacity"
            from: 1.0; to: 0
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: listView; property: "opacity"
            from: 0; to: 1
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: menuBar; property: "opacity"
            from: 0; to: 1
            duration: 750; easing.type: Easing.InOutSine }
    }
}
