# include "shell.h"
/*
    A shell has two main components : 
        Commands - which are executable tokens that connect the console to the back of the application
        Interpreter - which is responsible to provide an interface for a user to run commands saved on the interpreter
*/
class Command
{
    private:
        std::string name; // name of the command
        std::string help; // help string of the command
        std::string argsHelp;
        void (*method)(int, char const *[], char*);   // method associated with each command 
    public:
        /**
         * @brief Command
         * * Command class complete constructor
         * ? input:
         * ? output:
         */
        Command( std::string nam, std::string hel, std::string args, void (*meth)(int, char const *[], char *) = 0 ) //Class Constructor
        {
            //include exception throw when name and help strings are empty
            if ( nam.length() == 0 ){
                throw "Command name is empty.\n";
            } else {
                name = nam;
            }
            if ( hel.length() == 0 ){
                throw "Command help is empty.\n";
            } else {
                help = hel;
            }
            if ( args.length() == 0 ){
                argsHelp = "none";
            } else {
                argsHelp = args;
            }
            // test for no method parsed
            if ( meth == 0 ){ 
                throw "Command's associated method is empty.\n";
            } else {
                method = meth;
            }
            
        }

        std::string getHelp()// execute the help function
        {   
            return name + " - " + help;
        }

        std::string getArgsHelp()
        {
            return argsHelp;
        }

        std::string getName()
        {
            return name;
        }

        void execute(int argc, char const *argv[], char *outputHist) // call function associated with the command
        {
            try{
                (*method)(argc, argv, outputHist);
            } catch(const char* ex) {
                std::cerr << ex <<std::endl;
            }
        }
};

class Interpreter
{ 
    private:
        std::map<std::string, Command> commandDict; // dictionary of commands indexed by its own name (faster search results)
        std::vector<std::string> commandStack; // command buffer for an automatic feedthrough of console commands
        std::string historyFileName = "clic_cnsl_hstry.txt";
        std::string promptMessage = "clic#$>";
        std::string argumentDelimiter = " ";
        std::string parameterDelimiter = "--";
        const int MAXCHAR_ARGV = 125;
        const int MAXARGS = 15;
        const int MAXCHAR_CMDNAME = 15;
        //std::ofstream historyFile; // history file to save the executed commands and their outputs
        // take an input string and pre process it
        bool preProcessCommand(std::string inputBuffer, char* cmdName, int* argc, char* (*argv[]))
        { 
            std::vector<std::string> tokens;
            size_t endPos = 0;
            size_t initPos = 0;
            // save the found space delimited tokens on the tokens vector
            while((endPos = inputBuffer.find(argumentDelimiter,endPos)) != std::string::npos)
            {
                tokens.push_back(inputBuffer.substr(initPos,endPos));
                initPos = endPos+argumentDelimiter.length();
                endPos = initPos;
            }
            //the first found token should be the command name
            try{
                strcpy(cmdName, tokens[0].c_str());
            } catch(const char * ex1) {
                std::cerr << ex1 << std::endl;
                return false;
            }
            //the remaining tokens have to be delimmited by the parameter delimiter inside their own callback methods
            // and these tokens have to bne parsed from string to char vector
            *argc = 0;
            try{
                for(std::vector<std::string>::iterator it = tokens.begin() ; it != tokens.end() ; ++it){
                    strcpy(*argv[*argc], (*it).c_str());
                }
            } catch(const char * ex2) {
                std::cerr << ex2 << std::endl;
                return false;
            }
            return true;
        }
        // print message and read resulting command
        std::string promptUser(std::string promptMsg)
        {
            std::string inputBuffer;
            // prompt user for new input
            std::cout << promptMsg;
            std::getline(std::cin, inputBuffer);
            return inputBuffer;
        }
        
