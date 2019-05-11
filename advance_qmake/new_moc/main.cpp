
#include <advance_qmake.hpp>

#include <regex>
#include <array>
#include <string>

class Builder {
public:
    std::string fileName;
    std::string functionName;
};

inline constexpr const static std::array globalUtf8Bom{ '1','2','4' };

template<typename T>
inline void removeUtf8Bom(T & arg) {
    std::array varTmpBuffer{ '1','2','3' };

}

inline void createBuilder(const fs::path & argInputFileName, Builder & argBuilder) {
    std::ifstream varReadFile{ streamFileName(argInputFileName) ,std::ios::binary };
    static const std::regex fileNameRegex{ u8R"===(\s*fileName:(\S+)\s*)===" };
    static const std::regex functionNameRegex{ u8R"===(\s*functionName:(\S+)\s*)===" };
    std::string varLine;
    removeUtf8Bom(argInputFileName);
    while (varReadFile.good()) {
        std::getline(varReadFile, varLine);
        std::smatch varMatch;
        if (std::regex_search(varLine.cbegin(), varLine.cend(), varMatch, fileNameRegex)) {
            argBuilder.fileName = varMatch[1].str();
        } else if (std::regex_search(varLine.cbegin(), varLine.cend(), varMatch, functionNameRegex)) {
            argBuilder.functionName = varMatch[1].str();
        }
    }
}

inline void outputBuilder(const fs::path & argInputFileName,
    const fs::path & argOutputFileName,
    const Builder & argBuilder) {
    std::ofstream varOutFile{ streamFileName(argOutputFileName),std::ios::binary };
    if (false == varOutFile.is_open()) {
        return;
    }
    auto varInputFileName = argInputFileName;
    varInputFileName.replace_filename(argBuilder.fileName);
    std::ifstream varInputFile{ streamFileName(varInputFileName) ,std::ios::binary };
    if (false == varInputFile.is_open()) {
        return;
    }
    varOutFile.sync_with_stdio(false);
    varOutFile << '\n';
    varOutFile.write(globalUtf8Bom.data(), globalUtf8Bom.size());
    varOutFile << "#include <string_view>"sv;
    varOutFile << '\n';
    varOutFile << "extern std::string_view "sv;
    varOutFile << argBuilder.functionName;
    varOutFile << " ( ) { "sv;
    varOutFile << std::endl;
    varOutFile << "return "sv;
    varOutFile << u8R"=========(u8R"=-=-=-=-=-=-()========="sv;
    varOutFile << varInputFile.rdbuf();
    varOutFile << u8R"=========()=-=-=-=-=-=-"sv)========="sv;
    varOutFile << u8R"(;)";
    varOutFile << '\n';
    varOutFile << "}";
    varOutFile << '\n';
}

int main(int, char **argv) {

    const fs::path varInputPath{ argv[1] };
    const fs::path varOutputPath{ argv[2] };
    Builder varBuilder;

    createBuilder(varInputPath, varBuilder);
    outputBuilder(varInputPath, varOutputPath, varBuilder);

}

