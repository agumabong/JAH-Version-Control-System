#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>
#include <stdio.h>


namespace fs = std::experimental::filesystem;

void check_out(std::string copy_path, std::string source_path )
{
	time_t current_time = time(NULL);
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);
	std::string label_name;

	std::cout << "Enter a label name. If no label name, type 'N'" << std::endl;
	std::cin >> label_name;

	if (label_name == "N" || label_name == "n")
	{
		label_name == "manifest.txt";
	}
	
	//Need 2 steps here: 
	//1) Combine the source path and the original manifest name into a string, do the same with source path and label
	//2) Convert both into const char * for the rename function 
	std::string sp = source_path + "\\manifest.txt";
	const char *sp2 = sp.c_str();
	std::string label2 = source_path + "\\" + label_name;
	std::cout << label2 << std::endl;
	
	if (source_path == copy_path)
	{
		std::cout << "Error, copied path cannot be the same as destination folder." << std::endl;
	}
	else
	{
		fs::copy(copy_path, source_path, fs::copy_options::recursive);		

		std::ofstream fileManifest(source_path);
		const char * label = label2.c_str();
		//std::cout << label << std::endl;
		bool rename_success = rename(sp2, label);
		if (rename_success == true)
		{
			std::cout << "Sucessfully renamed file." << std::endl;
		}
		else
			std::cout << "Error in renaming file." << std::endl;
		
		label_name.insert(0, "\\");
		//const char * label2 = label_name.c_str();
		fileManifest.open(label2, std::ofstream::trunc);
		fileManifest << "File created at:" << timeStr;
	
		
		std::cout << "Successfully copied file path." << std::endl;
	}
}
