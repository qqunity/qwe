#ifndef SORTER_UNITTESTS_HPP
#define SORTER_UNITTESTS_HPP

#include <iostream>
#include "Exceptions.hpp"
#include <vector>

namespace unitTests {
    enum statusCode {
        successTesting = 1,
        waitingForTesting = 0,
        testingError = -1
    };

    enum testMarks {
        skip = 0,
        pass = 1,
        error = -1,
        wait = 2
    };

    template<typename Function>
    class Test {
    private:
        std::string testName;
        Function functionUnderTest;
        int testStatus;
        std::string testMessage;
        bool isTestNegative;
    public:
        Test(Function func, const std::string &testName, bool isTestNegative);

        void startTest();

        void getTestResult();

        int getTestStatus();

        std::string getTestName();

        std::string getTestMessage();

        ~Test();
    };

    template<typename Function>
    Test<Function>::Test(Function func, const std::string &testName, bool isTestNegative) {
        this->testName = testName;
        this->functionUnderTest = func;
        this->testStatus = statusCode::waitingForTesting;
        this->isTestNegative = isTestNegative;
        this->testMessage = "NULL";
    }

    template<typename Function>
    void Test<Function>::startTest() {
        try {
            if (this->functionUnderTest()) {
                this->testStatus = statusCode::successTesting;
                this->testMessage = "Pass the <" + this->testName + "> test!";
            } else {
                this->testStatus = statusCode::testingError;
                this->testMessage = "Error in the <" + this->testName + "> test!";
            }
        }
        catch (exceptions::ArrayException &exception) {
            if (this->isTestNegative) {
                this->testStatus = statusCode::successTesting;
                this->testMessage = "Pass the <" + this->testName + "> test!";
            } else {
                this->testStatus = statusCode::testingError;
                this->testMessage = "Error in the <" + this->testName + "> test!" + " | \x1b[31m" +
                                    "An array exception occurred ( " + exception.what() + " )\x1b[0m";
            }
        }
        catch (exceptions::ArrayElementException &exception) {
            if (this->isTestNegative) {
                this->testStatus = statusCode::successTesting;
                this->testMessage = "Pass the <" + this->testName + "> test!";
            } else {
                this->testStatus = statusCode::testingError;
                this->testMessage = "Error in the <" + this->testName + "> test!" + " | \x1b[31m" +
                                    "An array element exception occurred ( " + exception.what() + " )\x1b[0m";
            }
        }
        catch (exceptions::LinkedListException &exception) {
            if (this->isTestNegative) {
                this->testStatus = statusCode::successTesting;
                this->testMessage = "Pass the <" + this->testName + "> test!";
            } else {
                this->testStatus = statusCode::testingError;
                this->testMessage = "Error in the <" + this->testName + "> test!" + " | \x1b[31m" +
                                    "A linked list exception occurred ( " + exception.what() + " )\x1b[0m";
            }
        }
        catch (exceptions::ListElementException &exception) {
            if (this->isTestNegative) {
                this->testStatus = statusCode::successTesting;
                this->testMessage = "Pass the <" + this->testName + "> test!";
            } else {
                this->testStatus = statusCode::testingError;
                this->testMessage = "Error in the <" + this->testName + "> test!" + " | \x1b[31m" +
                                    "A list element exception occurred ( " + exception.what() + " )\x1b[0m";
            }
        }
        catch (std::exception &exception) {
            if (this->isTestNegative) {
                this->testStatus = statusCode::successTesting;
                this->testMessage = "Pass the <" + this->testName + "> test!";
            } else {
                this->testStatus = statusCode::testingError;
                this->testMessage = "Error in the <" + this->testName + "> test!" + " | \x1b[31m" +
                                    "Some other std::exception occurred ( " + exception.what() + " )\x1b[0m";
            }
        }
    }

    template<typename Function>
    void Test<Function>::getTestResult() {
        if (this->testStatus == statusCode::testingError) {
            std::cout << "\x1b[31mERR\x1b[0m" << "  | " + this->testMessage + " |" << std::endl;
        } else if (this->testStatus == statusCode::successTesting) {
            std::cout << "\x1b[32mOK\x1b[0m" << "   | " + this->testMessage + " |" << std::endl;
        } else if (this->testStatus == statusCode::waitingForTesting) {
            std::cout << "WAIT | Waiting the <" + this->testName + "> test! |" << std::endl;
        }
    }

    template<typename Function>
    int Test<Function>::getTestStatus() {
        return this->testStatus;
    }

    template<typename Function>
    std::string Test<Function>::getTestName() {
        return this->testName;
    }

    template<typename Function>
    std::string Test<Function>::getTestMessage() {
        return this->testMessage;
    }

    template<typename Function>
    Test<Function>::~Test() = default;


    template<typename Function>
    class UnitTests {
    private:
        std::vector<Test<Function>> tests;

        std::vector<int> testsConditions;

        unsigned int testsCount;
    public:
        UnitTests();

        void addTest(Function testFunc, std::string testName, bool isTestNegative);

        void eraseTeset(unsigned int index);

        void skipTest(unsigned int index);

        void startTest(unsigned int index);

        void startTests(unsigned int *testIds, unsigned int n);

        void startTests();

        ~UnitTests();
    };

    template<typename Function>
    UnitTests<Function>::UnitTests() {
        this->testsCount = 0;
    }

    template<typename Function>
    void UnitTests<Function>::addTest(Function testFunc, std::string testName, bool isTestNegative) {
        Test newTest(testFunc, testName, isTestNegative);
        this->tests.push_back(newTest);
        this->testsConditions.push_back(testMarks::wait);
        ++this->testsCount;
    }

    template<typename Function>
    void UnitTests<Function>::eraseTeset(unsigned int index) {
        this->tests.erase(this->tests.begin() + index);
        this->testsConditions.erase(this->testsConditions.begin() + index);
        --this->testsCount;
    }

    template<typename Function>
    void UnitTests<Function>::skipTest(unsigned int index) {
        this->testsConditions[index] = testMarks::skip;
    }

    template<typename Function>
    void UnitTests<Function>::startTest(unsigned int index) {
        if (this->testsConditions[index] == testMarks::wait) {
            std::cout << "Test " << index << " | ";
            this->tests[index].startTest();
            this->tests[index].getTestResult();
            this->testsConditions[index] = this->tests[index].getTestStatus();
        } else if (this->testsConditions[index] == testMarks::skip) {
            std::cout << "Test " << index << " | " << "\x1b[33mSKIP\x1b[0m" << " | Skip the <"
                      << this->tests[index].getTestName() << "> test! |" << std::endl;
        } else if (this->testsConditions[index] == testMarks::error) {
            std::cout << "Test " << index << " | " << "\x1b[31mERR\x1b[0m"
                      << "  | " + this->tests[index].getTestMessage() + " |" << std::endl;
        } else if (this->testsConditions[index] == testMarks::pass) {
            std::cout << "Test " << index << " | " "\x1b[32mOK\x1b[0m"
                      << "   | " + this->tests[index].getTestMessage() + " |" << std::endl;
        }
    }

    template<typename Function>
    void UnitTests<Function>::startTests(unsigned int *testIds, unsigned int n) {
        for (int i = 0; i < n; ++i) {
            this->startTest(testIds[i]);
        }
    }

    template<typename Function>
    void UnitTests<Function>::startTests() {
        for (int i = 0; i < this->testsCount; ++i) {
            this->startTest(i);
        }
    }

    template<typename Function>
    UnitTests<Function>::~UnitTests() = default;
}


#endif
