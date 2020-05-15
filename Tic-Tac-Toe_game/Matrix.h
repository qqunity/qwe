#ifndef TIC_TAC_TOE_GAME_MATRIX_H
#define TIC_TAC_TOE_GAME_MATRIX_H

#include "Optional.h"

template<typename T>
class Matrix {
private:
    unsigned int cntRows;
    unsigned int cntColumns;
    Optional<T> **data;
public:
    Matrix();

    Matrix(const Matrix<T> &mat);

    Matrix(unsigned int m, unsigned int n);

    void setValue(unsigned int i, unsigned int j, T val);

    T &getValue(unsigned int i, unsigned int j);

    void swap(unsigned int i1, unsigned int j1, unsigned int i2, unsigned int j2);

    unsigned int *shape();

    void setShape(const unsigned int *shape);

    Matrix<T> &operator=(const Matrix<T> &mat);

    Matrix<T> operator+(const Matrix<T> &mat);

    Matrix<T> operator-(const Matrix<T> &mat);

    Matrix<T> operator*(const Matrix<T> &mat);

    Matrix<T> operator*(T lambda);

    Matrix<T> transpose();

    Optional<T> *operator[](unsigned int i);

    bool operator==(const Matrix<T> &mat);

    bool operator!=(const Matrix<T> &mat);

    template<typename T1>
    friend std::ostream &operator<<(std::ostream &out, Matrix<T1> mat);

    ~Matrix();
};