        //todo : complete save state argument functionality
        // special command 1 - // exit command
        void shell_exit(int argc, char const *argv[])
        { 
            int exitIndex;
            std::string receivedParam;
            std::vector<std::string> variables = {
                "ss", // save state
                "ei" // exit index
            };
            std::vector<std::string> tokens;
            if( argc > 0 ){
                size_t endPos;
                size_t initPos;
                std::string arg;
                std::string var;
                //process the argv string
                for(int i = 0; i < argc; i++){
                    endPos = 0;
                    initPos = 0;
                    receivedParam = std::string(argv[i]); // transform the char array into a c++ string
                    // save the found "--" delimited tokens on the tokens vector
                    while((endPos = receivedParam.find(parameterDelimiter)) != std::string::npos){
                        tokens.push_back(receivedParam.substr(initPos,endPos));
                        initPos = endPos+parameterDelimiter.length();
                    }
                    //after obtaining the tokens, obtain the values and the arguments for them
                    if(tokens.size() != 2){
                        throw sformat("Unexpected number of received arguments. Expected : 2; Received : {}.\n", std::to_string( tokens.size() ).c_str() );
                    } else {
                        var = tokens.at(0);
                        arg = tokens.at(1);
                        tokens.pop_back();
                        tokens.pop_back();// clear the tokens vector for the next processed command
                        if( var.compare( variables.at(0) ) == 0 ){
                            //TODO - treat for this comparison - save all program state
                        } else if( var.compare( variables.at(1) ) == 0 ) {
                            try{
                                exitIndex = std::stoi(arg);
                            } catch (const char * ex2) {
                                std::cerr << ex2 << std::endl;
                            }
                        } else {
                            throw sformat("Unexected argument received : {}.\n", var.c_str());
                        }
                    }
                }
            } else {
                exitIndex = 0; // exit with null return, without save
            }
            exit(exitIndex); // exit program
            
        }

        std::string exitHelp()// exiting function help
        {
            return "exit - [description] : leave speedster application - [commands] : ss--[(char) y/n ] save state, ei--[(int) 0-3] application exit state parameter";
        }
        
        // special command 2 // to read command lines from a text file and store them in a buffer
        void automaticCommandFeedthrough(int argc, char *argv[], char *outputHist)
        { 
            std::vector<std::string> variables = {
                "f" //file variable
            };
            std::string noTxtFilePathExcept = "No text file path was received.";
            std::vector<std::string> tokens;
            std::string receivedParam;
            bool receivedTextFilePath = false;
            // from argv get the filepath of the text file to read the commands
            // while reading through the parsed filepath, add these commands to the command buffer as strings
            if( argc > 0 ){
                size_t endPos;
                size_t initPos;
                std::string arg;
                std::string var;
                //process the argv string
                for(int i = 0; i < argc; i++){
                    endPos = 0;
                    initPos = 0;
                    receivedParam = std::string(argv[i]); // transform the char array into a c++ string
                    // save the found "--" delimited tokens on the tokens vector
                    while((endPos = receivedParam.find(parameterDelimiter)) != std::string::npos){
                        tokens.push_back(receivedParam.substr(initPos,endPos));
                        initPos = endPos+parameterDelimiter.length();
                    }
                    //after obtaining the tokens, obtain the values and the arguments for them
                    if( tokens.size() != 2 ){
                        throw sformat( "Unexpected number of received arguments. Expected : 2; Received : {}.\n", std::to_string( tokens.size() ).c_str() );
                    } else {
                        var = tokens.at(0);
                        arg = tokens.at(1);
                        tokens.pop_back();
                        tokens.pop_back();// clear the tokens vector for the next processed command
                        if( var.compare( variables.at(0) ) == 0 ){
                            // at least one file was received
                            receivedTextFilePath = true;
                            // arg holds the text file path
                            // try to open the file 
                            try{
                                std::ifstream commandFile(arg); // open to append info
                                std::string line;
                                if (commandFile.is_open())
                                {
                                    while( std::getline(commandFile, line) ){
                                        commandStack.push_back(line); // read each command line from the file and append it to the command Stack
                                    }
                                } else {
                                    throw sformat("Unable to open file in path : {}.\n", arg.c_str());
                                }
                                
                            } catch(const char * ex) {
                                throw std::string(ex) + "\n";
                            }
                        } else {
                            throw sformat("Unexected argument received : {}.\n", var.c_str());
                        }
                    }
                }
                if(!receivedTextFilePath){
                    throw "No text file path was received.\n";
                }
            } else {
                throw "No argument was parsed after the [acf] command.\n";
            }
            return;
        }
        
        std::string acfHelp() // automatic commmand feedthrough help
        {
            return "acf - [description] : automatic command feedthrough - [commands] : f--[(string) *filepath* ] text file path of commands.";
        }

        void setupNewHistoryEntry(){// setup the latest history file entry with the current date and time
            // open text file
            std::ofstream historyFile;
            try{
                historyFile.open(historyFileName, std::ios::app); // open to append info
            } catch(const char * ex) {
                std::cerr << ex << std::endl;
                historyFile.open(historyFileName, std::ios::trunc); // open file to overwrite
            }
            // get present date and time and convert to string
            time_t now = time(0);
            char* nowDateTime = ctime(&now); 
            // write present date and time to history file
            historyFile << nowDateTime << std::endl;
            // close text file
            historyFile.close();
            return;
        }

