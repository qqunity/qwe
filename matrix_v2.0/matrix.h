
#ifndef MATRIX_V2_0_MATRIX_H
#define MATRIX_V2_0_MATRIX_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>


    struct Compl {
        float im;
        float re;
    };

    struct Matrix {
        int n;
        void ***content;
        int element_size;
        char **tcontent;
    };

    typedef struct Compl complex;
    typedef struct Matrix matrix;

    void create_matrix(matrix **, int);
    void set_matrix_item(matrix **, int, int, void *, char);
    void *get_matrix_item(matrix **, int, int, char *);
    void fill_matrix(matrix **);
    void print_matrix(matrix **);

    void sum_matrix(matrix **, matrix **, matrix **);
    void multip_matrix(matrix **, matrix **, matrix **);

    int is_complex(char []);
    void create_complex_num(complex **, float , float);
    complex *multip_complex(complex *, complex *);
    void convert_to_complex_num(complex **, char []);
    void multip_mat_by_a_scalar(matrix **, void *, matrix **, char);


    int len_c(char []);
    int to_int(char []);
    int len_i(int);
    int power(int, int);
    char *read_str();
    char **cut_str(char []);
    void convert_to_float_num(float *, char []);

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

    complex *multip_complex(complex *a, complex *b){
        complex *c;
        create_complex_num(&c, 0.0f, 0.0f);
        c->re = (a->re * b->re - a->im * b->im);
        c->im = (a->re * b->im + a->im * b->re);
        return c;
    }

    int is_complex(char s[]){
        int c, i = 0, flag = 0;
        while(s[i] != '\0'){
            if (s[i] == 'i'){
                flag = 1;
            }
            ++i;
        }
        return flag;
    }

    void convert_to_complex_num(complex **c, char input[]){
        int i = 0;
        float sgn_re, sgn_im;
        char *buffs = (char *)malloc(0 * sizeof(char));
        int i_re, f_re, i_im, f_im, j;
        sgn_re = (input[0] == '-' ? -1.0f : 1.0f);
        int u = (sgn_re == -1.0f ? 1 : 0);
        i += u;
        while (input[i] != '.'){
            buffs = (char *)realloc(buffs,(i - u + 1) * sizeof(char));
            buffs[i - u] = input[i];
            ++i;
        }
        buffs = (char *)realloc(buffs,(i - u) * sizeof(char));
        buffs[i - u] = '\0';
        i_re = to_int(buffs);
        free(buffs);
        buffs = (char *)malloc(0 * sizeof(char));
        j = 0;
        ++i;

        while((input[i] != '+') && (input[i] != '-')){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        buffs = (char *)realloc(buffs,(j) * sizeof(char));
        buffs[j] = '\0';
        f_re = to_int(buffs);
        free(buffs);
        sgn_im = (input[i] == '-' ? -1.0f : 1.0f);
        i += 3;
        j = 0;
        buffs = (char *)malloc(0 * sizeof(char));
        while(input[i] != '.'){
            buffs = (char *)realloc(buffs,(j + 1) * sizeof(char));
            buffs[j] = input[i];
            ++i;
            ++j;
        }
        buffs = (char *)realloc(buffs,(j) * sizeof(char));
        buffs[j] = '\0';
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
        buffs = (char *)realloc(buffs,(j) * sizeof(char));
        buffs[j] = '\0';
        f_im = to_int(buffs);
        free(buffs);
        create_complex_num(c, sgn_re * ((float)i_re + (float)f_re / (float)power(10, len_i(f_re))), sgn_im * ((float)i_im + (float)f_im / (float)power(10, len_i(f_im))));
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

    char *read_str(){
        int c, i = 0;
        char *s = (char *)malloc(0 * sizeof(char));
        while ((c = getchar()) != '\n'){
            s = (char *)realloc(s, (i + 1) * sizeof(char));
            s[i] = (char)c;
            ++i;
        }
        s = (char *)realloc(s, i  * sizeof(char));
        s[i] = '\0';
        return s;
    }

    char **cut_str(char s[]){
        char **cs = (char **)malloc(0 * sizeof(char *));
        char *buffs = (char *)malloc(0 * sizeof(char));
        int i = 0, k = 0, t =0;
        while(s[i] != '\0'){
            if (s[i] == ' '){
                buffs = (char *)realloc(buffs, k * sizeof(char));
                buffs[k] = '\0';
                k = 0;
                cs = (char **)realloc(cs, (t + 1) * sizeof(char *));
                cs[t] = buffs;
                buffs = (char *)malloc(0 * sizeof(char));
                ++t;
                ++i;
            }
            buffs = (char *)realloc(buffs, (k + 1) * sizeof(char));
            buffs[k] = s[i];
            ++k;
            ++i;
        }
        buffs = (char *)realloc(buffs, k * sizeof(char));
        buffs[k] = '\0';
        cs = (char **)realloc(cs, (t + 1) * sizeof(char *));
        cs[t] = buffs;
        return cs;
    }

    void convert_to_float_num(float *x, char input[]){
        int i = 0;
        float sgn = (input[0] == '-' ? -1.0f : 1.0f);
        int c = (sgn == -1.0f ? 1 : 0);
        int i_num, f_num, j;
        float num;
        char *buffs = NULL;
        i += c;
        while (input[i] != '.'){
            buffs = (char *)realloc(buffs,(i - c + 1) * sizeof(char));
            buffs[i - c] = input[i];
            ++i;
        }
        i_num = to_int(buffs);
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
        f_num = to_int(buffs);
        free(buffs);
        num = (float)i_num + ((float)f_num / (float)power(10, len_i(f_num)));
        *x = num * sgn;
    }

    void create_matrix(matrix **psmat, int size){
        matrix *npsmat;
        npsmat = (matrix *)malloc(sizeof(matrix));
        void ***mat = (void ***)malloc(size * sizeof(void **));
        for (int i = 0; i < size; ++i){
            mat[i] = malloc(size * sizeof(void *));
        }
        char **tmat = (char **)malloc(size * sizeof(char *));
        for (int i = 0; i < size; ++i){
            tmat[i] = (char *)malloc(size * sizeof(char));
        }
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                tmat[i][j] = 'n';
            }
        }
        npsmat->n = size;
        npsmat->content = mat;
        npsmat->tcontent = tmat;
        *psmat = npsmat;
    }

    void set_matrix_item(matrix **mat, int row_i, int column_i, void *value, char type){
        matrix *psmat = *mat;
        void **pitem = &(psmat->content[row_i][column_i]);
        void **pvalue = &value;
        memcpy(pitem, pvalue, sizeof(void *));
        psmat->tcontent[row_i][column_i] = type;
    }

    void *get_matrix_item(matrix **mat, int row_i, int column_i, char *type){
        matrix *psmat = *mat;
        void *value = psmat->content[row_i][column_i];
        *type =  psmat->tcontent[row_i][column_i];
        return value;
    }

    void fill_matrix(matrix **mat){
        matrix *psmat = *mat;
        int size = psmat->n;
        char *sinput;
        char **cutsinput;
        complex *cvaluse;
        float *fvalue;
        int i = 0, j;
        while (i < size){
            sinput = read_str();
            cutsinput = cut_str(sinput);
            j = 0;
            while (j < size){
                if(is_complex(cutsinput[j])){
                    cvaluse = (complex *)malloc(sizeof(complex));
                    convert_to_complex_num(&cvaluse, cutsinput[j]);
                    set_matrix_item(mat, i, j, cvaluse,'c');
                }
                else {
                    fvalue = (float *)malloc(sizeof(float));
                    convert_to_float_num(fvalue, cutsinput[j]);
                    set_matrix_item(mat, i, j, fvalue, 'f');
                }
                ++j;
            }
            ++i;
        }
    }

    void print_matrix(matrix **mat){
        matrix *psmat = *mat;
        void *value;
        complex *cvalue;
        float *fvalue;
        char type;
        int size = psmat->n;
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                value = get_matrix_item(mat, i, j, &type);
                if (type == 'c'){
                    cvalue = (complex *)value;
                    printf("%.2f+i*(%.2f)\t", cvalue->re, cvalue->im);
                }
                else if (type == 'f'){
                    fvalue = (float *)value;
                    printf("%.2f\t", *fvalue);
                }
            }
            printf("\n");
        }
    }

    void sum_matrix(matrix **a, matrix **b, matrix **c){
        matrix *pa = *a;
        matrix *pb = *b;
        matrix *pc = *c;
        char ta, tb;
        void *aval;
        void *bval;
        float *fvalue;
        complex *cvalue;
        int size = pa->n;
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                aval = get_matrix_item(a, i, j, &ta);
                bval = get_matrix_item(b, i, j, &tb);
                if ((ta == 'f') && (tb == 'f')){
                    pc->tcontent[i][j] = 'f';
                    fvalue = (float *)malloc(sizeof(float));
                    *fvalue = (*((float *)aval) + *((float *)bval));
                    set_matrix_item(c, i, j, fvalue, 'f');
                }
                else if ((ta == 'c') && (tb == 'c')){
                    pc->tcontent[i][j] = 'c';
                    create_complex_num(&cvalue, ((complex *)aval)->re + ((complex *)bval)->re, ((complex *)aval)->im + ((complex *)bval)->im);
                    set_matrix_item(c, i, j, cvalue, 'c');
                }
                else if ((ta == 'f') && (tb == 'c')){
                    pc->tcontent[i][j] = 'c';
                    fvalue = (float *)malloc(sizeof(float));
                    fvalue = (float *)aval;
                    create_complex_num(&cvalue, *fvalue + ((complex *)bval)->re, ((complex *)bval)->im);
                    set_matrix_item(c, i, j, cvalue, 'c');
                }
                else if ((ta == 'c') && (tb == 'f')){
                    pc->tcontent[i][j] = 'c';
                    fvalue = (float *)malloc(sizeof(float));
                    fvalue = (float *)bval;
                    create_complex_num(&cvalue, *fvalue + ((complex *)aval)->re, ((complex *)aval)->im);
                    set_matrix_item(c, i, j, cvalue, 'c');
                }
            }
        }
    }

    void multip_matrix(matrix **a, matrix **b, matrix **c){
        matrix *pa = *a;
        matrix *pb = *b;
        matrix *pc = *c;
        char ta, tb;
        void *aval;
        void *bval;
        complex *cvalue;
        complex *c1;
        complex  *c2;
        int size = pa->n;
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                create_complex_num(&cvalue, 0.0f, 0.0f);
                for (int k = 0; k < size; ++k){
                    aval = get_matrix_item(a, i, k, &ta);
                    bval = get_matrix_item(b, k, j, &tb);
                    if (ta == 'f') {
                        create_complex_num(&c1, *((float *)aval), 0.0f);
                    }
                    else if (ta == 'c'){
                        create_complex_num(&c1, ((complex *)aval)->re, ((complex *)aval)->im);
                    }
                    if (tb == 'f') {
                        create_complex_num(&c2, *((float *)bval), 0.0f);
                    }
                    else if (tb == 'c'){
                        create_complex_num(&c2, ((complex *)bval)->re, ((complex *)bval)->im);
                    }
                    cvalue->re += multip_complex(c1, c2)->re;
                    cvalue->im += multip_complex(c1, c2)->im;
                }
                set_matrix_item(c, i, j, cvalue, 'c');
            }
        }
    }

    void multip_mat_by_a_scalar(matrix **a, void * t, matrix **b, char tt){
        matrix *pa = *a;
        matrix *pb = *b;
        void *aval;
        float *fvalue;
        complex *c1;
        complex *c2;
        complex *cvalue;
        char ta;
        int size = pa->n;
        for (int i = 0; i < size; ++i){
            for (int j= 0; j < size; ++j){
                aval = get_matrix_item(a, i, j, &ta);
                if ((ta == 'f') && (tt == 'f')){
                    fvalue = (float *)malloc(sizeof(float));
                    *fvalue = *((float *)aval) * *((float *)t);
                    set_matrix_item(b, i, j, fvalue, 'f');
                }
                else if ((ta == 'c') && (tt == 'f')){
                    create_complex_num(c1, ((complex *)aval)->re, ((complex *)aval)->im);
                    create_complex_num(c2, *((float *)t), 0.0f);
                    cvalue = multip_complex(c1, c2);
                    set_matrix_item(b, i, j, cvalue, 'c');
                }
                else if ((ta == 'f') && (tt == 'c')){
                    create_complex_num(c1, *((float *)aval), 0.0f);
                    create_complex_num(c2, ((complex *)t)->re, ((complex *)t)->im);
                    cvalue = multip_complex(c1, c2);
                    set_matrix_item(b, i, j, cvalue, 'c');
                }
                else if ((ta == 'c') && (tt == 'c')){
                    create_complex_num(c1, ((complex *)aval)->re, ((complex *)aval)->im);
                    create_complex_num(c2, ((complex *)t)->re, ((complex *)t)->im);
                    cvalue = multip_complex(c1, c2);
                    set_matrix_item(b, i, j, cvalue, 'c');
                }
            }
        }
    }
#endif