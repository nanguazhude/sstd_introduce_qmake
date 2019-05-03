
#include <advance_qmake.hpp>

int main(int, char ** argv) {
    fs::path varOutPath{ argv[0] };
    varOutPath.replace_filename("before_link.txt"sv);
    std::ofstream varOutStream{ streamFileName(varOutPath) };
    varOutStream << getNow() << std::endl;
}





