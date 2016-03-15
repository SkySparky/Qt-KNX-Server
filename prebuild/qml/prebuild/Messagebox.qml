// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: msgBox
    width: parent.width
    height: 0
    color: clr_msg
    border.color: clr_border
    radius: 8

    property int msg_interval

    function onMsg(msg, interval) {
        tmr.stop();
        msg_interval = interval;
        msg_text.text = msg
        showMsgBox.start();
        showMsgText.start();
        tmr.start();
    }

    Text {
        id: msg_text
        anchors.fill: msgBox
        color: clr_msg_text
        opacity: 0
        text: qsTr("")
        font.pixelSize: msgboxCaptionSize
    }

    Timer {
        id: tmr
        interval: msg_interval
        onTriggered: {
            hideMsgText.start();
            hideMsgBox.start();
        }
    }


    ParallelAnimation {
        id: showMsgBox
        NumberAnimation { target: msgBox; property: "height"
            from: 0; to: msgboxHeight
            duration: 250; easing.type: Easing.InOutSine }
    }

    ParallelAnimation {
        id: hideMsgBox
        NumberAnimation { target: msgBox; property: "height"
            from: msgboxHeight; to: 0
            duration: 250; easing.type: Easing.InOutSine }
    }

    ParallelAnimation {
        id: showMsgText
        NumberAnimation { target: msg_text; property: "opacity"
            from: 0; to: 1
            duration: 500; easing.type: Easing.InOutSine }
    }

    ParallelAnimation {
        id: hideMsgText
        NumberAnimation { target: msg_text; property: "opacity"
            from: 1; to: 0
            duration: 180; easing.type: Easing.InOutSine }
    }

}
