#ifndef TASKS_TREENODE_H
#define TASKS_TREENODE_H

    #include <string>
    #include <iostream>

    class TreeNode {
        private:
            float number;
            std::string sign;
            bool _isSign;
            bool _isNumber;
            TreeNode *leftNodePtr;
            TreeNode *rightNodePtr;
        public:
            TreeNode();
            void setNumber(float number);
            float getNumber();
            bool isSign();
            bool isNumber();
            void setSign(std::string sign);
            std::string getSign();
            void setLeftNodePtr(TreeNode *ptr);
            void setRightNodePtr(TreeNode *ptr);
            TreeNode *getLeftNodePtr();
            TreeNode *getRightNodePtr();
            ~TreeNode();
            friend std::ostream& operator<< (std::ostream &out, const TreeNode& tNode);
    };

#endif
