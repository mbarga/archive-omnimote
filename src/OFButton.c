/*
 *  OFButtonRef.c
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/13/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#ifndef __OFButton
#include "OFButton.h"
#endif

unsigned char ButtonNames[MAX_BUTTONS][NAME_MAX+1];
OFImageRef ButtonImages[MAX_BUTTONS];
OFCommandRef ButtonCommands[MAX_BUTTONS][MAX_BUTTON_COMMANDS];

/***************************************************************
 * Initializes all OFButton resources
 ***************************************************************/
void initializeButtons(void){
	BYTE i;
	BYTE c;
	for(i = 0; i < MAX_BUTTONS; i++){
		// ButtonNames
		ButtonNames[i][0] = OFNullRef;
		ButtonNames[i][NAME_MAX] = OFNullRef;
		// ButtonImages
		ButtonImages[i] = OFNullRef;
		// ButtonCommands
		for(c = 0; c < MAX_BUTTON_COMMANDS; c++){
			ButtonCommands[i][c] = OFNullRef;
		}
	}
}

/***************************************************************
 * setButtonName - sets the name associated with button
 * 
 * Returns:
 * TRUE if button name was modified, FALSE otherwise
 *
 ***************************************************************/
OFBool setButtonName(OFButtonRef button, BYTE* name){
	BYTE i;
	if(name == NULL){
		ButtonNames[button][0] = OFNullRef;
		return TRUE;
	}
	if(isButtonActive(button) == FALSE) return FALSE;
	if(name[0] == OFNullRef) return FALSE;
	for(i = 0; i < NAME_MAX; i++){
		ButtonNames[button][i] = name[i];
		if(name[i] == OFNullRef) i = NAME_MAX;
	}
	return TRUE;
}

/***************************************************************
 * getButtonName - gets the name associated with button
 *
 * Returns:
 * name associated with button, 
 * an empty string if button was not active or invalid
 *
 ***************************************************************/
BYTE* getButtonName(OFButtonRef button){
	if(isButtonActive(button) == FALSE) return NULL;
	return ButtonNames[button];
}

/***************************************************************
 * addButtonCommand - adds the OFCommandRef at the end of the 
 * OFCommandRef array associated with this button
 * 
 * Returns:
 * TRUE if button command array was modified, FALSE otherwise
 *
 ***************************************************************/
OFBool addButtonCommand(OFButtonRef button, OFCommandRef cmd){
	BYTE i;
	BYTE cnt;
	if(isButtonActive(button) == FALSE) return FALSE;
	//if(isIRCommandActive(cmd) == FALSE) return FALSE;
	cnt = countButtonCommands(button);
	if(cnt == MAX_BUTTON_COMMANDS) return FALSE;
	ButtonCommands[button][cnt] = cmd;
	return TRUE;
}

/***************************************************************
 * removeButtonCommand - removes the OFCommandRef from the 
 * OFCommandRef array associated with this button
 * 
 * Returns:
 * TRUE if button command array was modified, FALSE otherwise
 *
 ***************************************************************/
OFBool removeButtonCommand(OFButtonRef button, OFCommandRef cmd){
	BYTE i;
	OFBool found;
	BYTE cnt;
	
	if(isButtonActive(button) == FALSE) return FALSE;
	if(cmd == OFNullRef) return FALSE;
	cnt = countButtonCommands(button);
	found = FALSE;
	for(i = 0; i < cnt; i++){
		if(found){
			ButtonCommands[button][i-1] = ButtonCommands[button][i];
		}
		if(ButtonCommands[button][i] == cmd){
			found = TRUE;
		}
	}
	if(found) ButtonCommands[button][cnt-1] = OFNullRef;
	return found;
}

/***************************************************************
 * getButtonCommands - gets the array containing all OFCommandRefs
 * associated with this button
 *
 * Returns:
 * the array containing all OFCommandRefs associated with this 
 * button, NULL if button is not valid
 *
 ***************************************************************/
