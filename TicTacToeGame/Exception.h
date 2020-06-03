#ifndef TIC_TAC_TOE_GAME_EXCEPTION_H
#define TIC_TAC_TOE_GAME_EXCEPTION_H

#include <exception>
#include <string>


class Exception : public std::exception {
private:
    std::string errorMessage;
public:
    Exception(std::string errMsg, unsigned int lineWithErr, std::string fileWithErr);

    const char *what() const noexcept override;

    ~Exception();
};


#endif
