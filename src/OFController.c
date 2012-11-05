/*
 *  OController.c
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/13/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#ifndef __OFController
#include "OFController.h"
#endif
				 
unsigned char ControllerNames[MAX_CONTROLLERS][NAME_MAX+1];
OFButtonRef ControllerButtons[MAX_CONTROLLERS][MAX_CONTROLLER_BUTTONS];

/***************************************************************
 * Initializes all OFController resources
 ***************************************************************/
void initializeControllers(void){
	int i;
	int b;
	for(i = 0; i < MAX_CONTROLLERS; i++){
		// ControllerNames
		ControllerNames[i][0] = OFNullRef;
		ControllerNames[i][NAME_MAX] = OFNullRef;
		// ControllerButtons
		for(b = 0; b < MAX_CONTROLLER_BUTTONS; b++){
			ControllerButtons[i][b] = OFNullRef;
		}
	}
}

/***************************************************************
 * setControllerName - sets the name associated with controller
 * 
 * Returns:
 * TRUE if controller name was modified, FALSE otherwise
 *
 ***************************************************************/
OFBool setControllerName(OFControllerRef ctrl, unsigned char* name){
	int i;
	if(name == NULL){
		ControllerNames[ctrl][0] = OFNullRef;
		return TRUE;
	}
	if(isControllerActive(ctrl) == FALSE) return FALSE;
	if(name[0] == OFNullRef) return FALSE;
	for(i = 0; i < NAME_MAX; i++){
		ControllerNames[ctrl][i] = name[i];
		if(name[i] == OFNullRef) i = NAME_MAX;
	}
	return TRUE;
}

/***************************************************************
 * getControllerName - gets the name associated with controller
 *
 * Returns:
 * name associated with controller, 
 * an empty string if controller was not active or invalid
 *
 ***************************************************************/
unsigned char* getControllerName(OFControllerRef ctrl){
	if(isControllerActive(ctrl) == FALSE) return NULL;
	return ControllerNames[ctrl];
}

/***************************************************************
 * addControllerButton - adds the OFButtonRef at the end of the 
 * OFButtonRef array associated with this button
 * 
 * Returns:
 * TRUE if controller button array was modified, FALSE otherwise
 *
 ***************************************************************/
OFBool addControllerButton(OFControllerRef ctrl, OFButtonRef btn){
	BYTE i;
	BYTE cnt;
	if(isControllerActive(ctrl) == FALSE) return FALSE;
	if(isButtonActive(btn) == FALSE) return FALSE;
	cnt = countControllerButtons(ctrl);
	if(cnt == MAX_CONTROLLER_BUTTONS) return FALSE;
	for(i = 0; i < cnt; i++){
		if(ControllerButtons[ctrl][i] == btn) return FALSE;
	}
	ControllerButtons[ctrl][cnt] = btn;
	return TRUE;
}

/***************************************************************
 * removeControllerButton - removes the OFButtonRef from the 
 * OFButtonRef array associated with this controller
 * 
 * Returns:
 * TRUE if controller button array was modified, FALSE otherwise
 *
 ***************************************************************/
OFBool removeControllerButton(OFControllerRef ctrl, OFButtonRef btn){
	int i;
	OFBool found;
	BYTE cnt;
	if(isControllerActive(ctrl) == FALSE) return FALSE;
	if(isButtonValid(btn) == FALSE) return FALSE;
	cnt = countControllerButtons(ctrl);
	found = FALSE;
	for(i = 0; i < cnt; i++){
		if(found){
			ControllerButtons[ctrl][i-1] = ControllerButtons[ctrl][i];
		}		
		if(ControllerButtons[ctrl][i] == btn){
			found = TRUE;
		}
	}
	if(found) ControllerButtons[ctrl][cnt-1] = OFNullRef;
	return found;
}

/***************************************************************
 * getControllerButtons - gets the array containing all OFButtonRefs
 * associated with this controller
 *
 * Returns:
 * the array containing all OFButtonRefs associated with this 
 * controller, NULL if controller is not valid
 *
 ***************************************************************/
OFButtonRef* getControllerButtons(OFControllerRef ctrl){
	if(isControllerActive(ctrl) == FALSE) return NULL;
	return ControllerButtons[ctrl];
}

/***************************************************************
 * countControllerButtons - counts number of OFButtonRef items 
 * associated with controller
 * 
 * Returns:
 * number of OFButtonRef items associated with controller
 *
 ***************************************************************/
unsigned char countControllerButtons(OFControllerRef ctrl){
	int i;
	if(isControllerActive(ctrl) == FALSE) return 0;
	for(i = 0; i < MAX_CONTROLLER_BUTTONS; i++){
		if(ControllerButtons[ctrl][i] == OFNullRef) return i;
	}
	return MAX_CONTROLLER_BUTTONS;
}

/***************************************************************
 * isControllerValid - checks if OFControllerRef value is within valid
 * range
 * 
 * Returns:
 * TRUE if OFControllerRef is valid, FALSE otherwise
 *
 ***************************************************************/
OFBool isControllerValid(OFControllerRef ctrl){
	if(ctrl < MAX_CONTROLLERS) return TRUE;
	return FALSE;
}

/***************************************************************
 * isControllerActive - check if controller is in use
 * 
 * Returns:
 * TRUE if controller's name is not empty, FALSE otherwise
 *
 ***************************************************************/
OFBool isControllerActive(OFControllerRef ctrl){
	if(isControllerValid(ctrl) == FALSE) return FALSE;
	if(ControllerNames[ctrl][0] == OFNullRef) return FALSE;
	return TRUE;
}

/***************************************************************
 * getFreeController - finds an available controller
 * 
 * Returns:
 * OFControllerRef of the available controller or OFNullRef if
 * there are no controllers available
 *
 ***************************************************************/
OFControllerRef getFreeController(void){
	BYTE i;
	for(i = 0; i < MAX_CONTROLLERS; i++){
		OFControllerRef c = (OFControllerRef) i;
		if(isControllerActive(c) == FALSE){
			return c;
		}
	}
	return OFNullRef;
}

/***************************************************************
 * addController - adds a new controller setting the name propery
 * 
 * Parameters: 
 * - char name - name of new controller. only first NAME_MAX
 * unsigned characters will be stored
 *
 * Returns:
 * OFControllerRef of the new controller or OFNullRef if
 * there are no controllers available or name was NULL
 *
 ***************************************************************/
OFControllerRef addController(unsigned char* name){
	BYTE i;
	OFControllerRef c;
	if(name == NULL) return OFNullRef;
	c = getFreeController();
	for(i = 0; i < NAME_MAX; i++){
		ControllerNames[c][i] = name[i];
		if(name[i] == OFNullRef) break;
	}
	return c;
}

/***************************************************************
 * removeController - frees a controller by setting it's name 
 * property to an empty string
 *
 * Returns:
 * the same OFControllerRef value if object was removed successfully;
 * OFNullRef otherwise
 *
 ***************************************************************/
OFControllerRef removeController(OFControllerRef ctrl){
	if(isControllerValid(ctrl) == FALSE) return OFNullRef;
	ControllerNames[ctrl][0] = OFNullRef;
	return ctrl;
}

