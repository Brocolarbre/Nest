#pragma once

#include <optional>
#include <string>

enum class ProjectType
{
	Application = 0,
	Library
};

class CommandProcessor
{
public:
	static void processInit(ProjectType projectType);
	static void processEnvironmentSet(const std::optional<std::string>& vcpkgPath);
	static void processEnvironmentReset();
	static void processWorkspaceSet(const std::optional<std::string>& target);
	static void processWorkspaceReset();
	static void processBuildClear();
};