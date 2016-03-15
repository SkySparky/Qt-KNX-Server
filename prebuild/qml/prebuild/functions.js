var glb_activeItem = 1;
var glb_TransitionType1 = 3;
var glb_obj1=_dummy;
var glb_obj2=_dummy;

function swap(obj1, obj2, type) {
    if (type === 0) {
            obj1.visible = false;
            obj2.visible = true;
            obj2.x = 0;
            obj2.y = 0;
    }
    else if (type === 1) {
        if (glb_activeItem == 1) {
            glb_activeItem = 2;
            _1to2.start();
        }
        else {
            _2to1.start();
            glb_activeItem = 1;
        }
    }
    else if (type === 2) {
        if (glb_activeItem == 1) {
            glb_activeItem = 2;
            _1sl2.start();
        }
        else {
            _2sl1.start();
            glb_activeItem = 1;
        }
    }
    else if (type === 3) {  // Forward
        scr1 = obj1;
        scr2 = obj2;
        obj1.visible = true;
        obj2.visible = true;
        obj1.y = 0;
        obj2.y = 0;
        obj2.x = obj1.width;
         _1to2fwd.start();
    }
    else if (type === 4) {  // Reverse
        scr1 = obj1;
        scr2 = obj2;
        obj1.visible = true;
        obj2.visible = true;
        obj1.y = 0;
        obj2.y = 0;
        obj2.x = -obj2.width;
         _1to2rev.start();
    }
}

//DEV_SWITCH    : 0
//DEV_DIMMER    : 1
//DEV_RGB       : 2
//DEV_SHUTTER   : 3
//DEV_TAGBTN    : 4

// After add (or edit ?) item selection the scr_add must be adjusted for correct properties
// This rputine does excactly that.
//
function setObjType(objType) {
    var startCount = 6; // 5 is minimum
    var nextY = startCount * backstage.buttonHeight + 6 * backstage.buttonSpacerHeight;

    if ( objType === 0)  // On/Off
    {
        // Put the ones needed in wanted order. JUST MOVE THE WHOLE LINE.
        // set the one not needed to -3000.
        //
        add_groupAddr.y =   nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr.btnText = "on/off address";
        add_groupAddr1.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr2.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr3.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr4.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.btnText = "on/off status";
        add_statusAddr1.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr2.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr3.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr4.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;

        addHdr.hdrText = "Add Switch";
        backstage.add_CurrentType = 0;
    }
    else if ( objType === 1) // Dimmer
    {
        // Put the ones needed in wanted order. JUST MOVE THE WHOLE LINE.
        // set the one not needed to -3000.
        //
        add_groupAddr.y =   nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr.btnText = "on/off address";
        add_groupAddr1.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr1.btnText = "dim address";
        add_groupAddr2.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr3.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr4.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.btnText = "on/off status";
        add_statusAddr1.y = nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr1.btnText = "dim status";
        add_statusAddr2.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr3.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr4.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;

        addHdr.hdrText = "Add Dimmer";
        backstage.add_CurrentType = 1;
    }
    else if ( objType === 2) // RGB
    {
        // Put the ones needed in wanted order. JUST MOVE THE WHOLE LINE.
        // set the one not needed to -3000.
        //
        add_groupAddr.y =   nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr.btnText = "on/off address";
        add_groupAddr1.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr1.btnText = "R address";
        add_groupAddr2.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr2.btnText = "G address";
        add_groupAddr3.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr3.btnText = "B address";
        add_groupAddr4.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.btnText = "on/off status";
        add_statusAddr1.y = nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr1.btnText = "R status";
        add_statusAddr2.y = nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr2.btnText = "G status";
        add_statusAddr3.y = nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr3.btnText = "B status";
        add_statusAddr4.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;

        addHdr.hdrText = "Add RGB light";
        backstage.add_CurrentType = 2;
    }
    else if ( objType === 3) // Shutters
    {
        // Put the ones needed in wanted order. JUST MOVE THE WHOLE LINE.
        // set the one not needed to -3000.
        //
        add_groupAddr.y =   nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr.btnText = "up/dn address";
        add_groupAddr1.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr1.btnText = "step up/dn address";
        add_groupAddr2.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr3.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr4.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr1.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr2.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr3.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr4.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;

        addHdr.hdrText = "Add Shutters";
        backstage.add_CurrentType = 3;
    }
    else if ( objType === 4) // Tag button
    {
        // Put the ones needed in wanted order. JUST MOVE THE WHOLE LINE.
        // set the one not needed to -3000.
        //
        add_groupAddr.y =   nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr.btnText = "Insert tag";
        add_groupAddr1.y =  -3000; //nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr2.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr3.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr4.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr1.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr2.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr3.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr4.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;

        addHdr.hdrText = "Add Tag-Button";
        backstage.add_CurrentType = 4;
    }
    else if ( objType === 5)  // Temp
    {
        // Put the ones needed in wanted order. JUST MOVE THE WHOLE LINE.
        // set the one not needed to -3000.
        //
        add_groupAddr.y =   nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr.btnText = "Temperature address";
        add_groupAddr1.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr2.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr3.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_groupAddr4.y =  -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.y =  nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr.btnText = "Temperature status";
        add_statusAddr1.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr2.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr3.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;
        add_statusAddr4.y = -3000; // nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 2 ;

        addHdr.hdrText = "Add Switch";
        backstage.add_CurrentType = 0;
    }

    // For all screens
    //
    add_cancel.y =      nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 1 ;
    add_finish.y =      nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 1 ;
    add_remove.y =      nextY; nextY += backstage.buttonSpacerHeight + backstage.buttonHeight * 1 ;

    // Adjust height of flicjable content
    // Hidden devices are bellow this size and never shown
    //
    flick_add.contentHeight =  nextY;
    backstage.add_CurrentHeight = flick_add.contentHeight ;

}


