// =======================================================================
// IMPORTANT NOTICE: 
// This software program ("Software") is a confidential and/or proprietary product of 
// CAE Inc. and is protected by copyright laws. The use of the Software is subject to the 
// terms of the CAE Inc. License Agreement. 
//
// Copyright © 2017. CAE Inc., All Rights Reserved.
// Written by: Massimo Pietracupa
// =======================================================================


//DESCRIPTION
//This is a dispatcher to call entry points to DLLs. We will first get a handle
// on the entry point of the DLL and then execute it at given frequency. timestep
// will be incremented every 1/60th of a second, once 


//THINGS LEFT TO DO:
//1) Input Checking - make sure user doesn't input garbage

#include "GenericDispatcher.h"

int main(int iArgCount, char* iArgs[])
{

	Dispatcher GenericDispatcher(iArgs);

	GenericDispatcher.Loop();
	

	return 0;
}