        void updateHistory( char* historyMsg ){// update the history file with the latest run command or obtained output
            // open text file to append
            std::ofstream historyFile;
            historyFile.open(historyFileName, std::ios::app);
            // append message
            historyFile << historyMsg << std::endl;
            // close file again
            historyFile.close();
            return;
        }

        void help()// interpreter help
        {
            std::string cmdArgSeparator = "\t";
            std::cout << "--- speedster help ---" << std::endl;
            for(std::map<std::string, Command>::iterator it = commandDict.begin(); it != commandDict.end(); it++){
                std::cout << (*it).first << " : " << (*it).second.getHelp() << cmdArgSeparator 
                    << "args : " << (*it).second.getArgsHelp() << std::endl;
            }
            std::cout << acfHelp() << std::endl;
            std::cout << exitHelp() << std::endl;
        }

    public:
        Interpreter(){}; // constructor

        void overWriteHistoryFileName(std::string newHistoryFileName){
            if (newHistoryFileName.length() == 0) {throw "New history file path is empty.\n";} 
            else{historyFileName = newHistoryFileName;} 
        }

        void addCommand(    std::string name, 
                            std::string help, 
                            std::string argHelp, 
                            void (*method)(int, char const *[], char *) )
        {
            try{
                // create new command
                Command *cmd = new Command(name, help, argHelp, method);
                // add this command to the commandDict
                commandDict.insert({name, *cmd});
            } catch (  const char* ex ) {
                std::cerr << ex << std::endl;
            }
        }

        // constructor with args
        Interpreter(    std::vector<std::string> commandNames, 
                        std::vector<std::string> commandHelps,  
                        std::vector<std::string> commandArgHelps, 
                        std::vector<void (*)(int, char const *[], char *)> commandMethods, 
                        std::string& newHistoryFileName)
        {
            overWriteHistoryFileName(newHistoryFileName);
            // test for equal sizes in the parsed vectors
            if(! (commandNames.size() == commandHelps.size() & commandNames.size() == commandMethods.size() & commandNames.size() == commandArgHelps.size()) ){
                throw "Parsed vectors are not equal in size.\n"; 
            } else {
                // build the command dict dictionary
                for(int i = 0; i < commandNames.size(); i++){
                    //create a new command
                    addCommand( commandNames.at(i), 
                                commandHelps.at(i), 
                                commandArgHelps.at(i), 
                                commandMethods.at(i) 
                    );
                }
            }
        };
        
        void setUpPromptMessage(const std::string newPromptMsg = "clic#$>")
        {
            promptMessage = newPromptMsg;
        }

        void setUpArgumentDelimiter(const std::string newArgDelimiter = "")
        {
            argumentDelimiter = newArgDelimiter;
        }

        void setUpParameterDelimiter(const std::string newParamDelimiter = "--")
        {
            parameterDelimiter = newParamDelimiter;
        }

        int run(){// main loop of the shell's command interpreter
            //setup a new history file entry
            setupNewHistoryEntry();
            while(true){
                std::string inputBuffer;
                char *outputHistory;
                char **argv;
                char *cmdName;
                int argc;

                if (commandStack.size() == 0)               // if there are no commands in stack
                    inputBuffer = promptUser(promptMessage);// prompt the user for a new command
                else{                                       // if, otherwise, there are commands to attend to in the stack
                    inputBuffer = commandStack.back();      // get the last item of the stack
                    commandStack.pop_back();                // and pop the last item out of the stack
                }
                //preprocess the received user command to extract command name and its arguments/parameters
                if( preProcessCommand(inputBuffer, cmdName, &argc, &argv) ){
                    // if the received command is valid
                    //after extracting the command name, arguments and parameters, try to execute command
                    std::string cmdMapName(cmdName);
                    if ( cmdMapName == "help" ) {
                        help();
                    } else if (cmdMapName == "exit"){
                        shell_exit(argc, argv);
                    } else if (cmdMapName == "aci"){
                        automaticCommandFeedthrough(argc, argv, outputHistory);
                    } else {
                        try{
                            commandDict.at(cmdMapName).execute(argc, argv, outputHistory);
                        } catch (const char * ex){
                            std::cerr << ex << std::endl;
                        }
                    }
                    std::cout << outputHistory << std::endl;
                }
            }
        } 

};
