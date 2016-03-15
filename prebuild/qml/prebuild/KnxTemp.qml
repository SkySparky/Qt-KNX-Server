// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

/**
    Temperature data format

    LSB           MSB
    MEEEEMMM MMMMMMMM   : 16 bits
    (0.01*M)*(2^E)
*/


Item {
    id: btnTemp
    width: (parent.width > parent.height) ? parent.height - 10 : parent.width - 10;
    height: width

    property int size: 0                // 0: size small, 1: size large
    property int devIndex
    property double iValue : 21
    property string tmpGroupAddr
    property string tmpStatusAddr
    property string tmpValue : "00 00 00"

    signal btnClicked(string tmpGa, string tmpVal);
    signal sendExitReq();
    signal sendSettingsReq();

    function getKnxTemp(temp) {
        var iVal = (3 << 11) | (((temp / 8) * 100 ));

        var hVal = "00" + (iVal >> 8).toString(16);
        hVal = hVal.substr(hVal.length - 2, 2);
        var lVal = "00" + (iVal & 0xFF).toString(16);
        console.log("lVal: " + lVal);
        lVal = lVal.substr(lVal.length - 2, 2);
        var ret = "00 " + hVal + " " + lVal;

        return(ret);
    }

    function getTempFromKnx(temp) {
        console.log("temp: " + temp.substr(3, 5));
        var itemp = parseInt(temp.substr(3, 5).replace(" ", ""),16);
        console.log("itemp: " + itemp);
        var m = 0x7FF & itemp;
        var e = (itemp >> 11) & 0x0F;

        var ret = (0.01*m) * (1 << e);
        console.log("temp: " + ret);
        return(ret);
    }

    onTmpValueChanged : {
        iValue = getTempFromKnx(tmpValue);
        txtValue.text = iValue;
    }

    //button image
    Image {
        id: imgTemp
        height: btnTemp.width
        width: btnTemp.height
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        smooth: true
        source: resourceBase + "temp.png"
        MouseArea {
            id: tempDn
            anchors.left: imgTemp.left
            anchors.bottom: imgTemp.bottom
            width: imgTemp.width/2
            height: imgTemp.height/2
            onPressed: {
                tempBtnDn.opacity = 1;
                iValue--;
                var value = getKnxTemp(iValue);
                btnClicked(tmpGroupAddr, value);
                txtValue.text = getTempFromKnx(value);
                console.log("y: " + txtValue.y);
            }
            onReleased: {
                tempBtnDn.opacity = 0;
            }
        }
        //button mouse area
        MouseArea {
            id: tempUp
            anchors.right: imgTemp.right
            anchors.bottom: imgTemp.bottom
            width: imgTemp.width/2
            height: imgTemp.height/2
            onPressed: {
                tempBtnUp.opacity= 1;
                iValue++;
                var value = getKnxTemp(iValue);
                btnClicked(tmpGroupAddr, value);
                txtValue.text = getTempFromKnx(value);
                console.log(getTempFromKnx(value));
            }
            onReleased: {
                tempBtnUp.opacity = 0;
                //imgTemp.source = resourceBase + "temp.png";
            }
        }
    }

    Image {
        id: tempBtnDn
        anchors.bottom: btnTemp.bottom
        width : btnTemp.width
        fillMode: Image.PreserveAspectFit
        source: resourceBase + "tempDownButton_D.png";
        opacity: 0
    }
    Image {
        id: tempBtnUp
        anchors.bottom: btnTemp.bottom
        width : btnTemp.width
        fillMode: Image.PreserveAspectFit
        source: resourceBase + "tempUpButton_D.png";
        opacity: 0
    }

    //button for return to list
    Image {
        id: exit
        height: 80
        width: 80
        source: resourceBase + "back" + resourceResolution
        anchors.left: btnTemp.left
        anchors.top: btnTemp.bottom
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
        anchors.right: btnTemp.right
        anchors.top: btnTemp.bottom
        anchors.topMargin: 10

        MouseArea {
            anchors.fill: parent
            onPressed: {
                sendSettingsReq();
            }
        }
    }

    Text {
        id: txtValue
        font.pointSize: btnTemp.width*50/360
        anchors.horizontalCenter: btnTemp.horizontalCenter
        y: btnTemp.height - 4/6*btnTemp.height

    }

}
