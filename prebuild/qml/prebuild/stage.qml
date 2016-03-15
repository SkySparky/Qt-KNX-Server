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
    id: stage
    width: 480
    height: 800

    property color clr_header_back: "#efefef"
    property color clr_header_border: "#ff9900"
    property color clr_header_text: "#3299bb"
    property color clr_header_text_back: "#ff9900"

    property color clr_back: "#242424"
    property color clr_border: "#ff9900"
    property color clr_text: "#FFFFFF"
    property color clr_text_back: "#3299bb"
    property color clr_msg: "#efefef"
    property color clr_msg_text: "#3299bb"

    property int smallIcons:0
    property int graphicHeight: (smallIcons==1? 50:100);                // Native size of bitmap on button. No scalling is done so this must match bitmap size (x and y)
    property int buttonHeight: (smallIcons==1? 56:110);                 // Vertical Size of the buttons
    property int menuButtonHeight: (smallIcons==1? 50:100);
    property int menuGraphicHeight: (smallIcons==1? 48:98);                // Native size of bitmap on button. No scalling is done so this must match bitmap size (x and y)
    property string resourceResolution: (smallIcons==1? "50.png":"100.png");   // Used to select smalled or bigger bitmaps

    property int scrollOffsetY: (smallIcons==1? 30:70);         // Header space before the FLICKABLE (and buttons) start
    property int buttonOffsetY: 5;         // Empty space between first button and star of FLICKABLE
    property int buttonCaptionSize: graphicHeight/3;
    property int msgboxCaptionSize: graphicHeight/4;
    property int msgboxHeight: (smallIcons==1? 65:120);
    property alias stageHeight : stage.height;

    property string resourceBase:  "/qml/prebuild/images/default/";


    color: clr_back

    signal notify(int notifyType, string notifyString);  //This is the only way to notify the c++ file (see: common.h for notifyType)

    function onMsg(title, msg) {
        var tmpStr = "<b>" + title + "</b><br><i>" + msg + "</i>";
        msgBox.onMsg(tmpStr, 2200);
    }

    Rectangle {
        color: clr_back
        id: listRow
        anchors.top: stage.top
        anchors.bottom: menuBar.top
        anchors.bottomMargin: 5
        anchors.left: stage.left
        anchors.right: stage.right

        ListView {
            id: listView
            anchors.fill: listRow;
            anchors.margins: 5
            focus: true
            opacity: 100
            visible:  true
            model: screenModel    //screenModel is referenced in C++

            delegate: Item {
                width: listView.width; height: buttonHeight + 6
              Row {
                  Column {
                      DeviceButton {
                          devIndex: model.modelData.index
                          devDescription: model.modelData.description   //button description [string]
                          devType: model.modelData.type           //device type [int] (see: en_en_devType in GroupAddrObject)
                          devValue: model.modelData.value         //the group address value [string]
                          devAddress: model.modelData.groupAddr   //this is the group address and it's a hidden property [string]
                          devAddress1: model.modelData.groupAddr1
                          devAddress2: model.modelData.groupAddr2
                          devAddress3: model.modelData.groupAddr3
                          devAddress4: model.modelData.groupAddr4
                          devStatusAddress: model.modelData.statusAddr
                          devStatusAddress1: model.modelData.statusAddr1
                          devStatusAddress2: model.modelData.statusAddr2
                          devStatusAddress3: model.modelData.statusAddr3
                          devStatusAddress4: model.modelData.statusAddr4
                          onDeviceButtonClicked: {    //when a list object is pressed
                              if (devType == 0) { //DEV_SWITCH
                                  knxSwitch.devIndex = devIndex;
                                  knxSwitch.swGroupAddr = devAddress; //update switch with the obj ga
                                  knxSwitch.swValue = devValue;   //update switch with the obj value
                                  getSwitch.start();
                              }
                              else if (devType == 1) { //DEV_DIMMER
                                  knxDimmer.devIndex = devIndex;
                                  knxDimmer.dimGroupAddr = devAddress;
                                  knxDimmer.dimVal = devValue;
                                  getDimmer.start();
                              }
                              else if (devType == 3) { //DEV_SHUTTER
                                  knxShutter.devIndex = devIndex;
                                  knxShutter.shGroupAddrVal = devAddress;
                                  knxShutter.shGroupAddrStep = devAddress1;
                                  getShutter.start();
                              }
                              else if (devType == 4) {    //DEV_TAGBTN
                                  //update screen with the "group address" of the tag button
                                  //the ga contains the tag that will be show on screen
                                  notify(19, devAddress);   //19 = NOTIFY_STAGE_UPDATE_SCREEN (see: common.h)
                              }
                              else if (devType == 5) {    //DEV_TEMP
                                  knxTemp.devIndex = devIndex;
                                  knxTemp.tmpGroupAddr = devAddress;
                                  knxTemp.tmpValue = devValue;
                                  getTemp.start();
                              }
                          }

                          //if the value is changed then update the thumbnail
                          onDevValueChanged: {
                              onValueChange();  //call on value change from DeviceButton.qml
                              if (devType == 0) {   //DEV_SWITCH
                                  if (knxSwitch.swGroupAddr == devAddress) {
                                      knxSwitch.swValue = devValue;
                                  }
                              }
                              else if (devType == 1) {  //DEV_DIMMER
                                  if (knxDimmer.dimGroupAddr == devAddress) {
                                      knxDimmer.dimVal = devValue;
                                  }
                              }
                              else if (devType == 3) {  //DEV_SHUTTER
                                  if (knxShutter.shGroupAddrStep == devAddress) {
                                      knxShutter.shValue = devValue;
                                  }
                              }
                              else if (devType == 5) {  //DEV_TEMP
                                  if (knxTemp.tmpGroupAddr == devAddress) {
                                      knxTemp.tmpValue = devValue;
                                  }
                              }
                          }

                          onUpdateDevValue : {
                              if (devType == 0) {
                                  var tmpstr = devType.toString() + "," + groupAddr + "," + newVal;
                                  notify(20, tmpstr); //20=NOTIFY_STAGE_UPDATE_VALUE (see: common.h)
                              }
                              else if (devType == 1) {
                                  //knxDimmer
                              }
                          }

                      } //:~ MenuButton
                  } //~:Column
              } //~: Row
            } //~: Item
        } //~: ListView

        ScrollBar {
            scrollArea: listView; height: listView.height; width: 8
            anchors.right: listView.right
        }

        KnxSwitch {
            id: knxSwitch
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            opacity: 0
            size: 1

            onUpdateSwValue: {  //if value has changed from the switch its self
                var tmpstr = "0," + swGroupAddr + "," + swValue;
                notify(20, tmpstr); //20=NOTIFY_STAGE_UPDATE_VALUE (see: common.h)
            }
            onSendExitReq: {
                getListFromSwitch.start();  //animate device list return
            }
            onSendSettingsReq: {
                notify(16, knxSwitch.devIndex.toString()); //16=NOTIFY_EDIT_DEVICE (see: common.h)
            }
        }

        KnxShutter {
            id: knxShutter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            opacity: 0
            size: 1

            onBtnClicked: {  //if value has changed from the switch its self
                var tmpstr = "0," + shGroupAddr + "," + shValue;
                notify(20, tmpstr); //20=NOTIFY_STAGE_UPDATE_VALUE (see: common.h)
            }
            onSendExitReq: {
                getListFromShutter.start();  //animate device list return
            }
            onSendSettingsReq: {
                notify(16, knxShutter.devIndex.toString()); //16=NOTIFY_EDIT_DEVICE (see: common.h)
            }
        }

        KnxDimmer {
            id: knxDimmer
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            dimmerValue: 0
            opacity: 0
            size: 1
            onSendValue: {
                var tmpstr = "0," + dimGroupAddr + "," + dimVal;
                notify(20, tmpstr); //20=NOTIFY_STAGE_UPDATE_VALUE (see: common.h)
            }
            onSendExitReq: {
                getListFromDimmer.start();
            }
            onSendSettingsReq: {
                notify(16, knxDimmer.devIndex.toString()); //16=NOTIFY_EDIT_DEVICE (see: common.h)
            }
        }

        KnxTemp {
            id: knxTemp
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            opacity: 0
            size: 1
            onBtnClicked: {  //if value has changed from the switch its self
                var tmpstr = "0," + tmpGa + "," + tmpVal;
                notify(20, tmpstr); //20=NOTIFY_STAGE_UPDATE_VALUE (see: common.h)
            }
            onSendExitReq: {
                getListFromTemp.start();
            }
            onSendSettingsReq: {
                notify(16, knxTemp.devIndex.toString()); //16=NOTIFY_EDIT_DEVICE (see: common.h)
            }
        }
    }

    Messagebox {
        id: msgBox
        anchors.top: stage.top
        anchors.left: stage.left
        anchors.right: stage.right
    }

