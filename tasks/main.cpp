#include "MathPhraseParser.h"

int main() {
    MathPhraseParser p("((3.0+4.0))+4.0*(5.0-4.0*(1.0-(1.0-1.0)))*2.0+2.0*(3.0+4.0*(2.0-1.0))");
    p.parse();
    p.printPhraseTree();
    p.calculate();
    std::cout << p.getAnswer();
    return 0;
}
