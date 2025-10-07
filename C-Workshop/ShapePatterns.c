#include <stdio.h>

int main() {
    int n;
    printf("Enter the size of the matrix (n): ");
    scanf("%d", &n);

    int matrix[n][n];

    printf("Enter %d numbers:\n", n * n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

    // a. Diagonals
    printf("\n(a) Diagonals:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j || i + j == n - 1)
                printf("%d ", matrix[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }

    // b. Medians
    printf("\n(b) Medians:\n");
    int mid = n / 2;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == mid || j == mid)
                printf("%d ", matrix[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }

    // c. Upper right triangle
    printf("\n(c) Upper Right Triangle:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i <= j)
                printf("%d ", matrix[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }

    // d. Lower right triangle
    printf("\n(d) Lower Right Triangle:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i >= j)
                printf("%d ", matrix[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }

    // e. Right half of each row
    printf("\n(e) Right Half of Each Row:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(j >= n / 2)
                printf("%d ", matrix[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }

    // f. Print array and product of each column
    printf("\n(f) Array and Column Products:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    // Column products
    for(int j = 0; j < n; j++) {
        int product = 1;
        for(int i = 0; i < n; i++)
            product *= matrix[i][j];
        printf("%d ", product);
    }
    printf(" <- Column Products\n");

    // g. Determinant (only for n == 2 or 3)
    if(n == 2) {
        int det = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
        printf("\n(g) Determinant: %d\n", det);
    } else if(n == 3) {
        int det = matrix[0][0]*(matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1])
                - matrix[0][1]*(matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0])
                + matrix[0][2]*(matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]);
        printf("\n(g) Determinant: %d\n", det);
    } else {
        printf("\n(g) Determinant: Not implemented for n > 3\n");
    }

    return 0;
}
