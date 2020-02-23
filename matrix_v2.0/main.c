#include "matrix.h"
#include "test.h"

int main() {
    int shut_down = 0;
    while (!shut_down) {
        printf("Введите 0, если хотите завершить работу программы.\nВведите 1, если хоти вычислить сумму двух матриц.\nВведите 2, если хотите умножить две матрицы.\nВведите 3, если хотите умножить матрицу на скаляр.\nВведите 4, если хотите запустить тесты.\n-> ");
        int user_input;
        scanf("%d", &user_input);
        if (user_input == 0){
            shut_down = 1;
        }
        else if (user_input == 1) {
            printf("\nВведите разметрность матриц, с которыми будет выполняться операция сложения.\n-> ");
            int n;
            scanf("%d", &n);
            matrix *matA;
            create_matrix(&matA, n);
            printf("\nЗаполните матрицы A и B, сдедуя следующим правилам:\n\t1. Каждый элемент матрицы отделятся пробелом от предыдущего.\n\t2. Матрица может содержать комплексные и вещественные числа (формат комплексных: a+i*b / a-i*b / -a+i*b / -a-i*b  (без пробелов между символами, где a и b - вещественные числа с форматом i.f, где i - целая часть, а f - дробная, формат вещественных: i.f / -i.f\n\nA:\n\n");
            getchar();
            fill_matrix(&matA);
            matrix *matB;
            create_matrix(&matB, n);
            printf("\nB:\n\n");
            fill_matrix(&matB);
            matrix *matC;
            create_matrix(&matC, n);
            sum_matrix(&matA, &matB, &matC);
            printf("Матрица полученная в результате сложения матрицы A и  матрицыB:\n\n");
            print_matrix(&matC);
            printf("\n");
        }
        else if (user_input == 2) {
            printf("\nВведите разметрность матриц, с которыми будет выполняться операция умножения.\n-> ");
            int n;
            scanf("%d", &n);
            matrix *matA;
            create_matrix(&matA, n);
            printf("\nЗаполните матрицы A и B, сдедуя следующим правилам:\n\t1. Каждый элемент матрицы отделятся пробелом от предыдущего.\n\t2. Матрица может содержать комплексные и вещественные числа (формат комплексных: a+i*b / a-i*b / -a+i*b / -a-i*b  (без пробелов между символами, где a и b - вещественные числа с форматом i.f, где i - целая часть, а f - дробная, формат вещественных: i.f / -i.f\n\nA:\n\n");
            getchar();
            fill_matrix(&matA);
            matrix *matB;
            create_matrix(&matB, n);
            printf("\nB:\n\n");
            fill_matrix(&matB);
            matrix *matC;
            create_matrix(&matC, n);
            multip_matrix(&matA, &matB, &matC);
            printf("Матрица полученная в результате умножения матрицы A на матрицу B:\n\n");
            print_matrix(&matC);
            printf("\n");
        }
        else if (user_input == 3) {
            printf("\nВведите разметрность матрицы, с которой будет выполняться операция умножения на скаляр.\n-> ");
            int n;
            scanf("%d", &n);
            matrix *matA;
            create_matrix(&matA, n);
            printf("\nЗаполните матрицу A сдедуя следующим правилам:\n\t1. Каждый элемент матрицы отделятся пробелом от предыдущего.\n\t2. Матрица может содержать комплексные и вещественные числа (формат комплексных: a+i*b / a-i*b / -a+i*b / -a-i*b  (без пробелов между символами, где a и b - вещественные числа с форматом i.f, где i - целая часть, а f - дробная, формат вещественных: i.f / -i.f\n\nA:\n\n");
            getchar();
            fill_matrix(&matA);
            printf("\nВведите скаляр, на который хотите умножить матрицу A (правила ввода скаляра аналогичну правилам ввода элемента матрицы):\n\n");
            char *user_s = read_str();
            printf("\n");
            if (is_complex(user_s)){
                complex *cscal;
                convert_to_complex_num(&cscal, user_s);
                matrix *matC;
                create_matrix(&matC, n);
                multip_mat_by_a_scalar(&matA, cscal, &matC, 'c');
                printf("Матрица полученная в результате умножения матрицы A на скаляр:\n\n");
                print_matrix(&matC);
                printf("\n");
            }
            else {
                float *fscal;
                convert_to_float_num(fscal, user_s);
                matrix *matC;
                create_matrix(&matC, n);
                multip_mat_by_a_scalar(&matA, fscal, &matC, 'f');
                printf("Матрица полученная в результате умножения матрицы A на скаляр:\n\n");
                print_matrix(&matC);
                printf("\n");
            }
        }
        else if (user_input == 4){
            start_test();
        }
        else {
            printf("Некореектный ввод, повторите попытку!\n");
        }
    }
}


