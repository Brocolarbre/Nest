#include "CommandProcessor.hpp"

#include <CLI11.hpp>

int main(int argc, char* argv[])
{
	CLI::App cli("C++ project generator with external dependencies and build management", "Nest");
	cli.set_help_all_flag("--help-all", "Expand all help");
	cli.require_subcommand(1);

	bool initCommandApplication = false;
	bool initCommandLibrary = false;

	CLI::App* initCommand = cli.add_subcommand("init", "Create an empty project");
	CLI::Option_group* initCommandOptions = initCommand->add_option_group("init flags", "Type of project to create");
	initCommandOptions->add_flag("--application", initCommandApplication, "Create an application project");
	initCommandOptions->add_flag("--library", initCommandLibrary, "Create an library project");
	initCommandOptions->require_option(1);

	std::string environmentSetCommandVcpkgPath;
	bool environmentSetCommandSkipVcpkg = false;

	CLI::App* environmentCommand = cli.add_subcommand("environment", "Perform an operation on the environment");
	CLI::App* environmentSetCommand = environmentCommand->add_subcommand("set", "Install external dependencies");
	environmentSetCommand->add_option("--vcpkg-path", environmentSetCommandVcpkgPath, "Path to an existing vcpkg installation directory");
	environmentSetCommand->add_flag("--skip-vcpkg", environmentSetCommandVcpkgPath, "Skip vcpkg and external depenndencies installation");
	CLI::App* environmentResetCommand = environmentCommand->add_subcommand("reset", "Uninstall external dependencies");
	environmentCommand->require_subcommand(1);

	std::string workspaceSetCommandTarget;

	CLI::App* workspaceCommand = cli.add_subcommand("workspace", "Perform an operation on the workspace");
	CLI::App* workspaceSetCommand = workspaceCommand->add_subcommand("set", "Generate IDE project files");
	workspaceSetCommand->add_option("--target", workspaceSetCommandTarget, "Premake IDE target (vs2022, gmake, xcode4, codelite)");
	CLI::App* workspaceResetCommand = workspaceCommand->add_subcommand("reset", "Remove IDE project files");
	workspaceCommand->require_subcommand(1);

	CLI::App* buildCommand = cli.add_subcommand("build", "Perform an operation on the build");
	CLI::App* buildClearCommand = buildCommand->add_subcommand("clear", "Remove the build directory");
	buildCommand->require_subcommand(1);

	std::string linesCountCommandRoot;

	CLI::App* linesCommand = cli.add_subcommand("lines", "Perform an operation on the lines");
	CLI::App* linesCountCommand = linesCommand->add_subcommand("count", "Count source files lines");
	linesCountCommand->add_option("--root", linesCountCommandRoot, "Recursive count root");
	linesCommand->require_subcommand(1);

	CLI11_PARSE(cli, argc, cli.ensure_utf8(argv));

	if (initCommand->parsed())
	{
		ProjectType projectType = ProjectType::Application;
		if (initCommandApplication)
			projectType = ProjectType::Application;
		else if (initCommandLibrary)
			projectType = ProjectType::Library;

		CommandProcessor::processInit(projectType);
	}
	else if (environmentCommand->parsed())
	{
		if (environmentSetCommand->parsed())
			CommandProcessor::processEnvironmentSet(environmentSetCommandSkipVcpkg, environmentSetCommandVcpkgPath.empty() ? std::nullopt : std::optional(environmentSetCommandVcpkgPath));
		else if (environmentResetCommand->parsed())
			CommandProcessor::processEnvironmentReset();
	}
	else if (workspaceCommand->parsed())
	{
		if (workspaceSetCommand->parsed())
			CommandProcessor::processWorkspaceSet(workspaceSetCommandTarget.empty() ? std::nullopt : std::optional(workspaceSetCommandTarget));
		if (workspaceResetCommand->parsed())
			CommandProcessor::processWorkspaceReset();
	}
	else if (buildClearCommand->parsed())
	{
		CommandProcessor::processBuildClear();
	}
	else if (linesCountCommand->parsed())
	{
		CommandProcessor::processLinesCount(linesCountCommandRoot.empty() ? std::nullopt : std::optional(linesCountCommandRoot));
	}

	return 0;
}