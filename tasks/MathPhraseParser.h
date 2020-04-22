#ifndef TASKS_MATHPHRASEPARSER_H
#define TASKS_MATHPHRASEPARSER_H

    #include "TreeNode.h"
    #include <vector>
    #include <iostream>
    #include <algorithm>

    class MathPhraseParser {
        private:
            std::string phrase;
            std::vector<TreeNode *> subTrees;
            int headIndex;
            float answer;
            void firstStageParser();
            void secondStageParser();
            void thirdStageParser();
            float subCalculate(TreeNode *node);
        public:
            MathPhraseParser(std::string phrase);
            void parse();
            void printPhraseTree();
            void calculate();
            float getAnswer();
            ~MathPhraseParser();
    };


#endif