var tagObjects = new Array ;    // Holds the references to the dynamically created objects
var tagCount = 0;
var tagNewTagCount = 0 ;        // If and how many new rags have been added
var tagSelectedItemCount = 0;   // How many items were selected
var tagListSep = "the";         // Holds the list of tags as a slash "/" seperated multiparams line
var tagSelectedCount = 0;
var tagSeperatorChar ="/";
var btnTagCancel;
var btnTagSave;
var tagNextFreeY=0;

function createList( inputTagString, listType ) {   //  0: Modify existing item's tags, 1: Select New Item's tag, 2: Manage all tags
    // Destroy existing list
    //
    if (tagCount != 0 ) destroyList();

    // Split input tags string into array and count items
    //
    tagListSep = inputTagString; //text_tags.text;
    var tmpTagsList = tagListSep.split(tagSeperatorChar);        // Split on "/" character
    tagCount = tmpTagsList.length - 1;              // First field tell us how many are already selected for the item
    tagSelectedCount = parseInt( tmpTagsList[0] );  // Number of selected items

    if ( tagListSep == "" ) return;

    // Add the "new tag" text edit
    //
    var component = Qt.createComponent("TagButtonAdd.qml");
    tagObjects[0] = component.createObject(flick_Tags.contentItem);
    if ( listType != 3) {
        tagObjects[0].tagY = tagNextFreeY;
        tagNextFreeY += buttonHeight + buttonSpacerHeight;
        tagObjects[0].tagImage = resourceBase + "checkBoxN"  + resourceResolution;
        tagObjects[0].tagAdded.connect( addTag );
    }
    else
        tagObjects[0].tagY = -1000;

    // Create items based on tags and attach to flickable on screen
    //
    var i;
    component = Qt.createComponent("TagButton.qml");    //  Creating a component. Will be instantiated in many copies bellow
    // Todo wait for "if (component.status == Component.Ready)"
    //
    for ( i=1; i<=tagCount; i++ ) {
        tagObjects[i] = component.createObject(flick_Tags.contentItem);
        tagObjects[i].tagY = tagNextFreeY; //(i - 1) * ( buttonHeight + buttonSpacerHeight ) ;              // TODO
        tagNextFreeY += buttonHeight + buttonSpacerHeight;
        tagObjects[i].tagText = tmpTagsList[i];
        tagObjects[i].tagIndex = i;
        if (i<=tagSelectedCount)
        {       // Selected already
            tagObjects[i].tagColor = "silver";
            tagObjects[i].tagImage = resourceBase + "checkBoxY"  + resourceResolution;
            tagObjects[i].tagSelected = 1;
        }
        else
        {       // Not selected tags
            tagObjects[i].tagSelected = 0;
            tagObjects[i].tagImage = resourceBase + "checkBoxN"  + resourceResolution;
            tagObjects[i].tagColor = "grey";
        }
    }

    // Add cancel and save buttons at list bottom
    //
    component = Qt.createComponent("BackStageBtn1.qml");
    btnTagCancel = component.createObject(flick_Tags.contentItem);
    btnTagCancel.y = tagNextFreeY;  //tagCount * buttonHeight;
    tagNextFreeY += buttonHeight + buttonSpacerHeight;
    btnTagCancel.btnText = "Cancel";
    btnTagCancel.btnImage = resourceBase + "back"  + resourceResolution ;

    btnTagSave = component.createObject(flick_Tags.contentItem);
    btnTagSave.y = tagNextFreeY; // (tagCount +1 ) * buttonHeight;
    tagNextFreeY += buttonHeight + buttonSpacerHeight;


    if ( listType == 3 )
    {
        btnTagSave.btnText = "Delete Selected";
        btnTagSave.btnImage = resourceBase + "delete"  + resourceResolution ;
        btnTagSave.btnClicked.connect( btnDeleteClicked );
        btnTagCancel.btnClicked.connect( btnCancel1Clicked );
    }
    else
    {
        btnTagSave.btnText = "Save";
        btnTagSave.btnImage = resourceBase + "ok"  + resourceResolution ;
        btnTagSave.btnClicked.connect( btnSaveClicked );
        btnTagCancel.btnClicked.connect( btnCancelClicked );
    }
    flick_Tags.contentHeight = tagNextFreeY; // (tagCount + 2) * buttonHeight + 400;  // TODO

}

