
#include <advance_qmake.hpp>

#include <regex>
#include <string>

class Builder{
public:
    std::string fileName;
    std::string functionName;
};

inline void createBuilder(const fs::path & argInputFileName,Builder & argBuilder){
    std::ifstream varReadFile{streamFileName(argInputFileName) ,std::ios::binary};
    static const std::regex fileNameRegex{u8R"===(\s*fileName:(\S+)\s*)==="};
    static const std::regex functionNameRegex{u8R"===(\s*functionName:(\S+)\s*)==="};
    std::string varLine;
    while( varReadFile.good() ){
        std::getline(varReadFile,varLine);
        std::smatch varMatch;
        if(std::regex_search( varLine.cbegin(),varLine.cend(),varMatch,fileNameRegex )){
            argBuilder.fileName = varMatch[1].str();
        } else if(std::regex_search( varLine.cbegin(),varLine.cend(),varMatch,functionNameRegex )){
            argBuilder.functionName = varMatch[1].str();
        }
    }
}

inline void outputBuilder(const fs::path & argInputFileName ,
                          const fs::path & argOutputFileName,
                          const Builder & argBuilder){
    std::ofstream varOutFile{streamFileName(argOutputFileName),std::ios::binary };
    if( false == varOutFile.is_open() ){
        return;
    }
    auto varInputFileName = argInputFileName;
    varInputFileName.replace_filename( argBuilder.fileName );
    std::ifstream varInputFile{ streamFileName(varInputFileName) ,std::ios::binary};
    if( false == varInputFile.is_open() ){
        return;
    }
    varOutFile << "extern const char * "sv;
    varOutFile << argBuilder.functionName ;
    varOutFile <<" ( ) { "sv;
    varOutFile << std::endl;
    varOutFile << "return "sv;
    varOutFile << u8R"=========(u8R"=-=-=-=-=-=-()========="sv;
    varOutFile << varInputFile.rdbuf();
    varOutFile << u8R"=========()=-=-=-=-=-=-")========="sv;
    varOutFile << u8R"(;)";
    varOutFile << std::endl;
    varOutFile << "}";
    varOutFile << std::endl;
}

int main(int,char **argv) {

    const fs::path varInputPath{argv[1]};
    const fs::path varOutputPath{argv[2]};
    Builder varBuilder;

    createBuilder(varInputPath,varBuilder);
    outputBuilder(varInputPath,varOutputPath,varBuilder);

}

