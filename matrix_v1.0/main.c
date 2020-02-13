#include <stdio.h>
#include <stdlib.h>



struct Compl {
    float im;
    float re;
};

struct Matrix {
    int n;
    struct Compl ** content;
};

typedef struct Compl complex;
typedef struct Matrix matrix;

void create_complex_num(complex **, float , float);
void create_matrix(matrix **);
void read_num(complex **, char []);
int len_c(char []);
int len_i(int);
int to_int(char []);
int power(int, int);
void print_matrix(complex **, int);
matrix * sum_matrix(matrix *, matrix *);
matrix * create_empty_matrix(int);
matrix * multip_matrix(matrix *, matrix *);
matrix * multip_mat_by_a_scalar(matrix *, complex *);
complex * multip_complex(complex *, complex *);

int main() {
//    complex  *a;
//    create_complex_num(&a, 4.0f, 5.0f);
//    printf("%f + i*%f", a->re, a->im);
//    char s[] = "112.34+i*9.8";
//    char s1[] = "12345";
//    printf("%d", to_int(s1));
//    read_num(&a, s);
//    printf("%f+i*%f", a->re, a->im);
//    char s[] = "qwerty";
//    printf("%d", len_c(s));
//    matrix *a;
//    create_matrix(&a);
//    print_matrix(a->content, a->n);
//    matrix *a;
//    a = create_empty_matrix(4);
//    print_matrix(a->content, a->n);
    matrix *a;
    complex *b;
    matrix *c;
    create_matrix(&a);
    create_complex_num(&b, 2.0f, 0.0f);
    c = multip_mat_by_a_scalar(a, b);
    print_matrix(c->content, c->n);
//    complex *a;
//    complex *b;
//    create_complex_num(&a, 2.0f, 1.0f);
//    create_complex_num(&b, 3.0f, 3.0f);
//    complex *c;
//    c = multip_complex(a, b);
//    printf("%f + i * %f", c->re, c->im);
}

void create_complex_num(complex **cmpl, float re_num, float im_num){
    complex *tmp;
    tmp = (complex *)malloc(sizeof(complex));
    tmp->re = re_num;
    tmp->im = im_num;
    *cmpl = tmp;
}



int len_c(char s[]){
    int i = 0;
    while (s[i] != '\0'){
        ++i;
    }
    return i;
}

matrix * sum_matrix(matrix *a, matrix *b){
    matrix *c;
    int size = a->n;
    c = create_empty_matrix(size);
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            (c->content)[i][j].im = (a->content)[i][j].im + (b->content)[i][j].im;
            (c->content)[i][j].re = (a->content)[i][j].re + (b->content)[i][j].re;
        }
    }
    return c;
}
matrix * multip_mat_by_a_scalar(matrix *a, complex * b){
    matrix *c;
    int size = a->n;
    c = create_empty_matrix(size);
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            (c->content)[i][j].im = (a->content)[i][j].im * b->im;
            (c->content)[i][j].re = (a->content)[i][j].re * b->re;
        }
    }
    return c;
}

complex * multip_complex(complex *a, complex *b){
    complex *c;
    create_complex_num(&c, 0.0f, 0.0f);
    c->re = (a->re * b->re - a->im * b->im);
    c->im = (a->re * b->im + a->im * b->re);
    return c;
}

matrix * multip_matrix(matrix *a, matrix *b){
    matrix *c;
    int size = a->n;
    c = create_empty_matrix(size);
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            for (int k = 0; k < size; ++ k){
                (c->content)[i][j].im += multip_complex(&(a->content[i][k]), &(b->content[k][j]))->im;
                (c->content)[i][j].re += multip_complex(&(a->content[i][k]), &(b->content[k][j]))->re;
            }
        }
    }
    return c;
}

matrix * create_empty_matrix(int size){
    int i, j;
    complex **mat = (complex **) malloc(size * sizeof(complex *));
    for (i = 0; i < size; ++i) {
        mat[i] = (complex *) malloc(size * sizeof(complex));
    }
    complex *buff;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j){
            read_num(&buff, "0.0+i*0.0");
            mat[i][j].re = buff->re;
            mat[i][j].im = buff->im;
        }
    }
    matrix *smat;
    smat = (matrix *)malloc(sizeof(matrix));
    smat->n = size;
    smat->content = mat;
    return smat;
}

