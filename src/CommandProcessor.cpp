#include "CommandProcessor.hpp"
#include "Template/ApplicationTemplate.hpp"
#include "Template/LibraryTemplate.hpp"
#include "ZipExtractor.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

void CommandProcessor::processInit(ProjectType projectType)
{
	std::cout << "Initializing project...";

	std::string archiveName("Project.zip");
	std::string directoryName("Project");

	if (std::filesystem::exists(archiveName) || std::filesystem::exists(directoryName))
	{
		std::cerr << "\nA file named '" << archiveName << "' or a directory named '" << directoryName << "' already exists in the current directory" << std::endl;
		return;
	}

	std::ofstream projectArchive(archiveName, std::ios::binary);

	switch (projectType)
	{
	case ProjectType::Application:
		projectArchive.write(reinterpret_cast<const char*>(applicationTemplateData), applicationTemplateDataLength);
		break;
	case ProjectType::Library:
		projectArchive.write(reinterpret_cast<const char*>(libraryTemplateData), libraryTemplateDataLength);
		break;
	}

	projectArchive.close();

	ZipExtractor::extract(archiveName, "");
	std::filesystem::remove_all(archiveName);

	std::cout << " Done." << std::endl;
}

void CommandProcessor::processEnvironmentSet(bool skipVcpkg, const std::optional<std::string>& vcpkgPath)
{
	std::string arguments;
	if (!skipVcpkg)
		arguments = "--skip-vcpkg";
	else if (vcpkgPath.has_value())
		arguments = std::string(" --vcpkg-path \"") + std::filesystem::path(vcpkgPath.value()).string() + "\"";

#ifdef _WIN32
	if (std::system(std::string("cmd /c .\\scripts\\windows\\set_environment.bat" + arguments).c_str()) == -1)
        std::cerr << "set_environment.bat failed" << std::endl;
#else
	if (std::system(std::string("bash ./scripts/linux/set_environment.sh" + arguments).c_str()) == -1)
        std::cerr << "set_environment.sh failed" << std::endl;
#endif
}

void CommandProcessor::processEnvironmentReset()
{
#ifdef _WIN32
	if (std::system("cmd /c .\\scripts\\windows\\reset_environment.bat") == -1)
        std::cerr << "reset_environment.bat failed" << std::endl;
#else
	if (std::system("bash ./scripts/linux/reset_environment.sh") == -1)
        std::cerr << "reset_environment.sh failed" << std::endl;
#endif
}

void CommandProcessor::processWorkspaceSet(const std::optional<std::string>& target)
{
	std::string arguments(target.has_value() ? std::string(" --target ") + target.value() : "");
#ifdef _WIN32
	if (std::system(std::string("cmd /c .\\scripts\\windows\\set_workspace.bat" + arguments).c_str()) == -1)
        std::cerr << "set_workspace.bat failed" << std::endl;
#else
	if (std::system(std::string("bash ./scripts/linux/set_workspace.sh" + arguments).c_str()) == -1)
        std::cerr << "set_workspace.sh failed" << std::endl;
#endif
}

void CommandProcessor::processWorkspaceReset()
{
#ifdef _WIN32
	if (std::system("cmd /c .\\scripts\\windows\\reset_workspace.bat") == -1)
        std::cerr << "reset_workspace.bat failed" << std::endl;
#else
	if (std::system("bash ./scripts/linux/reset_workspace.sh") == -1)
        std::cerr << "reset_workspace.sh failed" << std::endl;
#endif
}

void CommandProcessor::processBuildClear()
{
#ifdef _WIN32
	if (std::system("cmd /c .\\scripts\\windows\\clear_build.bat") == -1)
        std::cerr << "clear_build.bat failed" << std::endl;
#else
	if (std::system("bash ./scripts/linux/clear_build.sh") == -1)
        std::cerr << "clear_build.sh failed" << std::endl;
#endif
}

void CommandProcessor::processLinesCount()
{
#ifdef _WIN32
	if (std::system("cmd /c .\\scripts\\windows\\count_lines.bat") == -1)
		std::cerr << "count_lines.bat failed" << std::endl;
#else
	if (std::system("bash ./scripts/linux/count_lines.sh") == -1)
		std::cerr << "count_lines.sh failed" << std::endl;
#endif
}