//    //For orientation changes ONLY
//    property bool changeOfWidth: false
//    property bool changeOfHeight: false
//    property bool newOrientation:  false

//    onWidthChanged: {changeOfWidth = true; newOrientation = (changeOfWidth && changeOfHeight)}
//    onHeightChanged: {changeOfHeight = true; newOrientation  = (changeOfWidth && changeOfHeight)}

//    onNewOrientationChanged: {
//        if (newOrientation) {
//            changeOfWidth = false;
//            changeOfHeight = false;

//            if (height < 500) smallIcons = 1;
//            else smallIcons = 0;

//            if (width > height) {
//                // landscape
//                knxDimmer.width = height;
//                knxSwitch.width = height;
//            } else {
//                // portrait
//                knxDimmer.width = width;
//                knxSwitch.width = width;
//            }
//        }
//    }


    //Main menu
    Rectangle {
        id: menuBar
        color: clr_back
        width: stage.width
        height: menuButtonHeight
        anchors.bottom: stage.bottom
        anchors.bottomMargin: 5
        anchors.left: stage.left
        anchors.right: stage.right
        MenuButton {
            id: menuBack
            anchors.left:  menuBar.left //anchor to main screen
            anchors.leftMargin: (stage.width - 4*menuButtonHeight)/8
            thumbnail: resourceBase + "back" + resourceResolution
            onBtnClicked: {
                notify(18, "");  //18=NOTIFY_STAGE_BACK (see: common.h) send back signal to c++
            }
        }
        MenuButton {
            id: menuMain
            anchors.left:  menuBack.right
            anchors.leftMargin: (stage.width - 4*menuButtonHeight)/4
            thumbnail: resourceBase + "home" + resourceResolution
            onBtnClicked: {
                notify(19, "./");   //19 = NOTIFY_STAGE_UPDATE_SCREEN (see: common.h)
            }
        }
        MenuButton {
            id: menuSettings
            anchors.left:  menuMain.right   //anchor to main screen
            anchors.leftMargin: (stage.width - 4*menuButtonHeight)/4
            thumbnail: resourceBase + "settings" + resourceResolution
            onBtnClicked: {
                notify(21, ""); //21=NOTIFY_STAGE_EXIT (see: common.h)
            }
        }
        MenuButton {
            id: menuConnect
            anchors.left:  menuSettings.right   //anchor to main screen
            anchors.leftMargin: (stage.width - 4*menuButtonHeight)/4
            thumbnail: resourceBase + "settings" + resourceResolution
            onBtnClicked: {
                notify(23, ""); //23=NOTIFY_STAGE_RECONNECT (see: common.h)
            }
        }
    }

    // Switch animations
    //
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

    // Dimmer animations
    //
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

    // Shutter animations
    //
    ParallelAnimation {
        id: getShutter
        NumberAnimation { target: knxShutter; property: "opacity"
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
        id: getListFromShutter
        NumberAnimation { target: knxShutter; property: "opacity"
            from: 1.0; to: 0
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: listView; property: "opacity"
            from: 0; to: 1
            duration: 250; easing.type: Easing.InOutSine }
        NumberAnimation { target: menuBar; property: "opacity"
            from: 0; to: 1
            duration: 750; easing.type: Easing.InOutSine }
    }
    // Temp animations
    //
    ParallelAnimation {
        id: getTemp
        NumberAnimation { target: knxTemp; property: "opacity"
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
        id: getListFromTemp
        NumberAnimation { target: knxTemp; property: "opacity"
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