void read_num(complex **c, char input[]){
    int l = len_c(input), flag = 0, i = 0;
    while (input[i] != '\0'){
        if (input[i] == 'i'){
            flag = 1;
        }
        ++i;
    }
    char *buffs = (char *)malloc(0 * sizeof(char));
    int i_re, f_re, i_im, f_im, j;
    if (flag){
        i = 0;
        while (input[i] != '.'){
            buffs = (char *)realloc(buffs,(i + 1) * sizeof(char));
            buffs[i] = input[i];
            ++i;
        }
        i_re = to_int(buffs);
        free(buffs);
        buffs = (char *)malloc(0 * sizeof(char));
        j = 0;
        ++i;
        while(input[i] != '+'){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        f_re = to_int(buffs);
        free(buffs);
        i += 3;
        j = 0;
        buffs = (char *)malloc(0 * sizeof(char));
        while(input[i] != '.'){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        i_im = to_int(buffs);
        free(buffs);
        buffs = (char *)malloc(0 * sizeof(char));
        j = 0;
        ++i;
        while(input[i] != '\0'){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        f_im = to_int(buffs);
        free(buffs);
        create_complex_num(c, (float)i_re + (float)f_re / (float)power(10, len_i(f_re)), (float)i_im + (float)f_im / (float)power(10, len_i(f_im)));
    }
    else {
        i = 0;
        while (input[i] != '.'){
            buffs = (char *)realloc(buffs,(i + 1) * sizeof(char));
            buffs[i] = input[i];
            ++i;
        }
        i_re = to_int(buffs);
        free(buffs);
        buffs = (char *)malloc(0 * sizeof(char));
        j = 0;
        ++i;
        while(input[i] != '\0'){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        f_re = to_int(buffs);
        free(buffs);
        i_im = 0;
        f_im = 0;
        create_complex_num(c, (float)i_re + (float)f_re / (float)power(10, len_i(f_re)), (float)i_im + (float)f_im / (float)power(10, len_i(f_im)));
    }
}

int to_int(char s[]){
    int l = len_c(s), i = 0, ans = 0;
    while (s[i] != '\0'){
        ans += (int)(s[i] - '0') * power(10, l - 1);
        --l;
        ++i;
    }
    return ans;
}

int power(int x, int y){
    int i = 0, ans = 1;
    for (i; i < y; ++i){
        ans *= x;
    }
    return ans;
}

int len_i(int x){
    int ans = 0;
    ans = (x == 0 ? 1 : ans);
    while (x > 0){
        x /= 10;
        ++ans;
    }
    return ans;
}

void create_matrix(matrix **pmat){
    matrix *smat;
    smat = (matrix *)malloc(sizeof(matrix));
    char *row = (char *)malloc(0 * sizeof(char));
    int c;
    int i = 0;
    while ((c = getchar()) != '\n'){
        row = (char *)realloc(row, (i + 1) * sizeof(char));
        row[i] = (char)c;
        ++i;
    }
    row = (char *)realloc(row, (i + 1) * sizeof(char));
    row[i] = '\0';
    int size = 0;
    i = 0;
    while (row[i] != '\0'){
        if (row[i] == ' '){
            ++size;
        }
        ++i;
    }
    ++size;
    smat->n = size;
    complex **mat = (complex**)malloc(size * sizeof(complex *));
    for (i = 0; i < size; ++i){
        mat[i] = (complex *)malloc(size * sizeof(complex));
    }
    int j;
    i = 0;
    int k;
    complex *buff;
    for (j = 0; j < size; ++j){
        char *buffs = (char *)malloc(0 * sizeof(char));
        k = 0;
        while ((row[i] != ' ') && (row[i] != '\0')){
            buffs = (char *)realloc(buffs,(k + 1) * sizeof(char));
            buffs[k] = row[i];
            ++i;
            ++k;
        }
        ++i;
        buffs = (char *)realloc(buffs,(k + 1) * sizeof(char));
        buffs[k] = '\0';
        read_num(&buff, buffs);
        mat[0][j].re = buff->re;
        mat[0][j].im = buff->im;
        free(buffs);
    }
    free(row);
    int t;
    for (i = 1; i < size; ++i){
        t = 0;
        row = (char *)malloc(0 * sizeof(char));
        while ((c = getchar()) != '\n'){
            row = (char *)realloc(row, (t + 1) * sizeof(char));
            row[t] = (char)c;
            ++t;
        }
        row = (char *)realloc(row, (t + 1) * sizeof(char));
        row[t] = '\0';
        k = 0;
        for (j = 0; j < size; ++j){
            char *buffs = (char *)malloc(0 * sizeof(char));
            t = 0;
            while ((row[k] != ' ') && (row[k] != '\0')){
                buffs = (char *)realloc(buffs,(t + 1) * sizeof(char));
                buffs[t] = row[k];
                ++k;
                ++t;
            }
            ++k;
            buffs = (char *)realloc(buffs,(t + 1) * sizeof(char));
            buffs[t] = '\0';
            read_num(&buff, buffs);
            mat[i][j].re = buff->re;
            mat[i][j].im = buff->im;
            free(buffs);
        }
        free(row);
    }
    smat->content = mat;
    *pmat = smat;
}

void print_matrix(complex **mat, int n){
    int i, j, size = n;
    for (i = 0; i < size; ++i){
        for (j = 0; j < size; ++j) {
            printf("%.1f + i * %.1f\t", (*(mat + i) + j)->re, (*(mat + i) + j)->im);
        }
        printf("\n");
    }
}