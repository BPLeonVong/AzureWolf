#include "AzureWolfStd.h"

#include "AW_Application.h"

using namespace AW;

Application* Application::MYApplication = 0;
Command* Application::TheCommand = 0;
std::string Application::DirPath;
Application::EntryPoint Application::Run = 0;


Application::Application()
{
}

Application::~Application()
{
}


int main(int numArguments, char* arguments[])
{
    InitTerm::ExecuteInitializers();

	std::string directory;
	

	Application::TheCommand = new0 Command(numArguments,arguments);
	int exitCode = Application::Run(numArguments,arguments);
	delete0(Application::TheCommand);

	InitTerm::ExecuteTerminators();

	return exitCode;
}