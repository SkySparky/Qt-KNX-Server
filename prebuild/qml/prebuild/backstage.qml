// File Version
// v0.1     Red icons test
// v0.2     Buttons moved to external qml files. Major cleanup
// v0.3     Optimised bitmap handling. Added dimentions for graphic as well as button height
// v0.4     Added text input as external qml file
// v0.5     Added checkbox as qml file
// v0.6     Added header as qml file
//          Changed colors to parametrized names
//          Added variable for space between elements
// v0.7		Added device selector type and automatic adaptation of device properties
// v0.8		Added tag deletion
//
// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "functions.js" as Functions
// import debugger

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
// import QtQuick 1.0

Rectangle {
    id: backstage
    width: 480; height: 800; color: "#242424"

    // signal redrawAll()

    // User set items
    //
    property int standaloneQml:0
    property int smallIcons:0
    property int graphicHeight: (smallIcons==1? 50:100);                // Native size of bitmap on button. No scalling is done so this must match bitmap size (x and y)
    property int buttonHeight: (smallIcons==1? 56:110);                 // Vertical Size of the buttons
    property int buttonSpacerHeight: (smallIcons==1? 3:6);                 // Vertical empty space between buttons

 property string resourceResolution: (smallIcons==1? "50.png":"100.png");   // Used to select smalled or bigger bitmaps

    property int scrollOffsetY: (smallIcons==1? 30:70);         // Header space before the FLICKABLE (and buttons) start
    property int buttonOffsetY: 5;         // Empty space between first button and star of FLICKABLE
    property int buttonCaptionSize: graphicHeight/3; //24;
    property alias stageHeight : backstage.height;
    property int swallowGradientHeight: 30; // Height of the horizontal gradient that "swallows" the scolling elements
    property int msgboxCaptionSize: graphicHeight/4;
    property int msgboxHeight: (smallIcons==1? 65:120);

    property color clr_header_back: "#4f2900"
    property color clr_header_border: "#ff9900"
    property color clr_header_text: "#3299bb"
    property color clr_header_text_back: "#ff9900"

    property color clr_back: "#242424"
    property color clr_border: "#ff9900"
    property color clr_text: "#ffffff"
    property color clr_text_back: "#3299bb"

    property color clr_msg: "#efefef"
    property color clr_msg_text: "#3299bb"

    property string add_tags_text;              // Has the input from the stage
    property string add_tags_edit;              // Has the latest SAVED version of tags from backstage tags screen. ALL TAGS
    property string add_tags_return;            // Has the latest SAVED version of tags from backstage tags screen. ONLY SELETED TAGS
    property int  tags_mode: 0;                 // The tags screen may be used for 0: Modify existing item's tags, 1: Select New Item's tag, 2: Manage all tags


    property int add_CurrentIndex: -1;
    property int add_CurrentType: 0;		// Type selected by add or edit device selector
    property int add_CurrentHeight: 0;		// Size of flickable content

    property int impexpType: 0;

    // property alias dbgText: scr_mainMenu.rect1.text1.text ;

    property string resourceBase: ( standaloneQml == 1 ?"images/" : "/qml/prebuild/images/default/");

//    property string resourceBase: "";

    // System Items
    //
    property Rectangle scr1     // Used for passing the screen rectangles between javascript and transitions
    property Rectangle scr2

    signal notify(int notifyType, string notifyData);   //send data to backstage.cpp

    function startAutoSearch() {
        notify(10, "");    //10 = NOTIFY_AUTOSEARCH
        searchTimer.start();
        searchTimeout.start();
        imgSearchWait.visible = true;
    }

    function stopAutoSearch() {
        searchTimeout.stop();
        searchTimer.stop();
        imgSearchWait.visible = false;
        imgSearchWait.x = -3000;
    }

    Timer {
        id: searchTimeout
        interval: 12000; running: false; repeat: false
        onTriggered: {
            stopAutoSearch();
        }
    }


    Timer {
        id: searchTimer
        interval: 500; repeat: true
        onTriggered: {
            imgSearchWait.rotation += 10;
        }
    }


    function onNotify(notifyType, notifyData) { //receive data from backstage.cpp
        //console.log("[onNotify QML]: " + notifyData);
        switch(notifyType) {
        case 1:     //NOTIFY_KNX_SEARCH_RESULT
        //case 3:
            txt_gwIP.text = notifyData;
            break;

        case 4:     //NOTIFY_SETTINGS_REQ
            txt_gwIP.text = notifyData;
            break;

        case 10:    //NOTIFY_AUTOSEARCH
            //add_groupAddr.text = notifyData
            stopAutoSearch();
            var tmpStr = "<b>Found address:</b><br><i>" + notifyData + "</i>";
            msgBox.onMsg(tmpStr, 5000);
            break;
        case 16:    //NOTIFY_EDIT_DEVICE
            var dVal = notifyData.split(",");         // split params

            //fill with edit data
            add_CurrentIndex = dVal[0];
            add_description.text = dVal[1];
            add_root.cbValue = (dVal[2] === "0") ? 0 : 1;
            add_tags_text = dVal[3];        // Get existing tags from system. On first backstage save has the final values
            add_tags_edit = add_tags_text;  // Temporary working copy between backstage screens
            // add_tags_return = Functions.filterReplyString( add_tags_edit ); // We need the return string in case user does not enter tag editing
            tags_mode = 1;

            var dType = 0;
            if (dVal[4] === "switch") dType = 0;
            else if (dVal[4] === "dimmer") dType = 1;
            else if (dVal[4] === "rgb") dType = 2;
            else if (dVal[4] === "shutter") dType = 3;
            else if (dVal[4] === "tagbtn") dType = 4;
            else if (dVal[4] === "temp") dType = 5;

            Functions.setObjType( dType );      // set type

            add_groupAddr.text = dVal[5];
            add_groupAddr1.text = dVal[6];
            add_groupAddr2.text = dVal[7];
            add_groupAddr3.text = dVal[8];
            add_groupAddr4.text = dVal[9];
            add_statusAddr.text = dVal[10];
            add_statusAddr1.text = dVal[11];
            add_statusAddr2.text = dVal[12];
            add_statusAddr3.text = dVal[13];
            add_statusAddr4.text = dVal[14];

            Functions.swap(scr_mainMenu, scr_add, Functions.glb_TransitionType1 );

            break;

        case 25:
            add_tags_text = notifyData;        // Get existing tags from system. On first backstage save has the final values
            add_tags_edit = add_tags_text;  // Temporary working copy between backstage screens
            break;
        }

    }

    function onMsg(title, msg) {
        var tmpStr = "<b>" + title + "</b><br><i>" + msg + "</i>";
        msgBox.onMsg(tmpStr, 2200);
    }

    function returnToStage() {
        notify(21, "0");    //21=NOTIFY_STAGE_EXIT (see: common.h)
    }

    //For orientation changes ONLY
    //
    property bool changeOfWidth: false
    property bool changeOfHeight: false
    property bool newOrientation:  false

    // onWidthChanged: {changeOfWidth = true; newOrientation = (changeOfWidth && changeOfHeight)}
    // onHeightChanged: {changeOfHeight = true; newOrientation  = (changeOfWidth && changeOfHeight)}

    onNewOrientationChanged: {
        if (newOrientation) {
            changeOfWidth = false;
            changeOfHeight = false;

            if (height < 500) smallIcons = 1;
            else smallIcons = 0;

            if (width > height) {
                // Do landscape handling in da here
            } else {
                // Do portrait handling in da here
            }
        }
    }


    Keys.onBackPressed: {
        event.accepted = true;
        Functions.swap(scr_mainMenu, scr_about, Functions.glb_TransitionType1 );
    }
    Keys.onPressed: {
        if ( event.key == Qt.Key_Menu || event.key == Qt.Key_MenuKB || event.key == Qt.Key_MenuPB ) {
            event.accepted = true;
            Functions.swap(scr_mainMenu, scr_about, Functions.glb_TransitionType1 );
        }
        else
            Functions.swap(scr_mainMenu, scr_add, Functions.glb_TransitionType1 );
    }


//    Image {
//        id: imgBottom
//        x:0;  y: (stageHeight - 30);  z:200;  height: swallowGradientHeight ; width: parent.width
//        source: resourceBase + "alphalist4.png"; fillMode: Image.Stretch
//        // anchors.bottom: backstage.bottom
//    }
//    Image {
//        id: imgTop
//        x:0; y: flick_mainMenu.y; z:200; height: swallowGradientHeight; width: parent.width
//        source: resourceBase + "alphalist3.png"; fillMode: Image.Stretch
//    }





















    // SCR Main Menu (BackStage) ====================================================
    //
    Rectangle {

        id: scr_mainMenu
        x: 0;  y: 000;
        width: backstage.width; height: backstage.height; color: clr_back
        property int itemIndex: 0;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ hdrText: "Main Menu" }

        // Page Body
        //
        Flickable { // Note : For the flick effect to be visible the contentHeight MUST be smaller than height
            // id:  flick_mainMenu

            width : backstage.width; height:backstage.height - scrollOffsetY ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            // contentHeight: Math.max ( stageHeight-scrollOffsetY - 1, ( parent.itemIndex * buttonHeight ) + buttonOffsetY );    // This must be smaller than the total height of children

            onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }

            // Buttons (!!! IN REVERSE ORDER OF APEARENCE !!!!) ========================================
            //
            // Back Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "back"  + resourceResolution ;      btnText: "Back";
                onBtnClicked:  returnToStage();
            }
            // About Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "info"  + resourceResolution ;      btnText: "About";
                onBtnClicked:  {
                    Functions.swap(scr_mainMenu, scr_about, Functions.glb_TransitionType1 );
                }
            }
            // Settings Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "settings"  + resourceResolution ;  btnText: "Settings";
                onBtnClicked:  {
                    notify(4, ""); //4= NOTIFY_SETTINGS_REQ (see common.h)
                    Functions.swap(scr_mainMenu, scr_settings, Functions.glb_TransitionType1 );
                }
            }
            // Manage Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "managebus"  + resourceResolution ;  btnText: "Manage Bus" ;
                onBtnClicked:  {
                    notify(25, "-1"); //request tags
                    Functions.swap(scr_mainMenu, scr_manage, Functions.glb_TransitionType1 );
                }
            }


            // Page footer =========
            //

        }   // Flickable

    }
    //
    // SCR MainMenu


    // SCR Manage =======================
    //
    Rectangle {

        id: scr_manage
        x: 1000;  y: 0
        width: backstage.width; height: backstage.height; color: "black"
        property int itemIndex: 0;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ hdrText: "Manage Bus" }

        // Page Body
        //
        Flickable { // Note : For the flick effect to be visible the contentHeight MUST be smaller than height
            //id:  flick_manage
            width : backstage.width; height:backstage.height - scrollOffsetY - swallowGradientHeight*2 ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }

            // Buttons (!!! IN REVERSE ORDER OF APEARENCE !!!!) ======================================== ========================================
            //
            // Back Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "back"  + resourceResolution;  btnText: "Back" ;
                onBtnClicked: Functions.swap(scr_manage, scr_mainMenu, Functions.glb_TransitionType1 + 1 );
            }
            // Export Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "export"  + resourceResolution;  btnText: "Export" ;
                onBtnClicked: {
                    Functions.swap(scr_manage, scr_importExport, Functions.glb_TransitionType1 );
                    impexpType = 0;
                }
            }
            // Import Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "import"  + resourceResolution;  btnText: "Import" ;
                onBtnClicked: {
                    Functions.swap(scr_manage, scr_importExport, Functions.glb_TransitionType1 );
                    impexpType = 1;
                }
            }
            // Reset Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "delete"  + resourceResolution;  btnText: "Delete all" ;
                onBtnClicked:  Functions.swap(scr_manage, scr_resetVerification, Functions.glb_TransitionType1 );
            }
            // Manage Tags Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "folder"  + resourceResolution;  btnText: "Manage Tags" ;
                onBtnClicked:  {
                    // add_CurrentIndex = -1;  //reset current index
                    // notify(25, "-1");   //25: NOTIFY_STAGE_SYS_TAGS, -1: get all tags
                    //if ( add_tags_edit == "" ) add_tags_edit = "0/1/2/3/4/5/6/7/8/9/0/hgff";
                    Functions.createList(add_tags_edit, 3); // Populate the tags list
                    Functions.swap(scr_manage, scr_tags, Functions.glb_TransitionType1);
                }
            }
            // Add Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "add"  + resourceResolution;  btnText: "Add device" ;
                onBtnClicked:  {
                    add_CurrentIndex = -1;  //reset current index
                    notify(25, "-1");   //25: NOTIFY_STAGE_SYS_TAGS, -1: get all tags
                    add_description.text = "";
                    add_root.cbValue = 0;
                    add_groupAddr.text = "";
                    add_groupAddr1.text = "";
                    add_groupAddr2.text = "";
                    add_groupAddr3.text = "";
                    add_groupAddr4.text = "";
                    add_statusAddr.text = "";
                    add_statusAddr1.text = "";
                    add_statusAddr2.text = "";
                    add_statusAddr3.text = "";
                    add_statusAddr4.text = "";
                    Functions.swap(scr_manage, scr_selectType, Functions.glb_TransitionType1 );
                }
            }