OFCommandRef* getButtonCommands(OFButtonRef button){
	if(isButtonActive(button) == FALSE) return NULL;
	return ButtonCommands[button];
}

/***************************************************************
 * countButtonCommands - counts number of OFCommandRef items 
 * associated with button
 * 
 * Returns:
 * number of OFCommandRef items associated with button
 *
 ***************************************************************/
BYTE countButtonCommands(OFButtonRef button){
	BYTE i;
	if(isButtonActive(button) == FALSE) return 0;
	for(i = 0; i < MAX_BUTTON_COMMANDS; i++){
		if(ButtonCommands[button][i] == OFNullRef) return i;
	}
	return MAX_BUTTON_COMMANDS;
}

/***************************************************************
 * setButtonImage - sets the OFImageRef associated with button
 * 
 * Returns:
 * TRUE if button image was set, FALSE otherwise
 *
 ***************************************************************/
OFBool setButtonImage(OFButtonRef button, OFImageRef image){
	if(isButtonActive(button) == FALSE) return FALSE;
	ButtonImages[button] = image;
	return TRUE;
}

/***************************************************************
 * getButtonImage - gets the OFImageRef associated with button
 *
 * Returns:
 * OFImageRef associated with button, 
 * OFNullRef if button was not active or invalid
 *
 ***************************************************************/
OFImageRef getButtonImage(OFButtonRef button){
	if(isButtonActive(button) == FALSE) return OFNullRef;
	return ButtonImages[button];
}

/***************************************************************
 * isButtonValid - checks if OFButtonRef value is within valid
 * range
 * 
 * Returns:
 * TRUE if OFButtonRef is valid, FALSE otherwise
 *
 ***************************************************************/
OFBool isButtonValid(OFButtonRef button){
	if(button < (OFButtonRef)MAX_BUTTONS) return TRUE;
	return FALSE;
}

 /***************************************************************
 * isButtonActive - check if button is in use
 * 
 * Returns:
 * TRUE if button's name is not empty, FALSE otherwise
 *
 ***************************************************************/
OFBool isButtonActive(OFButtonRef button){
	if(isButtonValid(button) == FALSE) return FALSE;
	if(ButtonNames[button][0] == (unsigned char)OFNullRef) return FALSE;
	return TRUE;
}

/***************************************************************
 * getFreeButton - finds an available button
 * 
 * Returns:
 * OFButtonRef of the available button or OFNullButtonRef if
 * there are no buttons available
 *
 ***************************************************************/
OFButtonRef getFreeButton(){
	BYTE i;
	for(i = 0; i < MAX_BUTTONS; i++){
		OFButtonRef b = i;
		if(isButtonActive(b) == FALSE){
			return b;
		}
	}
	return OFNullRef;
}

/***************************************************************
 * addButton - adds a new button setting the name propery
 * 
 * Parameters: 
 * - char name - name of new button. only first NAME_MAX
 * unsigned characters will be stored
 *
 * Returns:
 * OFButtonRef of the new button or OFNullButtonRef if
 * there are no buttons available or name was NULL
 *
 ***************************************************************/
OFButtonRef addButton(BYTE* name){
	BYTE i;
	OFButtonRef b;
	if(name == NULL) return OFNullRef;
	if(name[0] == OFNullRef) return OFNullRef;
	b = getFreeButton();
	for(i = 0; i < NAME_MAX; i++){
		ButtonNames[b][i] = name[i];
		if(name[i] == OFNullRef) break;
	}
	return b;
}

/***************************************************************
 * removeButton - frees a button by setting it's name property
 * to an empty string
 * 
 * Returns:
 * the same OFButtonRef value if object was removed successfully;
 * OFNullButtonRef otherwise
 *
 ***************************************************************/
OFButtonRef removeButton(OFButtonRef button){
	if(isButtonValid(button) == FALSE) return OFNullRef;
	ButtonNames[button][0] = OFNullRef;
	return button;
}
