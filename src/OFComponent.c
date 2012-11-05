/*
 *  OFComponent.c
 *  OmnimoteTest
 *
 *  Created by Alex Reyes on 11/14/10.
 *  Copyright 2010 Purdue University. All rights reserved.
 *
 */

#ifndef __OFComponent
#include "OFComponent.h"
#endif
		 
BYTE ComponentNames[MAX_COMPONENTS][NAME_MAX+1];

/***************************************************************
 * Initializes all OFComponent resources
 ***************************************************************/
void initializeComponents(void){
	BYTE i;
	for(i = 0; i < MAX_COMPONENTS; i++){
		// ComponentNames
		ComponentNames[i][0] = OFNullRef;
		ComponentNames[i][NAME_MAX] = OFNullRef;
	}
}

/***************************************************************
 * setComponentName - sets the name associated with component
 * 
 * Returns:
 * TRUE if component name was modified, FALSE otherwise
 *
 ***************************************************************/
OFBool setComponentName(OFComponentRef cmp, unsigned char* name){
	BYTE i;
	if(name == NULL){
		ComponentNames[cmp][0] = OFNullRef;
		return TRUE;
	}
	if(name[0] == OFNullRef) return FALSE;
	if(isComponentValid(cmp) == FALSE) return FALSE;
	for(i = 0; i < NAME_MAX; i++){
		ComponentNames[cmp][i] = name[i];
		if(name[i] == OFNullRef) i = NAME_MAX;
	}
	return TRUE;
}

/***************************************************************
 * getComponentName - gets the name associated with component
 *
 * Returns:
 * name associated with component, 
 * an empty string if component was not active or invalid
 *
 ***************************************************************/
BYTE* getComponentName(OFComponentRef cmp){
	if(isComponentValid(cmp) == FALSE) return NULL;
	return ComponentNames[cmp];
}

/***************************************************************
 * isComponentValid - checks if OFComponentRef value is within valid
 * range
 * 
 * Returns:
 * TRUE if OFComponentRef is valid, FALSE otherwise
 *
 ***************************************************************/
OFBool isComponentValid(OFComponentRef cmp){
	if(cmp < MAX_COMPONENTS) return TRUE;
	return FALSE;
}

/***************************************************************
 * isComponentActive - check if component is in use
 * 
 * Returns:
 * TRUE if component's name is not empty, FALSE otherwise
 *
 ***************************************************************/
OFBool isComponentActive(OFComponentRef cmp){
	if(isComponentValid(cmp) == FALSE) return FALSE;
	if(ComponentNames[cmp][0] == OFNullRef) return FALSE;
	return TRUE;
}

/***************************************************************
 * removeComponent - frees a component by setting it's name 
 * property to an empty string
 *
 * Returns:
 * the same OFComponentRef value if object was removed successfully;
 * OFNullComponentRef otherwise
 *
 ***************************************************************/
OFComponentRef removeComponent(OFComponentRef cmp){
	if(isComponentValid(cmp) == FALSE) return OFNullRef;
	ComponentNames[cmp][0] = OFNullRef;
	return cmp;
}

