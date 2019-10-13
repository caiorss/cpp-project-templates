#include <iostream>
#include <string>
#include <cassert>

//---- Library Headers -----------------//
#include <CLI/CLI.hpp>


int main(int argc, char* argv[])
{
    CLI::App app{ "cli-app"};
    app.footer("\n Command line application for managing processes and applications.");

    //----- Run subcommand settings -----------------//
    //...............................................//

    // Subcommand: run
    CLI::App* cmd_run  = app.add_subcommand(
         "run"
        ,"Run some application"
        );

    // Positional argument of subcommand run (required)
    std::string cmd_run_application = ".";
    cmd_run->add_option("<APPLICATION>", cmd_run_application
                        , "Application to be launched as daemon")->required();

    // Optional argument of subcommand run
    bool cmd_run_flag_exec = false;
    cmd_run->add_flag("-e,--exec", cmd_run_flag_exec
                      , "Run application in the current terminal.");

    std::string cmd_run_directorty = ".";
    cmd_run->add_flag("-d,--directory", cmd_run_directorty
                      , "Set process current directory");


    //----- Path subcommand settings -----------------//
    //................................................//

    // Subcommand path: Show all directories listed
    // in path environment variable.
    CLI::App* cmd_path = app.add_subcommand(
         "path"
        ,"Show content of $PATH environment variable"
        );

    //----- Relaunch command settings -----------------//
    //.................................................//

    // Subcommand relaunch: Relaunch process given its PID (Process ID)
    CLI::App* cmd_relaunch = app.add_subcommand(
         "relaunch-pid"
        ,"Relaunch a process, given its PID"
        );

    int pid_to_relaunch;
    cmd_relaunch->add_option("<PID>", pid_to_relaunch
                             , "PID of application to be relaunched")->required();

    std::string relaunch_pid_directory = ".";
    cmd_relaunch->add_option("-d,--directory", relaunch_pid_directory
                             , "Current working directory.");


    //=============================================//
    // ------ Parse and validade arguments -------//

    app.require_subcommand();    

    try
    {
        app.validate_positionals();
        app.parse(argc, argv);
    } catch(const CLI::ParseError &e)
    {
        return (app).exit(e);
    } catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    //------------ Program Actions --------------------//

    // Command: run => Launch a process
    if(*cmd_run){
        std::cout << std::boolalpha;
        std::cout << " [INFO] Running subcommand <<RUN>>" << std::endl;
        std::cout << "  =>>                  Application  = " << cmd_run_application << std::endl;
        std::cout << "  =>>          Run in terminal flag = " << cmd_run_flag_exec << std::endl;
        std::cout << "  =>>     Process current directory = " << cmd_run_directorty << std::endl;

        return EXIT_SUCCESS;
    }

    // Command: path show directories in PATH environment variable
    if(*cmd_path)
    {
        std::cout << " [INFO] Subcommand PATH => Show all directories listed in $PATH"
                  << std::endl
                  << " environment variable"
                  << std::endl;
        return  EXIT_SUCCESS;
    }

    if(*cmd_relaunch)
    {
        std::cout << " [INFO] Subcommand RELAUNCH-PID" << std::endl;
        std::cout << " =>>  PID = " << pid_to_relaunch << std::endl;
        std::cout << " =>>  CWD = " << relaunch_pid_directory << std::endl;

        return EXIT_SUCCESS;
    } 
	
	return EXIT_SUCCESS;
}
