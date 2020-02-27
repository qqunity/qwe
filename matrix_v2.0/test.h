#ifndef MATRIX_V2_0_TEST_H
#define MATRIX_V2_0_TEST_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "matrix.h"

    struct Errors {
        int *error_code;
        char **error_description;
        int *error;
        int count;
    };

    typedef struct Errors errors;

    void create_errors(errors **);
    void start_test();
    void test_create_complex_num(errors **, int);
    void test_multip_complex(errors **, int);
    void test_sum_matrix(errors **, int);
    void test_multip_matrix(errors **, int);
    void test_multip_mat_by_a_scalar(errors **, int);
    void copy_string(char [], char **);

    void copy_string(char s1[], char **s2){
        int n = len_c(s1);
        char *buff = (char *)malloc(n * sizeof(char));
        for (int i = 0; i < n; ++i){
            buff[i] = s1[i];
        }
        *s2 = buff;
    }

    void start_test(){
        errors *err;
        create_errors(&err);
        errors *s_err = err;
        test_create_complex_num(&err, 6);
        test_multip_complex(&err, 6);
        test_sum_matrix(&err, 1);
        test_multip_matrix(&err, 1);
        test_multip_mat_by_a_scalar(&err, 1);
        int n = s_err->count;
        for (int i = 0; i < n; ++i){
            if ((s_err->error)[i] == 1){
                printf("TEST: [%d]\t|\tERROR CODE: [%d]\t|\tSTATUS: [ERR]\t|\tDESCRIPTION: [%s]\n", i + 1, (s_err->error_code)[i], (s_err->error_description)[i]);
            }
            else {
                printf("TEST: [%d]\t|\tSTATUS: [OK]\n", i + 1, (s_err->error_code)[i]);
            }
        }
    }

    void test_create_complex_num(errors **err, int cnt_t){
        complex *compl;
        int flag = 0;
        for (int i = 0; i < cnt_t; ++i){
            create_complex_num(&compl, (float)i + 2.2f, (float)i * 4.1f + 5.0f);
            if ((compl->re != (float)i + 2.2f) || (compl->im != (float)i * 4.1f + 5.0f)){
                flag = 1;
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 201;
        char buff_s[] = "Incorrect function operation <create_complex_num>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }

    void test_multip_complex(errors **err, int cnt_t){
        complex *compl1;
        complex *compl2;
        complex *compl3;
        int flag = 0;
        for (int i = 0; i < cnt_t; ++i){
            create_complex_num(&compl1, (float)i + 2.2f, (float)i * 4.1f + 5.0f);
            create_complex_num(&compl2, (float)i - 2.2f, (float)i * 6.1f - 5.0f);
            compl3 = multip_complex(compl1, compl2);
            if (((((float)i + 2.2f) * ((float)i - 2.2f) - ((float)i * 4.1f + 5.0f) * ((float)i * 6.1f - 5.0f)) != compl3->re) || ((((float)i + 2.2f) * ((float)i * 6.1f - 5.0f) + ((float)i * 4.1f + 5.0f) * ((float)i - 2.2f)) != compl3->im)){
                flag = 1;
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 204;
        char buff_s[] = "Incorrect function operation <multip_complex>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }

    void test_sum_matrix(errors **err, int cnt_t){
        int flag = 0;
        for (int i = 0; i < cnt_t; ++i){
            matrix *A;
            create_matrix(&A, 2);
            for (int k = 0; k < 2; ++k){
                for (int j = 0; j < 2; ++j){
                    float *buff_f =(float *)malloc(sizeof(float));
                    *buff_f = (float)k + (float)j + 2.3f;
                    set_matrix_item(&A, k, j, buff_f, 'f');
                }
            }
            matrix *B;
            create_matrix(&B, 2);
            for (int k = 0; k < 2; ++k){
                for (int j = 0; j < 2; ++j){
                    float *buff_f =(float *)malloc(sizeof(float));
                    *buff_f = (float)k - (float)j + 7.3f;
                    set_matrix_item(&B, k, j, buff_f, 'f');
                }
            }
            matrix *C;
            create_matrix(&C, 2);
            sum_matrix(&A, &B, &C);
            for (int k = 0; k < 2; ++k){
                for (int j = 0; j < 2; ++j){
                    if (*((float *)((C->content)[k][j])) != (((float)k + (float)j) + 2.3f + ((float)k - (float)j + 7.3f))) {
                        flag = 1;
                        break;
                    }
                }
                if (flag) {
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 254;
        char buff_s[] = "Incorrect function operation <sum_matrix>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }

    void test_multip_matrix(errors **err, int cnt_t){
        int flag = 0;
        for (int i = 0; i < cnt_t; ++i){
            matrix *A;
            create_matrix(&A, 2);
            for (int k = 0; k < 2; ++k){
                for (int j = 0; j < 2; ++j){
                    float *buff_f =(float *)malloc(sizeof(float));
                    *buff_f = (float)k + (float)j;
                    set_matrix_item(&A, k, j, buff_f, 'f');
                }
            }
            matrix *B;
            create_matrix(&B, 2);
            for (int k = 0; k < 2; ++k){
                for (int j = 0; j < 2; ++j){
                    float *buff_f =(float *)malloc(sizeof(float));
                    *buff_f = (float)k - (float)j;
                    set_matrix_item(&B, k, j, buff_f, 'f');
                }
            }
            int t = 0;
            float ans[] = {1.0f, 0.0f, 2.0f, -1.0f};
            matrix *C;
            create_matrix(&C, 2);
            multip_matrix(&A,&B, &C);
            for (int k = 0; k < 2; ++k){
                for (int j = 0; j < 2; ++j){
                    if (((complex *)((C->content)[k][j]))->re != ans[t]){
                        flag = 1;
                        break;
                    }
                    ++t;
                }
                if (flag) {
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 354;
        char buff_s[] = "Incorrect function operation <multip_matrix>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }

    void test_multip_mat_by_a_scalar(errors **err, int cnt_t){
        int flag = 0;
        for (int i = 0; i < cnt_t; ++i){
            matrix *A;
            create_matrix(&A, 2);
            for (int k = 0; k < 2; ++k){
                for (int j = 0; j < 2; ++j){
                    float *buff_f =(float *)malloc(sizeof(float));
                    *buff_f = (float)k + (float)j;
                    set_matrix_item(&A, k, j, buff_f, 'f');
                }
            }
            float scalar = 2.0f;
            int t = 0;
            float ans[] = {0.0f, 2.0f, 2.0f, 4.0f};
            matrix *C;
            create_matrix(&C, 2);
            multip_mat_by_a_scalar(&A, &scalar, &C, 'f');
            for (int k = 0; k < 2; ++k){
                for (int j = 0; j < 2; ++j){
                    if (*((float*)((C->content)[k][j])) != ans[t]){
                        flag = 1;
                        break;
                    }
                    ++t;
                }
                if (flag) {
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        errors *s_err = *err;
        int n = s_err->count;
        s_err->error_code = (int *)realloc(s_err->error_code, (n + 1) * sizeof(int));
        s_err->error_description = (char **)realloc(s_err->error_description, (n + 1) * sizeof(char *));
        s_err->error = (int *)realloc(s_err->error, (n + 1) * sizeof(int));
        ++(s_err->count);
        (s_err->error_code)[n] = 354;
        char buff_s[] = "Incorrect function operation <multip_matrix>";
        char *buff;
        copy_string(buff_s, &buff);
        (s_err->error_description)[n] = buff;
        (s_err->error)[n] = flag;
    }

    void create_errors(errors **errs){
        errors *n_errs = (errors *)malloc(sizeof(errors));
        int *err_c = (int *)malloc(0 * sizeof(int));
        char **err_desc = (char **)malloc(0 * sizeof(char *));
        int *err = (int *)malloc(0 * sizeof(int));
        n_errs->count = 0;
        n_errs->error_code = err_c;
        n_errs->error_description = err_desc;
        n_errs->error = err;
        *errs = n_errs;
    }

#endif