//            // Edit Button
//            //
//            BackStageBtn1 {
//                btnImage: resourceBase + "add"  + resourceResolution;  btnText: "Edit device" ;
//                onBtnClicked:  Functions.swap(scr_manage, scr_edit, Functions.glb_TransitionType1 );
//            }
            // Page footer
            //
        }   // Flickable
    }
    //
    // SCR Manage

//    // SCR device list
//    //
//    Rectangle {
//        id: scr_edit
//        x: 1000;  y: 0
//        width: backstage.width; height: backstage.height; color: "black"
//        property int itemIndex: 0;

//        ListView {
//            id: deviceListView
//            anchors.fill: deviceList;
//            anchors.margins: 5
//            model: screenModel    //screenModel is referenced in C++
//            delegate:
//                Rectangle {
//                    radius: 2
//                    color: clr_back; border.color: clr_border
//                    Text {
//                        anchors.fill: parent
//                        text: descr //the device's description
//                    }
//            }
//        }
//        ScrollBar {
//            scrollArea: deviceListView; height: deviceListView.height; width: 8
//            anchors.right: deviceListView.right
//        }
//    }

    // SCR Settings ====================================================
    //
    Rectangle {
        id: scr_settings
        x: 1000;  y: 0
        width: backstage.width; height: backstage.height; color: "black"
        property int itemIndex: 0;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ hdrText: "Settings" }

        // Page Body
        //
        Flickable { // Note : For the flick effect to be visible the contentHeight MUST be smaller than height
            // id:  flick_manage
            width : backstage.width; height:backstage.height - scrollOffsetY - swallowGradientHeight*2 ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ; }


            // Buttons ================
            //
            // Back Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "back"  + resourceResolution;  btnText: "Back" ;
                onBtnClicked: Functions.swap(scr_settings, scr_mainMenu, Functions.glb_TransitionType1 + 1 );
            }
            // Save Button
            //
            BackStageBtn1 {
                id: settings_gwip
                btnImage: resourceBase + "ok"  + resourceResolution;  btnText: "Save" ;
                onBtnClicked: notify(5, "gatewayip=" + txt_gwIP.text); //5= NOTIFY_SETTINGS_SAVE_REQ (see common.h)
            }

            // Large Icons
            //
            BackStageBtn1 {
                btnImage: resourceBase + "settings"  + resourceResolution ;  btnText: "Large";
                onBtnClicked:  {
                    resourceResolution = "100.png";
                    graphicHeight = 100;                // Native size of bitmap on button. No scalling is done so this must match bitmap size (x and y)
                    buttonHeight = 104;                 // Vertical Size of the buttons
                }
            }

            // Small Icons
            //
            BackStageBtn1 {
                btnImage: resourceBase + "managebus"  + resourceResolution ;  btnText: "Small" ;
                onBtnClicked:  {
                    resourceResolution = "50.png";
                    graphicHeight = 50;                // Native size of bitmap on button. No scalling is done so this must match bitmap size (x and y)
                    buttonHeight = 52;                 // Vertical Size of the buttons
                }
            }

            // Autosearch Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Search for Gateway" ;
                onBtnClicked: {
                    //Functions.swap(scr_settings, scr_mainMenu, Functions.glb_TransitionType1 + 1 );
                    notify(0, ""); //0 = NOTIFY_KNX_SEARCH_REQ (see common.h)
                }
            }


            // Gateway IP TextBox
            //
            TextInput1 {
                id: txt_gwIP
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Gateway IP" ;

            }






            // Back Button
            //

            // Footer
            //

        } // Flickable
    }
    //
    // SCR Settings


    // SCR About ====================================================
    //
    Rectangle {
        id: scr_about
        x: 1000;  y: 0
        width: backstage.width; height: backstage.height; color: "black"
        property int itemIndex: 5;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ hdrText: "About" }

        // Page Body
        //
        Flickable { // Note : For the flick effect to be visible the contentHeight MUST be smaller than height
            width : backstage.width; height:backstage.height - scrollOffsetY - swallowGradientHeight*2 ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }

            Image {
                id: logo
                width : parent.width
                height : parent.width
                fillMode: Image.Tile
                source: resourceBase + "logo_a.png"
                // + resourceResolution
            }

            // Text
            //
            Rectangle {
                x: 0;
                y: parent.width ;
                width : parent.width
                height: backstage.buttonHeight ;
                color: "black"
                Column {
                    anchors.centerIn: parent
                    Text { text:"GIDT Bus Control"; horizontalAlignment: Text.AlignHCenter; color: "white"; width: parent.width}
                    // Text { text:"Coming to light your world" ; horizontalAlignment: Text.AlignHCenter;color: "white"; width: parent.width                    }
                    Text { text:"version 0.1" ;horizontalAlignment: Text.AlignHCenter; color: "white" ;width: parent.width                  }
                }
            }
            // Back Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "back"  + resourceResolution;  btnText: "Back" ;
                onBtnClicked: Functions.swap(scr_about, scr_mainMenu, Functions.glb_TransitionType1 + 1 );
            }


            // Footer
            //


        } // Flickable
    }
    //
    // SCR About






    // SCR Select Component Type ====================================================
    //
    Rectangle {
        id: scr_selectType
        x: 1000;  y: 0
        width: backstage.width; height: backstage.height; color: "black"
        property int itemIndex: 0;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ hdrText: "Select Component Type" }

        // Page Body
        //
        Flickable { // Note : For the flick effect to be visible the contentHeight MUST be smaller than height
            width : backstage.width; height:backstage.height - scrollOffsetY - swallowGradientHeight*2 ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }


//            Rectangle {
//                x: 0;
//                y: backstage.scrollOffsetY;
//                width : parent.width
//                height: backstage.buttonHeight * 2;
//                color: "black"
//                Flow { anchors.fill: parent
//                    Text { text: "ATTENTION ! Pressing yes will reset all configured devices."; color: "white"; width: parent.width}
//                    Text { text:"Are you sure you want to continue ?";color: "white"; width: parent.width                    }
//                }
//            }
            // Buttons (!!! IN REVERSE ORDER OF APEARENCE !!!!) ======================================== ========================================
            //
            // Back Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "back"  + resourceResolution;  btnText: "Cancel" ;
                onBtnClicked: Functions.swap(scr_selectType, scr_manage, Functions.glb_TransitionType1 + 1 );
            }
            // Tag button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "folder"  + resourceResolution;  btnText: "Tag button" ;
                onBtnClicked: {
                    Functions.setObjType( 4 );
                    Functions.swap(scr_selectType, scr_add, Functions.glb_TransitionType1 );
                }
            }
            // RGB
            //
            BackStageBtn1 {
                btnImage: resourceBase + "rgb"  + resourceResolution;  btnText: "RGB light" ;
                onBtnClicked: {
                    Functions.setObjType( 2 );
                    Functions.swap(scr_selectType, scr_add, Functions.glb_TransitionType1 );
                }
            }
            // Temp
            //
            BackStageBtn1 {
                btnImage: resourceBase + "temp"  + resourceResolution;  btnText: "Temperature" ;
                onBtnClicked: {
                    Functions.setObjType( 5 );
                    Functions.swap(scr_selectType, scr_add, Functions.glb_TransitionType1 );
                }
            }
            // Shutters
            //
            BackStageBtn1 {
                btnImage: resourceBase + "shutters_N"  + resourceResolution;  btnText: "Shutters" ;
                onBtnClicked: {
                    Functions.setObjType( 3 );
                    // notify(8, ""); //NOTIFY_RESET_ALL
                    Functions.swap(scr_selectType, scr_add, Functions.glb_TransitionType1 );
                }
            }
            // Dimmer
            //
            BackStageBtn1 {
                btnImage: resourceBase + "dimmer"  + resourceResolution;  btnText: "Dimmer" ;
                onBtnClicked: {
                    // notify(8, ""); //NOTIFY_RESET_ALL
                    Functions.setObjType( 1 );
                    Functions.swap(scr_selectType, scr_add, Functions.glb_TransitionType1 );
                }
            }
            // On/Off Switch
            //
            BackStageBtn1 {
                btnImage: resourceBase + "switch_on"  + resourceResolution;  btnText: "On/Off Switch" ;
                onBtnClicked: {
                    // notify(8, ""); //NOTIFY_RESET_ALL
                    Functions.setObjType( 0 );
                    Functions.swap(scr_selectType, scr_add, Functions.glb_TransitionType1 );
                }
            }
        }
    }


    // SCR Tags
    //
    Rectangle {
        id: scr_tags
        x: 0;  y: 2000;
        width: backstage.width; height: backstage.height; color: clr_back
        property int itemIndex: 0;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ hdrText: "Tags Editor" }


        Text {
            id: dbgText
            anchors.top: parent.top
            text: ""
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 15

        }

        MouseArea {
            id: mouse_area1
            x: 5
            y: 2
            width: 183
            height: 82
            onClicked: {
                dbgText.text = "CreateList";
                Functions.createList();
            }
        }

        MouseArea {
            id: mouse_area2
            x: 291
            y: 0
            width: 189
            height: 84
            onClicked: {
                // dbgText.text = "ReturnList";
                dbgText.text = Functions.composeReplyString();
            }
        }

        Flickable {
            id: flick_Tags


            width : backstage.width; height:backstage.height - scrollOffsetY ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            contentHeight: 0
    //        onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }
        }

        TextEdit {
            id: text_tags
            x: 0
            y: 92
            width: 480
            height: 53
            text: qsTr("3/te/quick/brown/fox/jumps/over/the/lazy/dog")
            font.pixelSize: 12
        }

        Component.onCompleted: {
            if ( tags_mode == 3 ) { // We are managing all tags
                Functions.tagObjects[0].tagY = -500;
            }
        }
    }



    // SCR Add ====================================================
    //
    Rectangle {
        id: scr_add
        x: 1000;  y: 0
        width: backstage.width; height: backstage.height; color: "black"
        property int itemIndex: 0;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ id : addHdr; hdrText: "Add item" }

        // Page Body
        //
        Flickable { // Note : For the flick effect to be visible the contentHeight MUST be smaller than height
            id:  flick_add
            width : backstage.width; height:backstage.height - scrollOffsetY - swallowGradientHeight*2 ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }

            // Buttons (!!! IN REVERSE ORDER OF APEARENCE !!!!) ======================================== ========================================
            //


            // OK Button
            //
            BackStageBtn1 {
                id: add_finish
                btnImage: resourceBase + "ok"  + resourceResolution;  btnText: "Finish" ;
                onBtnClicked: {
                    var resp = "descr=" + add_description.text + ",root=" + add_root.cbValue
                            + ",tags=" + Functions.filterReplyString( add_tags_edit ) +        // This must be the final tag String (only seleted tags needed)
                            ",type=" + add_CurrentType +
                            ",ga=" + add_groupAddr.text +       //5th param
                            ",ga1=" + add_groupAddr1.text +
                            ",ga2=" + add_groupAddr2.text +
                            ",ga3=" + add_groupAddr3.text +
                            ",ga4=" + add_groupAddr4.text +
                            ",sa=" + add_statusAddr.text +      //10th param
                            ",sa1=" + add_statusAddr1.text +
                            ",sa2=" + add_statusAddr2.text +
                            ",sa3=" + add_statusAddr3.text +
                            ",sa4=" + add_statusAddr4.text +
                            ",index=" + add_CurrentIndex.toString();
                    notify(9, resp); //9= NOTIFY_ADD_DEVICE (see common.h)
                    Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
                    add_CurrentIndex = -1;

                    console.log(Functions.filterReplyString( add_tags_edit ));
                }
            }
            // Remove Button
            //
            BackStageBtn1 {
                id: add_remove;
                btnImage: resourceBase + "delete"  + resourceResolution;  btnText: "Delete" ;
                onBtnClicked: {
                    if (add_CurrentIndex >= 0) {
                        notify(15, add_CurrentIndex.toString()); //15= NOTIFFY_REMOVE_DEVICE (see common.h)
                        add_CurrentIndex = -1;
                    }
                    Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1);
                }
            }
            // Cancel Button
            //
            BackStageBtn1 {
                id: add_cancel;
                btnImage: resourceBase + "back"  + resourceResolution;  btnText: "Cancel" ;
                onBtnClicked: {
                    Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 + 1 );
                    add_CurrentIndex = -1;
                }
            }

            // Address Text
            //
            TextInput1 {
                id: add_statusAddr4
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Status Address 4" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_statusAddr3
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Status Address 3" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_statusAddr2
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Status Address 2" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_statusAddr1
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Status Address 1" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_statusAddr
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Status Address" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_groupAddr4
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Address4" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_groupAddr3
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Address3" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_groupAddr2
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Address2" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_groupAddr1
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Address1" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Address Text
            //
            TextInput1 {
                id: add_groupAddr
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Address" ;
                // visible: false
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Auto Learn Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Auto Learn" ;
                onBtnClicked: {
                    startAutoSearch();
                }
            }
            // Tags Text
            //
            BackStageBtn1 {
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Tags" ;
                onBtnClicked: {
                    console.log("tags: " + add_tags_edit);
                    tags_mode = 0;
                    Functions.createList(add_tags_edit,0); // Populate the tags list
                    Functions.swap(scr_add, scr_tags, Functions.glb_TransitionType1);
                }
            }

//            TextInput1 {
//                id: add_tags;
//                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Tags" ;
//                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
//            }

            // Root item checkbox
            //
            Checkbox1 {
                id: add_root
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Root item" ;
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
            // Description Text
            //
            TextInput1 {
                id: add_description
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Description" ;
                //onBtnClicked: Functions.swap(scr_add, scr_manage, Functions.glb_TransitionType1 );
            }
        }
    }


    // SCR itemProperties ====================================================
    //
    Rectangle {
        id: scr_itemProperties
        x: parent.width
        y: 215
        width:  parent.width
        height:  parent.height
        color: "#ffffff"
        Text {
            id: text4
            x: 42
            y: 16
            text: qsTr("Reset Yes/No")
            font.pixelSize: 12
        }
    }

    // SCR Reset ====================================================
    //
    Rectangle {
        id: scr_resetVerification
        x: 1000;  y: 0
        width: backstage.width; height: backstage.height; color: "black"
        property int itemIndex: 2;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ hdrText: "Reset bus devices" }

        // Page Body
        //
        Flickable { // Note : For the flick effect to be visible the contentHeight MUST be smaller than height
            width : backstage.width; height:backstage.height - scrollOffsetY - swallowGradientHeight*2 ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }


            Rectangle {
                x: 0;
                y: backstage.scrollOffsetY;
                width : parent.width
                height: backstage.buttonHeight * 2;
                color: "black"
                Flow { anchors.fill: parent
                    Text { text: "ATTENTION ! Pressing yes will reset all configured devices."; color: "white"; width: parent.width}
                    Text { text:"Are you sure you want to continue ?";color: "white"; width: parent.width                    }
                }
            }


            // Buttons (!!! IN REVERSE ORDER OF APEARENCE !!!!) ======================================== ========================================
            //
            // Back Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "back"  + resourceResolution;  btnText: "Cancel" ;
                onBtnClicked: Functions.swap(scr_resetVerification, scr_manage, Functions.glb_TransitionType1 + 1 );
            }
            // Confirm reset Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "back"  + resourceResolution;  btnText: "Yes, Reset all" ;
                onBtnClicked: {
                    notify(8, ""); //NOTIFY_RESET_ALL
                    Functions.swap(scr_resetVerification, scr_manage, Functions.glb_TransitionType1 );
                }
            }
        }
    }


    // SCR Import/Export ====================================================
    //
    Rectangle {
        id: scr_importExport
        x: 1000;  y: 0
        width: backstage.width; height: backstage.height; color: "black"
        property int itemIndex: 0;

        // Page Header - excluded from scrolling ==============================
        //
        BackStageHeader{ hdrText: (impexpType == 0) ? "Export" : "Import" }

        // Page Body
        //
        Flickable { // Note : For the flick effect to be visible the contentHeight MUST be smaller than height
            //id:  flick_manage
            width : backstage.width; height:backstage.height - scrollOffsetY - swallowGradientHeight*2 ; x:0; y: scrollOffsetY ; z: 100;
            contentWidth: backstage.width; clip: true
            onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }

            // Back Button
            //
            BackStageBtn1 {
                btnImage: resourceBase + "back"  + resourceResolution;  btnText: "Back" ;
                onBtnClicked: Functions.swap(scr_importExport, scr_manage, Functions.glb_TransitionType1 + 1 );
            }
            // Import/Export button
            //
            BackStageBtn1 {
                btnImage: resourceBase + ((impexpType == 0) ? "export" : "import")
                                                             + resourceResolution;
                btnText: (impexpType == 0) ? "Export config" : "Import config";
                onBtnClicked: {
                    var resp = "server=" + txt_impexportserver.text
                            + ",project=" + txt_impexportproject.text
                            + ",user=" + txt_impexportuser.text
                            + ",passwd=" + txt_impexportpasswd.text;
                    if (impexpType == 0)
                        notify(12, resp); //12= NOTIFY_EXPORT_CONFIG (see common.h)
                    else if (impexpType == 1)
                        notify(11, resp); //11= NOTIFY_IMPORT_CONFIG (see common.h)
                }
            }
            // Import/Export passwd
            //
            TextInput1 {
                id: txt_impexportpasswd
                text: "warwick"
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Password" ;
            }
            // Import/Export passwd
            //
            TextInput1 {
                id: txt_impexportuser
                text: "jaco"
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Username" ;
            }
            // Import/Export project
            //
            TextInput1 {
                id: txt_impexportproject
                text: "home1"
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Project" ;
            }
            // Import/Export project
            //
            TextInput1 {
                id: txt_impexportserver
                text: "192.168.0.214"
                btnImage: resourceBase + "settings"  + resourceResolution;  btnText: "Server" ;
            }
        }

    }





    // Transitions and effects
    //
    ParallelAnimation {
        id: _1to2fwd
        NumberAnimation { target: scr1; property: "x"
            from: 0; to: -( scr2.width )
            duration: 500; easing.type: Easing.OutInQuad }
        NumberAnimation { target: scr2; property: "x"
            from: scr2.width; to: 0
            duration: 500; easing.type: Easing.OutInQuad }
    }
    ParallelAnimation {
        id: _1to2rev
        NumberAnimation { target: scr1; property: "x"
            from: 0; to: ( scr2.width )
            duration: 500; easing.type: Easing.OutInQuad }
        NumberAnimation { target: scr2; property: "x"
            from: -scr2.width; to: 0
            duration: 500; easing.type: Easing.OutInQuad }
    }

    Image {
        id: imgSearchWait
        visible: false
        x: -3000
        anchors.horizontalCenter: backstage.horizontalCenter
        anchors.verticalCenter: backstage.verticalCenter
        source: resourceBase + "busy.png"
    }

    Messagebox {
        id: msgBox
        anchors.top: backstage.top
        anchors.left: backstage.left
        anchors.right: backstage.right
    }



    Item {
        id: _dummy
    }

}