template<typename T>
Matrix<T>::Matrix() {
    this->cntColumns = 0;
    this->cntRows = 0;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &mat) {
    this->cntRows = mat.cntRows;
    this->cntColumns = mat.cntColumns;
    this->data = new Optional<T> *[this->cntRows];
    for (unsigned int i = 0; i < this->cntRows; ++i) {
        this->data[i] = new Optional<T>[this->cntColumns];
    }
    for (unsigned int i = 0; i < this->cntRows; ++i) {
        for (unsigned int j = 0; j < this->cntColumns; ++j) {
            this->data[i][j] = mat.data[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(unsigned int m, unsigned int n) {
    this->cntRows = m;
    this->cntColumns = n;
    this->data = new Optional<T> *[this->cntRows];
    for (unsigned int i = 0; i < this->cntRows; ++i) {
        this->data[i] = new Optional<T>[this->cntColumns];
    }
}

template<typename T>
unsigned int *Matrix<T>::shape() {
    auto shape = new unsigned int[2];
    shape[0] = this->cntRows;
    shape[1] = this->cntColumns;
    return shape;
}

template<typename T>
void Matrix<T>::setValue(unsigned int i, unsigned int j, T val) {
    if (i >= 0 && i < this->cntRows && j >= 0 && j < this->cntColumns) {
        this->data[i][j] = val;
    } else {
        throw Exception("Index out of range!", __LINE__, __FILE__);
    }
}

template<typename T>
T &Matrix<T>::getValue(unsigned int i, unsigned int j) {
    if (i >= 0 && i < this->cntRows && j >= 0 && j < this->cntColumns) {
        return this->data[i][j];
    } else {
        throw Exception("Index out of range!", __LINE__, __FILE__);
    }
}

template<typename T1>
std::ostream &operator<<(std::ostream &out, Matrix<T1> mat) {
    if (mat.cntColumns != 0 && mat.cntRows) {
        for (unsigned int i = 0; i < mat.cntRows; ++i) {
            for (unsigned int j = 0; j < mat.cntColumns; ++j) {
                out << mat.data[i][j] << " ";
            }
            out << '\n';
        }
    } else {
        out << "None";
    }
    return out;
}

template<typename T>
void Matrix<T>::swap(unsigned int i1, unsigned int j1, unsigned int i2, unsigned int j2) {
    if (i1 >= 0 && i1 < this->cntRows && j1 >= 0 && j1 < this->cntColumns && i2 >= 0 && i2 < this->cntRows && j2 >= 0 &&
        j2 < this->cntColumns) {
        T buffEl = this->data[i1][j1];
        this->data[i1][j1] = this->data[i2][j2];
        this->data[i2][j2] = buffEl;
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &mat) {
    if (this == &mat) {
        return *this;
    }
    for (unsigned int i = 0; i < this->cntRows; ++i) {
        delete[] this->data[i];
    }
    this->cntColumns = mat.cntColumns;
    this->cntRows = mat.cntRows;
    this->data = new Optional<T> *[this->cntRows];
    for (unsigned int i = 0; i < this->cntRows; ++i) {
        this->data[i] = new Optional<T>[this->cntColumns];
    }
    for (unsigned int i = 0; i < this->cntRows; ++i) {
        for (unsigned int j = 0; j < this->cntColumns; ++j) {
            this->data[i][j] = mat.data[i][j];
        }
    }
    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &mat) {
    if (this->cntRows == mat.cntRows && this->cntColumns == mat.cntColumns) {
        for (unsigned int i = 0; i < this->cntRows; ++i) {
            for (unsigned int j = 0; j < this->cntColumns; ++j) {
                if (this->data[i][j] != mat.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    } else {
        throw Exception("It is not possible to compare matrices with different shapes", __LINE__, __FILE__);
    }
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T> &mat) {
    return !(*this == mat);
}

template<typename T>
Optional<T> *Matrix<T>::operator[](unsigned int i) {
    if (i >= 0 && i < this->cntRows) {
        return this->data[i];
    } else {
        throw Exception("Index out of range!", __LINE__, __FILE__);
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat) {
    if (this->cntRows == mat.cntRows && this->cntColumns == mat.cntColumns) {
        Matrix<T> buffMat(*this);
        for (unsigned int i = 0; i < this->cntRows; ++i) {
            for (unsigned int j = 0; j < this->cntColumns; ++j) {
                buffMat[i][j] = buffMat[i][j] + mat.data[i][j];
            }
        }
        return buffMat;
    } else {
        throw Exception("It is not possible to add matrices with different shapes!", __LINE__, __FILE__);
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &mat) {
    if (this->cntRows == mat.cntRows && this->cntColumns == mat.cntColumns) {
        Matrix<T> buffMat(*this);
        for (unsigned int i = 0; i < this->cntRows; ++i) {
            for (unsigned int j = 0; j < this->cntColumns; ++j) {
                buffMat[i][j] = buffMat[i][j] - mat.data[i][j];
            }
        }
        return buffMat;
    } else {
        throw Exception("It is not possible to subtract matrices with different shapes!", __LINE__, __FILE__);
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &mat) {
    if (this->cntColumns == mat.cntRows) {
        Matrix<T> buffMat(this->cntRows, mat.cntColumns);
        for (unsigned int i = 0; i < this->cntRows; ++i) {
            for (unsigned int j = 0; j < mat.cntColumns; ++j) {
                buffMat[i][j] = this->data[i][0] * mat.data[0][j];
                for (unsigned int k = 1; k < this->cntColumns; ++k) {
                    buffMat[i][j] = buffMat[i][j] + this->data[i][k] * mat.data[k][j];
                }
            }
        }
        return buffMat;
    } else {
        throw Exception("It is not possible to subtract matrices with different shapes!", __LINE__, __FILE__);
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T lambda) {
    Matrix<T> buffMat(this->cntRows, this->cntColumns);
    for (unsigned int i = 0; i < this->cntColumns; ++i) {
        for (unsigned int j = 0; j < this->cntRows; ++j) {
            buffMat[i][j] = this->data[i][j] * lambda;
        }
    }
    return buffMat;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix<T> buffMat(this->cntColumns, this->cntRows);
    for (unsigned int i = 0; i < this->cntColumns; ++i) {
        for (unsigned int j = 0; j < this->cntRows; ++j) {
            buffMat[i][j] = this->data[j][i];
        }
    }
    return buffMat;
}

template<typename T>
void Matrix<T>::setShape(const unsigned int *shape) {
    if (this->cntRows == 0 && this->cntColumns == 0) {
        this->cntRows = shape[0];
        this->cntColumns = shape[1];
        this->data = new Optional<T> *[this->cntRows];
        for (unsigned int i = 0; i < this->cntRows; ++i) {
            this->data[i] = new Optional<T>[this->cntColumns];
        }
    }
    else {
        throw Exception("You can't change the shape of the matrix!", __LINE__, __FILE__);
    }
}

template<typename T>
Matrix<T>::~Matrix() = default;

#endif
