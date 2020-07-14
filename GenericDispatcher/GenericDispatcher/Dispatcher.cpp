#include "GenericDispatcher.h"

Dispatcher::Dispatcher(char* inputs[])
{
	//=================================================//
	//================== CONSTRUCTOR ==================//
	//=================================================//



	//Getting log path from environment variable ===============================================================================================//
	if (const char* env_p = std::getenv("CAE_LOG"))																								//
	{																																			//
		logpath = env_p + logfilename;																											//
		fout.open(logpath.c_str());																												//
		std::cout << "Log created at: " << logpath << std::endl;																				//
	}																																			//
	//==========================================================================================================================================//


	//Parsing Inputs ===========================================================================================================================//
	if (inputs[1])	path = inputs[1];							//FIle Path UI																	//
	else fout << "ERROR: DLL Path not specified. " << std::endl; return;																		//
																																				//
	if (inputs[2])	dllName = inputs[2];						//DLL Name UI																	//
	else fout << "ERROR: DLL name not specified. " << std::endl; return;																		//
																																				//
	if (inputs[3])	entryPoint = inputs[3];						//Entry Point function UI														//
	else fout << "ERROR: Entry Point not specified. " << std::endl; return;																		//
																																				//
	if (inputs[4])	frequency = inputs[4];						//Frequency UI (Hz)																//
	else fout << "ERROR: Frequency not specified. " << std::endl; return;																		//
																																				//
	fullFileName = path + "\\" + dllName;						//Combining the path and the dll name											//
																																				//
	if (inputs[5])																																//
	{																																			//
		Debug = inputs[5];										//Debug (Seconds)																//
		DebugMode = true;																														//
		fout << "Debug Mode Initiated" << std::endl;																							//
	}																																			//
	//==========================================================================================================================================//


	// Enable Debug Mode =======================================================================================================================//
	if (DebugMode)																																//
	{																																			//
		try {																																	//
			Sleep(std::stoi(Debug) * 1000);						//Sleep in milliseconds															//
		}																																		//
		catch (const std::exception& e) {																										//
			fout << "ERROR: Cannot convert " << Debug << " to an integer - please try again. " << e.what() << std::endl;						//
			return;																																//
		}																																		//
	}																																			//
	//==========================================================================================================================================//


	// LOADING LIBRARY AND GETTING ENTRY POINT =================================================================================================//
	HMODULE dll = LoadLibrary(fullFileName.c_str());		// Load the DLL																		//
	if (NULL == dll) fout << "ERROR: DLL not found. | " << dll << std::endl; return;															//
																																				//
	pFNC = (PFNC)GetProcAddress(dll, entryPoint.c_str());	// Get Entry point of DLL															//
	if (NULL == pFNC) fout << "ERROR: Entry point not found. | " << entryPoint.c_str() << std::endl; return;									//
																																				//
																																				//
	//==========================================================================================================================================//


	fout << "Dispatcher Initialization: Complete - " << fullFileName << " | Entry Point: " << entryPoint << " | Frequency: " << frequency << std::endl;
}

Dispatcher::~Dispatcher() {

};

void Dispatcher::Loop()
{


	while (true)
	{
		simtime = (get_time() - t0);
		cdt = (simtime - timestep);
		if (DebugMode) fout << "Current Time: " << simtime << " | timestep: " << timestep << std::endl;

		if (cdt >= dt && cdt <= 2 * dt)
		{
			pFNC();												//Call Function

			if (DebugMode) fout << "Function call count: " << counter << " | " << "time: " << timestep << std::endl; //For Debugging
			counter++; //For Debugging
			timestep += dt;										//increment step
		}
		else if (cdt >= 2 * dt)
		{
			// We skipped an iteration lets get back on track
			timestep = ((int)simtime / dt) * dt;
		}
		else if (cdt < dt)
		{
			if (DebugMode) fout << "Sleeping..." << dt - cdt << std::endl;
			Sleep((dt - cdt) * 1000);
		}
	}



}