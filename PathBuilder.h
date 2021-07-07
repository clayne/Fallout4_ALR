#pragma once
#include "pch.h"

class PathBuilderParent {
public:

	virtual void findInputFiles() = 0,
		generateInputPaths() = 0,
		correctFiles() = 0,
		generateOutputPaths() = 0,
		findDLLPath() = 0,
		displayErrorMessage(string title, string message) = 0;
	 
	vector<wstring> inputFilePaths;
	array<wstring, MAX_INPUTS> outputPaths;
};

class PathBuilder : public PathBuilderParent {

private:
	vector<string> inputFiles;
	string inputPath, outputPath, iniPath;

	void findInputFiles(),
		generateInputPaths(),
		correctFiles(),
		generateOutputPaths(),
		findDLLPath(),
		displayErrorMessage(string title, string message);

public:

	PathBuilder() {
		findDLLPath();

		ifstream in(iniPath);
		if (!in.is_open()) displayErrorMessage("ALR_ERROR", "ALR.ini Not Found");

		getline(in, inputPath);

		if (inputPath.at(inputPath.size() != '\\')) inputPath.push_back('\\');

		in.close();

		findInputFiles();

		if (inputFiles.size() == 0) displayErrorMessage("ALR_ERROR", "No Files Found In ALR.ini's Path \n Ensure A Full Path Is Being Used EX.\n C:\Program Files (x86)\Steam\screenshots");

		if (inputFilePaths.size() != MAX_INPUTS) correctFiles();

		generateInputPaths();
		generateOutputPaths();
	};
};