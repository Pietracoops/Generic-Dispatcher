// =======================================================================
// IMPORTANT NOTICE: 
// This software program ("Software") is a confidential and/or proprietary product of 
// CAE Inc. and is protected by copyright laws. The use of the Software is subject to the 
// terms of the CAE Inc. License Agreement. 
//
// Copyright © 2017. CAE Inc., All Rights Reserved.
// =======================================================================

#pragma once

#include<iostream>
#include<windows.h>
#include "chrono/chrono.hpp"
#include <string>
#include <fstream>

typedef void (WINAPI *PFNC)();

double high_resolution_time();  //Windows
double get_time();				//Boost

class Dispatcher
{

private:

	std::string path = "";
	std::string dllName = "";
	std::string entryPoint = "";
	std::string frequency = "";
	std::string Debug = "";
	std::string fullFileName = "";
	std::string logpath = "";
	std::string logfilename = "\\Generic_Dispatcher_Log.txt";
	std::ofstream fout;
	
	DWORD error;

	double simtime = 0;										// Exact sim time (s)
	double frequencyd = std::stod(frequency);				// Convert frequency to double
	double dt = (1.00000 / frequencyd);						// Delta Time (s)
	double cdt = 0;											// calculated delta (s)
	double t0 = get_time();									// Initial time (s)
	double timestep = 0;									// Sim time in dt steps (s)

	int counter = 1;										// For Debugging
	
	bool DebugMode = false;

	PFNC pFNC;

public:

	//VARIABLES

	Dispatcher(char* inputs[]);
	~Dispatcher();
	void Loop();
};