function btnCancelClicked() {
    dbgText.text = "CANCEL";
    swap(scr_tags, scr_add, Functions.glb_TransitionType1 + 1 );
}
function btnCancel1Clicked() {  // For tagMode 3
    dbgText.text = "CANCEL";
    swap(scr_tags, scr_manage, Functions.glb_TransitionType1 + 1 );
}

function btnSaveClicked() {
    dbgText.text = "SAVE";
    //text_tags.text = Functions.composeReplyString(0);
    add_tags_edit = Functions.composeReplyString(1);   // Save only selected items. First token is number of new tags
    //console.log(add_tags_edit);
    swap(scr_tags, scr_add, Functions.glb_TransitionType1 );
}

function btnDeleteClicked() {   // TODO USER VERIFICATION
    dbgText.text = "DELETE";
    add_tags_edit = Functions.filterReplyString( Functions.composeReplyString(1));   // Save only selected items. These will be deleted
    console.log(add_tags_edit);
    notify(26, add_tags_edit);  //26: NOTIFY_STATE_REMOVE_TAGS (see: common.h)
    swap(scr_tags, scr_manage, Functions.glb_TransitionType1 + 1 );
}

function addTag() {
    var tmpText;
    tmpText = "" + (tagCount + 1);

    // Add new tag
    //
    tmpText = composeReplyString(1);
    text_tags.text   = tmpText;
    createList(  tmpText, 0 );    // Recreate all items including not selected ones
    tagNewTagCount++;

}

function destroyList() {
    var i;
    for ( i=0; i<=tagCount; i++ ) {
        tagObjects[i].destroy();
    }
    tagCount = 0;
    tagNextFreeY=0;
    btnTagCancel.destroy();
    btnTagSave.destroy();
}

// After user has selected/deselected/added some tags a string must be returned with only the selected tags
function composeReplyString( includeAllItems ) {
    var i;
    var retString = "";
    var tmptagSeperatorChar = tagSeperatorChar; // "";   // First tag must not have separator
    tagSelectedItemCount = 0;

    if ( includeAllItems == 3 ) {   // Reproduce all items, no sorting  // TODO for add tags
        for ( i=0; i<=tagCount; i++ ) {

            if ( tagObjects[i].tagSelected == 1 ) {
                retString = retString + tmptagSeperatorChar + tagObjects[i].tagText ;
                if ( tagObjects[i].tagSelected == 1) tagSelectedItemCount++;    // Count selected
            }
        }
    }
    else
    {
        // First pass collects only selected items
        //
        for ( i=0; i<=tagCount; i++ ) {

            if ( tagObjects[i].tagSelected == 1 ) {
                retString = retString + tmptagSeperatorChar + tagObjects[i].tagText ;
                //if ( tagObjects[i].tagSelected == 1)
                    tagSelectedItemCount++;    // Count selected
            }
        }

        // Second pass collects not selected items
        //
        for ( i=1; i<=tagCount; i++ ) {
            if ( tagObjects[i].tagSelected == 0 && includeAllItems == 1 ) {
                retString = retString + tmptagSeperatorChar + tagObjects[i].tagText ;
            }
        }

        if ( includeAllItems == 1) {
            retString = tagSelectedItemCount  + retString;
        }
        else
        {
            retString = tagNewTagCount  + retString;
        }

    }
    destroyList();

    return (retString);
}

// Take a full string and return only the selected items indicated by the first number
//
function filterReplyString( inputTagString ) {
    var i=0;
    var tmpStringOut = "";

    // Split input tags string into array and count items
    //
    var tmpTagsList = inputTagString.split(tagSeperatorChar);        // Split on "/" character
    var tmpTagCount = tmpTagsList.length - 1;              // First field tell us how many are already selected for the item
    var tmpTagSelectedCount = parseInt( tmpTagsList[0] );  // Number of selected items

    if (tmpTagCount < tmpTagSelectedCount ) tmpTagSelectedCount = tmpTagCount ;

    for ( i= 1; i <= tmpTagSelectedCount; i++)
    {
        tmpStringOut += tagSeperatorChar + tmpTagsList[i];
    }

    tmpStringOut = "0" + tmpStringOut;

    return ( tmpStringOut );

}
