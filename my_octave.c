/* Copyright Marius-Tudor Zaharia 313CAa 2022-2023 */

#include<stdio.h>
#include<stdlib.h>
#define DIV 10007
#define INC 10

// elibereaza intregul array de matrice (si fiecare matrice din el)
void free_the_whole_array(int ***matrix_array, int size)
{
	for (int i = 0; i < size; i++) {
		// cate linii avea matricea respectiva
		int nr_lin = matrix_array[i][0][0];
		// Dealoc coloanele.
		for (int j = 0; j <= nr_lin; j++)
			free(matrix_array[i][j]);
	}
	// Dealoc liniile.
	for (int i = 0; i < size; i++)
		free(matrix_array[i]);
	// Dealoc array-ul mare.
	free(matrix_array);
}

// aloca mai multa memorie array-ului mare, daca este necesar
void alloc_array(int ****matrix_array, int size, int capacity)
{
	int ***tmp = (int ***)realloc(*matrix_array, capacity * sizeof(int **));

	// Programare defensiva.
	if (!tmp) {
		fprintf(stderr, "Alocarea array-ului a esuat.\n");
		free_the_whole_array(*matrix_array, size);
		exit(-1);
	} else {
		*matrix_array = tmp;
	}
}

// adauga o matrice la finalul array-ului mare
// (inclusiv alocand memoria pentru ea)
void add_matrix(int ****matrix_array, int size, int m, int n)
{
	// Aloc liniile, sunt m + 1 caci pe linia 0 stochez dimensiunile matricei,
	// dar si suma tuturor elementelor matricei.
	(*matrix_array)[size] = (int **)malloc((m + 1) * sizeof(int *));

	// Programare defensiva
	if (!(*matrix_array)[size]) {
		fprintf(stderr, "Alocarea liniilor matricei a esuat.\n");
		free_the_whole_array(*matrix_array, size);
		exit(-1);
	}

	// Aloc 3 coloane pe linia 0 pt dimensiunile si suma elementelor matricei.
	(*matrix_array)[size][0] = (int *)malloc(3 * sizeof(int));

	// Programare defensiva
	if (!(*matrix_array)[size][0]) {
		fprintf(stderr, "Alocarea coloanelor de pe linia 0 a esuat.\n");
		for (int i = 0; i < size; i++) {
			// cate linii avea matricea respectiva
			int nr_lin = (*matrix_array)[i][0][0];
			// Dealoc coloanele.
			for (int j = 0; j <= nr_lin; j++)
				free((*matrix_array)[i][j]);
		}
		// Dealoc liniile.
		for (int i = 0; i <= size; i++)
			free((*matrix_array)[i]);
		// Dealoc array-ul mare.
		free(*matrix_array);
		exit(-1);
	}

	// Aloc cate n coloane pt liniile efective ale matricei.
	for (int i = 1; i <= m; i++) {
		(*matrix_array)[size][i] = (int *)malloc(n * sizeof(int));

		// Programare defensiva
		if (!(*matrix_array)[size][i]) {
			fprintf(stderr, "Alocarea coloanelor matricei a esuat.\n");
			// Dealoc coloanele alocate mai devreme.
			for (int j = 0; j < i; j++)
				free((*matrix_array)[size][j]);
			for (int j = 0; j < size; j++) {
				// cate linii avea acea matrice
				int nr_lin = (*matrix_array)[j][0][0];
				// Dealoc coloanele alocate matricelor precedente.
				for (int k = 0; k <= nr_lin; k++)
					free((*matrix_array)[j][k]);
			}
			// Dealoc liniile.
			for (int j = 0; j <= size; j++)
				free((*matrix_array)[j]);
			// Dealoc array-ul mare.
			free(*matrix_array);
			exit(-1);
		}
	}
	// Adaug dimensiunile matricei pe linia 0 si initializez suma la 0;
	(*matrix_array)[size][0][0] = m;
	(*matrix_array)[size][0][1] = n;
	(*matrix_array)[size][0][2] = 0;
}

// citeste o matrice direct in array
void read_matrix(int ***matrix_array, int size, int m, int n)
{
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &matrix_array[size][i][j]);
	}
}

// aloca memorie pentru o matrice auxiliara
int **alloc_aux_matrix(int m, int n)
{
	// matrice auxiliara
	int **mat_aux = (int **)malloc((m + 1) * sizeof(int *));
	// Programare defensiva
	if (!mat_aux) {
		fprintf(stderr, "Alocarea liniilor matricei auxiliare a esuat.\n");
		return NULL;
	}

	// aloc linia unde pun dimensiunile matricei
	mat_aux[0] = (int *)malloc(3 * sizeof(int));
	// Programare defensiva
	if (!mat_aux[0]) {
		fprintf(stderr, "Alocarea coloanelor matricei auxiliare esuat.\n");
		// Dealoc matricea auxiliara.
		free(mat_aux);
		return NULL;
		}

	for (int i = 1; i <= m; i++) {
		mat_aux[i] = (int *)malloc(n * sizeof(int));
		// Programare defensiva
		if (!mat_aux[i]) {
			fprintf(stderr, "Alocarea coloanelor matricei auxiliare esuat.\n");
			// Dealoc matricea auxiliara (alocata pana in acel moment).
			for (int j = 0; j < i; j++)
				free(mat_aux[j]);
			free(mat_aux);
		return NULL;
		}
	}
	for (int i = 1; i <= m; i++)
		for (int j = 0; j < n; j++)
			mat_aux[i][j] = 0;
	mat_aux[0][0] = m;
	mat_aux[0][1] = n;
	mat_aux[0][2] = 0;
	return mat_aux;
}

// elibereaza orice matrice alocata dinamic (cu m linii reale si cu
// dimensiunile stocate pe linia 0)
void free_matrix(int **mat_aux, int m)
{
	for (int i = 0; i <= m; i++)
		free(mat_aux[i]);
	free(mat_aux);
}

// aloca memorie pentru un vector auxiliar
int *alloc_aux_vek(int dim)
{
	int *vek_aux = (int *)malloc(dim * sizeof(int));
	// Programare defensiva
	if (!vek_aux) {
		fprintf(stderr, "Alocarea vectorului auxiliar a esuat.\n");
		return NULL;
	}
	return vek_aux;
}

// citeste orice vector
void read_vek(int *vek, int dim)
{
	for (int i = 0; i < dim; i++)
		scanf("%d", &vek[i]);
}

// interschimba orice doua matrice
void swap_matrix(int ***matrix1, int ***matrix2)
{
	int **tmp = *matrix1;
	(*matrix1) = *matrix2;
	(*matrix2) = tmp;
}

// inmultirea a doua matrice oarecare
// a are m linii si n coloane, b are n linii si p coloane,
// iar dest are m linii si p coloane
void matrix_multiplication(int **a, int **b, int ***dest, int m, int n, int p)
{
	(*dest)[0][0] = m;
	(*dest)[0][1] = p;
	(*dest)[0][2] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < p; j++) {
			(*dest)[i][j] = 0;
			for (int k = 0; k < n; k++) {
				(*dest)[i][j] += (a[i][k] * b[k + 1][j]) % DIV;
				if ((*dest)[i][j] < 0)
					(*dest)[i][j] += DIV;
				(*dest)[i][j] %= DIV;
			}
			(*dest)[0][2] += (*dest)[i][j];
			if ((*dest)[0][2] < 0)
				(*dest)[0][2] += DIV;
			(*dest)[0][2] %= DIV;
		}
	}
}

// inmultirea a doua matrice patratice (pentru operatia R)
void matrix_multiplication_R(int ****matrix_arr, int size, int **a, int **b,
							 int ***dest, int m)
{
	int **mat_aux = alloc_aux_matrix(m, m);
	// Programare defensiva
	if (!mat_aux) {
		// eliberez tot array-ul
		free_the_whole_array(*matrix_arr, size);
		exit(-1);
	}
	mat_aux[0][0] = m;
	mat_aux[0][1] = m;
	mat_aux[0][2] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < m; j++) {
			mat_aux[i][j] = 0;
			for (int k = 0; k < m; k++) {
				mat_aux[i][j] += (a[i][k] * b[k + 1][j]) % DIV;
				if (mat_aux[i][j] < 0)
					mat_aux[i][j] += DIV;
				mat_aux[i][j] %= DIV;
			}
			mat_aux[0][2] += mat_aux[i][j];
			if (mat_aux[0][2] < 0)
				mat_aux[0][2] += DIV;
			mat_aux[0][2] %= DIV;
		}
	}
	(*dest)[0][0] = m;
	(*dest)[0][1] = m;
	(*dest)[0][2] = mat_aux[0][2];
	// copiez elementele din auxiliara la destinatie
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < m; j++)
			(*dest)[i][j] = mat_aux[i][j];
	}
	free_matrix(mat_aux, m);
}

// elibereaza o matrice din memorie, apoi o aloca iar, cu dimensiuni date,
// tinand cont sa dealoce si o matrice auxiliara (la programare defensiva)
void alloc_again_one_matrix(int ****mat_arr, int index, int m, int n, int size,
							int **aux_mat, int no_of_lines)
{
	// Eliberez din memorie matricea veche.
	int nr_lin = (*mat_arr)[index][0][0];
	for (int i = 0; i <= nr_lin; i++)
		free((*mat_arr)[index][i]);
	free((*mat_arr)[index]);

	// Aloc din nou memorie in acel loc, cu dimensiunile necesare.
	(*mat_arr)[index] = (int **)malloc((m + 1) * sizeof(int *));

	// Programare defensiva
	if (!(*mat_arr)[index]) {
		fprintf(stderr, "Alocarea liniilor matricei a esuat.\n");
		for (int i = 0; i < size && i != index; i++) {
			// numar linii matrice eliberata
			int nr_lin_free = (*mat_arr)[i][0][0];
			for (int j = 0; j <= nr_lin_free; j++)
				free((*mat_arr)[i][j]);
		}
		for (int i = 0; i < size && i != index; i++)
			free((*mat_arr)[i]);
		free(*mat_arr);
		// eliberez si matricea auxiliara
		free_matrix(aux_mat, no_of_lines);
		exit(-1);
	}

	// Aloc 3 coloane pe linia 0.
	(*mat_arr)[index][0] = (int *)malloc(3 * sizeof(int));

	// Programare defensiva
	if (!(*mat_arr)[index][0]) {
		fprintf(stderr, "Alocarea coloanelor de pe linia 0 a esuat.\n");
		// eliberam restul matricelor
		for (int i = 0; i < size && i != index; i++) {
			// numar linii matrice eliberata
			int nr_lin_free = (*mat_arr)[i][0][0];
			for (int j = 0; j <= nr_lin_free; j++)
				free((*mat_arr)[i][j]);
		}
		for (int i = 0; i < size; i++)
			free((*mat_arr)[i]);
		free(*mat_arr);
		free_matrix(aux_mat, no_of_lines);
		exit(-1);
	}

	// Aloc celelalte coloane.
	for (int i = 1; i <= m; i++) {
		(*mat_arr)[index][i] = (int *)malloc(n * sizeof(int));

		// Programare defensiva
		if (!(*mat_arr)[index][i]) {
			fprintf(stderr, "Alocarea coloanelor matricei a esuat.\n");
			// eliberam coloanele alocate mai devreme
			for (int j = 0; j < i; j++)
				free((*mat_arr)[index][j]);
			// eliberam restul matricelor
			for (int j = 0; j < size && j != index; j++) {
				// numar linii matrice eliberata
				int nr_lin_free = (*mat_arr)[j][0][0];
				for (int k = 0; k <= nr_lin_free; k++)
					free((*mat_arr)[j][k]);
			}
			for (int j = 0; j < size; j++)
				free((*mat_arr)[j]);
			free(*mat_arr);
			free_matrix(aux_mat, no_of_lines);
			exit(-1);
		}
	}
}

// elibereaza o matrice din memorie, apoi o aloca iar, cu dimensiuni date,
// tinand cont sa dealoce si o matrice auxiliara, si doi vectori auxiliari
// (la programare defensiva)
void alloc_again_one_matrix_C(int ****mat_arr, int index, int m, int n,
							  int size, int **aux_mat, int no_of_lines,
							  int *vek1, int *vek2)
{
	// Eliberez din memorie matricea veche.
	int nr_lin = (*mat_arr)[index][0][0];
	for (int i = 0; i <= nr_lin; i++)
		free((*mat_arr)[index][i]);
	free((*mat_arr)[index]);

	// Aloc din nou memorie in acel loc, cu dimensiunile necesare.
	(*mat_arr)[index] = (int **)malloc((m + 1) * sizeof(int *));

	// Programare defensiva
	if (!(*mat_arr)[index]) {
		fprintf(stderr, "Alocarea liniilor matricei a esuat.\n");
		for (int i = 0; i < size && i != index; i++) {
			// numar linii matrice eliberata
			int nr_lin_free = (*mat_arr)[i][0][0];
			for (int j = 0; j <= nr_lin_free; j++)
				free((*mat_arr)[i][j]);
		}
		for (int i = 0; i < size && i != index; i++)
			free((*mat_arr)[i]);
		free(*mat_arr);
		// eliberez si matricea auxiliara
		free_matrix(aux_mat, no_of_lines);
		free(vek1);
		free(vek2);
		exit(-1);
	}

	(*mat_arr)[index][0] = (int *)malloc(3 * sizeof(int));

	// Programare defensiva
	if (!(*mat_arr)[index][0]) {
		fprintf(stderr, "Alocarea coloanelor de pe linia 0 a esuat.\n");
		// eliberam restul matricelor
		for (int i = 0; i < size && i != index; i++) {
			// numar linii matrice eliberata
			int nr_lin_free = (*mat_arr)[i][0][0];
			for (int j = 0; j <= nr_lin_free; j++)
				free((*mat_arr)[i][j]);
		}
		for (int i = 0; i < size; i++)
			free((*mat_arr)[i]);
		free(*mat_arr);
		free_matrix(aux_mat, no_of_lines);
		free(vek1);
		free(vek2);
		exit(-1);
	}
	for (int i = 1; i <= m; i++) {
		(*mat_arr)[index][i] = (int *)malloc(n * sizeof(int));

		// Programare defensiva
		if (!(*mat_arr)[index][i]) {
			fprintf(stderr, "Alocarea coloanelor matricei a esuat.\n");
			// eliberam coloanele alocate mai devreme
			for (int j = 0; j < i; j++)
				free((*mat_arr)[index][j]);
			// eliberam restul matricelor
			for (int j = 0; j < size && j != index; j++) {
				// numar linii matrice eliberata
				int nr_lin_free = (*mat_arr)[j][0][0];
				for (int k = 0; k <= nr_lin_free; k++)
					free((*mat_arr)[j][k]);
			}
			for (int j = 0; j < size; j++)
				free((*mat_arr)[j]);
			free(*mat_arr);
			free_matrix(aux_mat, no_of_lines);
			free(vek1);
			free(vek2);
			exit(-1);
		}
	}
}

// aloca memorie si copiaza anumite elemente dintr-o matrice mama in
// alta matrice, in functie de o zona codificata prin variabila key
int **alloc_defensive_strassen(int dim, int **mother, int key)
{
	int **mat_strassen = alloc_aux_matrix(dim, dim);

	// Programare defensiva
	if (!mat_strassen) {
		fprintf(stderr, "Alocarea unei matrice Strassen a esuat.\n");
		exit(-1);
	}
	mat_strassen[0][0] = dim; // numar de linii
	mat_strassen[0][1] = dim; // numar de coloane
	mat_strassen[0][2] = 0; // suma elementelor
	switch (key) {
	case 1:
		// stanga sus
		for (int i = 1; i <= dim; i++) {
			for (int j = 0; j < dim; j++)
				mat_strassen[i][j] = mother[i][j];
		}
		break;
	case 2:
		// dreapta sus
		for (int i = 1; i <= dim; i++) {
			for (int j = 0; j < dim; j++)
				mat_strassen[i][j] = mother[i][j + dim];
		}
		break;
	case 3:
		// stanga jos
		for (int i = 1; i <= dim; i++) {
			for (int j = 0; j < dim; j++)
				mat_strassen[i][j] = mother[i + dim][j];
		}
		break;
	case 4:
		// dreapta jos
		for (int i = 1; i <= dim; i++) {
			for (int j = 0; j < dim; j++)
				mat_strassen[i][j] = mother[i + dim][j + dim];
		}
		break;
	}
	return mat_strassen;
}

// calculeaza suma sau diferenta a doua matrice date
// suma pentru key == 1
// diferenta pentru key == 2
int **sum_strassen(int **a, int **b, int dim, int key)
{
	int **mat_sum = alloc_aux_matrix(dim, dim);

	// Programare defensiva
	if (!mat_sum) {
		fprintf(stderr, "Alocarea unei matrice suma a esuat.\n");
		exit(-1);
	}

	mat_sum[0][0] = dim; // numar de linii
	mat_sum[0][1] = dim; // numar de coloane
	mat_sum[0][2] = 0; // suma elementelor
	if (key == 1) {
		mat_sum[0][2] = (a[0][2] + b[0][2]) % DIV;
		if (mat_sum[0][2] < 0)
			mat_sum[0][2] += DIV;

		for (int i = 1; i <= dim; i++) {
			for (int j = 0; j < dim; j++) {
				mat_sum[i][j] = (a[i][j] + b[i][j]) % DIV;
				if (mat_sum[i][j] < 0)
					mat_sum[i][j] += DIV;
			}
		}
	} else {
		mat_sum[0][2] = (a[0][2] - b[0][2]) % DIV;
		if (mat_sum[0][2] < 0)
			mat_sum[0][2] += DIV;

		for (int i = 1; i <= dim; i++) {
			for (int j = 0; j < dim; j++) {
				mat_sum[i][j] = (a[i][j] - b[i][j]) % DIV;
				if (mat_sum[i][j] < 0)
					mat_sum[i][j] += DIV;
			}
		}
	}
	return mat_sum;
}

// algoritm Strassen recursiv
int **strassen_product(int m, int **a, int **b)
{
	int **c = alloc_aux_matrix(m, m); // matricea rezultat
	if (!c) {
		fprintf(stderr, "Alocarea unei matrice auxiliare a esuat.\n");
		exit(-1);
	}
	c[0][0] = m, c[0][1] = m, c[0][2] = 0;
	if (m == 1) {
		c[1][0] = (a[1][0] * b[1][0]) % DIV;
		if (c[1][0] < 0)
			c[1][0] += DIV;
		c[0][2] = c[1][0];
		return c;
	}
	int **a1 = alloc_defensive_strassen(m / 2, a, 1);
	int **a2 = alloc_defensive_strassen(m / 2, a, 2);
	int **a3 = alloc_defensive_strassen(m / 2, a, 3);
	int **a4 = alloc_defensive_strassen(m / 2, a, 4);
	int **b1 = alloc_defensive_strassen(m / 2, b, 1);
	int **b2 = alloc_defensive_strassen(m / 2, b, 2);
	int **b3 = alloc_defensive_strassen(m / 2, b, 3);
	int **b4 = alloc_defensive_strassen(m / 2, b, 4);
	int **help1, **help2; // matrice ajutatoare pentru sume
	help1 = sum_strassen(a1, a4, m / 2, 1);
	help2 = sum_strassen(b1, b4, m / 2, 1);
	int **m1 = strassen_product(m / 2, help1, help2);
	free_matrix(help1, m / 2), free_matrix(help2, m / 2);
	help1 = sum_strassen(a3, a4, m / 2, 1);
	int **m2 = strassen_product(m / 2, help1, b1);
	free_matrix(help1, m / 2);
	help1 = sum_strassen(b2, b4, m / 2, 2);
	int **m3 = strassen_product(m / 2, a1, help1);
	free_matrix(help1, m / 2);
	help1 = sum_strassen(b3, b1, m / 2, 2);
	int **m4 = strassen_product(m / 2, a4, help1);
	free_matrix(help1, m / 2);
	help1 = sum_strassen(a1, a2, m / 2, 1);
	int **m5 = strassen_product(m / 2, help1, b4);
	free_matrix(help1, m / 2);
	help1 = sum_strassen(a3, a1, m / 2, 2);
	help2 = sum_strassen(b1, b2, m / 2, 1);
	int **m6 = strassen_product(m / 2, help1, help2);
	free_matrix(help1, m / 2), free_matrix(help2, m / 2);
	help1 = sum_strassen(a2, a4, m / 2, 2);
	help2 = sum_strassen(b3, b4, m / 2, 1);
	int **m7 = strassen_product(m / 2, help1, help2);
	free_matrix(help1, m / 2), free_matrix(help2, m / 2);
	help1 = sum_strassen(m1, m4, m / 2, 1);
	help2 = sum_strassen(m7, m5, m / 2, 2);
	int **c1 = sum_strassen(help1, help2, m / 2, 1);
	free_matrix(help1, m / 2), free_matrix(help2, m / 2);
	int **c2 = sum_strassen(m3, m5, m / 2, 1);
	int **c3 = sum_strassen(m2, m4, m / 2, 1);
	help1 = sum_strassen(m1, m2, m / 2, 2);
	help2 = sum_strassen(m3, m6, m / 2, 1);
	int **c4 = sum_strassen(help1, help2, m / 2, 1);
	free_matrix(help1, m / 2), free_matrix(help2, m / 2);
	for (int i = 1; i <= m / 2; i++)
		for (int j = 0; j < m / 2; j++) {
			c[i][j] = c1[i][j]; // stanga sus
			c[i][j + m / 2] = c2[i][j]; // dreapta sus
			c[i + m / 2][j] = c3[i][j]; // stanga jos
			c[i + m / 2][j + m / 2] = c4[i][j]; // dreapta jos
		}
	c[0][2] = (c1[0][2] + c2[0][2] + c3[0][2] + c4[0][2]) % DIV;
	if (c[0][2] < 0)
		c[0][2] += DIV;
	// eliberez toate matricele ajutatoare
	free_matrix(a1, m / 2), free_matrix(a2, m / 2);
	free_matrix(a3, m / 2), free_matrix(a4, m / 2);
	free_matrix(b1, m / 2), free_matrix(b2, m / 2);
	free_matrix(b3, m / 2), free_matrix(b4, m / 2);
	free_matrix(c1, m / 2), free_matrix(c2, m / 2);
	free_matrix(c3, m / 2), free_matrix(c4, m / 2);
	free_matrix(m1, m / 2), free_matrix(m2, m / 2);
	free_matrix(m3, m / 2), free_matrix(m4, m / 2);
	free_matrix(m5, m / 2), free_matrix(m6, m / 2);
	free_matrix(m7, m / 2);
	return c;
}

// incarcarea in memorie a unei matrice (si stocarea dimensiunilor)
void operation_L(int ****matrix_array, int m, int n, int *size, int *capacity)
{
	if (*size + 1 > *capacity) {
		*capacity += INC;
		alloc_array(matrix_array, *size, *capacity);
	}
	add_matrix(matrix_array, *size, m, n);
	read_matrix(*matrix_array, *size, m, n);

	// Stochez suma elementelor matricei pe linia 0, coloana 2.
	int nr_lin = (*matrix_array)[*size][0][0];
	int nr_col = (*matrix_array)[*size][0][1];
	for (int i = 1; i <= nr_lin; i++) {
		for (int j = 0; j < nr_col; j++) {
			(*matrix_array)[*size][0][2] += (*matrix_array)[*size][i][j] % DIV;
			// Daca rezultatul este negativ, adun la el DIV
			if ((*matrix_array)[*size][0][2] < 0)
				(*matrix_array)[*size][0][2] += DIV;
			(*matrix_array)[*size][0][2] %= DIV;
			if ((*matrix_array)[*size][0][2] < 0)
				(*matrix_array)[*size][0][2] += DIV;
		}
	}
	(*size)++;
}

// determinarea dimensiunilor unei matrice
void operation_D(int ***matrix_array, int index, int size)
{
	// conditii
	if (index >= size || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	// numarul de linii pt matricea a[index]
	int nr_lin = matrix_array[index][0][0];
	// numarul de coloane pt matricea a[index]
	int nr_col = matrix_array[index][0][1];
	printf("%d %d\n", nr_lin, nr_col);
}

// afisarea unei matrice
void operation_P(int ***matrix_array, int index, int size)
{
	// conditii
	if (index >= size || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	// numarul de linii pt matricea a[index]
	int nr_lin = matrix_array[index][0][0];
	// numarul de coloane pt matricea a[index]
	int nr_col = matrix_array[index][0][1];
	for (int i = 1; i <= nr_lin; i++) {
		for (int j = 0; j < nr_col; j++)
			printf("%d ", matrix_array[index][i][j]);
		printf("\n");
	}
}

// redimensionarea unei matrice
void operation_C(int ****matrix_arr, int index, int size)
{
	int lines, cols;
	scanf("%d", &lines);
	int *vek_lines = alloc_aux_vek(lines);
	if (!vek_lines) {
		free_the_whole_array(*matrix_arr, size); // eliberez tot array-ul
		exit(-1);
	}
	read_vek(vek_lines, lines);
	scanf("%d", &cols);
	int *vek_cols = alloc_aux_vek(cols);
	if (!vek_cols) {
		free_the_whole_array(*matrix_arr, size); // eliberez tot array-ul
		free(vek_lines);
		exit(-1);
	}
	read_vek(vek_cols, cols);
	// conditii
	if (index >= size || index < 0) {
		printf("No matrix with the given index\n");
		free(vek_lines);
		free(vek_cols);
		return;
	}
	// matrice auxiliara
	int **mat_aux = alloc_aux_matrix(lines, cols);

	// Programare defensiva
	if (!mat_aux) {
		free_the_whole_array(*matrix_arr, size); // eliberez tot array-ul
		free(vek_lines);
		free(vek_cols);
		exit(-1);
	}
	mat_aux[0][0] = lines; // cate linii are matricea crop
	mat_aux[0][1] = cols; // cate coloane are matricea crop
	mat_aux[0][2] = 0; // initializam suma elementelor cu 0
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < cols; j++) {
			int which_lin = vek_lines[i];
			int which_col = vek_cols[j];
			mat_aux[i + 1][j] = (*matrix_arr)[index][which_lin + 1][which_col];
			mat_aux[0][2] += mat_aux[i + 1][j] % DIV;
			// Daca rezultatul este negativ, adun la el DIV
			if (mat_aux[0][2] < 0)
				mat_aux[0][2] += DIV;
			mat_aux[0][2] %= DIV;
		}
	}
	// scot matricea din memorie si o aloc din nou, cu dimensiunile dorite
	alloc_again_one_matrix_C(matrix_arr, index, lines, cols, size, mat_aux,
							 lines, vek_lines, vek_cols);
	(*matrix_arr)[index][0][0] = mat_aux[0][0]; //numar de linii
	(*matrix_arr)[index][0][1] = mat_aux[0][1]; // numar de coloane
	(*matrix_arr)[index][0][2] = mat_aux[0][2]; // suma elementelor
	// Punem efectiv elementele in matrice
	for (int i = 1; i <= lines; i++) {
		for (int j = 0; j < cols; j++)
			(*matrix_arr)[index][i][j] = mat_aux[i][j];
	}
	free_matrix(mat_aux, lines);
	free(vek_lines);
	free(vek_cols);
}

// inmultirea a doua matrice din array si stocarea rezultatului la final
void operation_M(int ****mat_arr, int index1, int index2, int *size,
				 int *capacity)
{
	// conditii
	if (index1 >= *size || index2 >= *size || index1 < 0 || index2 < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	int nr_lin_1 = (*mat_arr)[index1][0][0]; // cate linii are prima matrice
	int nr_col_1 = (*mat_arr)[index1][0][1]; // cate coloane are prima matrice
	int nr_lin_2 = (*mat_arr)[index2][0][0]; // cate linii are a doua matrice
	int nr_col_2 = (*mat_arr)[index2][0][1]; // cate coloane are a doua matrice
	if (nr_col_1 != nr_lin_2) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	if (*size + 1 > *capacity) {
		*capacity += INC;
		alloc_array(mat_arr, *size, *capacity);
	}
	add_matrix(mat_arr, *size, nr_lin_1, nr_col_2);
	matrix_multiplication((*mat_arr)[index1], (*mat_arr)[index2],
						  &(*mat_arr)[*size], nr_lin_1, nr_col_1,
						  nr_col_2);
	(*size)++;
}

// sortarea matricelor (prin selectie)
void operation_O(int ****mat_arr, int size)
{
	// Sortam in functie de suma elementelor (modulo DIV), ce este stocata
	// pe linia 0 si coloana 2 a fiecarei matrice.
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if ((*mat_arr)[i][0][2] > (*mat_arr)[j][0][2])
				swap_matrix(&(*mat_arr)[i], &(*mat_arr)[j]);
		}
	}
}

// transpunerea unei matrice
void operation_T(int ****arr_mat, int index, int size)
{
	// conditii
	if (index >= size || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	int nr_lin = (*arr_mat)[index][0][0];
	int nr_col = (*arr_mat)[index][0][1];
	// matrice auxiliara, liniile devin coloane si coloanele devin linii.
	int **mat_aux = alloc_aux_matrix(nr_col, nr_lin);
	// Programare defensiva
	if (!mat_aux) {
		free_the_whole_array(*arr_mat, size); // eliberez tot array-ul
		exit(-1);
	}
	mat_aux[0][0] = nr_col; // cate linii are transpusa
	mat_aux[0][1] = nr_lin; // cate coloane are transpusa
	mat_aux[0][2] = (*arr_mat)[index][0][2]; // suma elementelor
	// adaug efectiv elementele transpusei
	for (int i = 1; i <= nr_col; i++) {
		for (int j = 0; j < nr_lin; j++)
			mat_aux[i][j] = (*arr_mat)[index][j + 1][i - 1];
	}
	// scot matricea din memorie si o aloc din nou, cu dimensiunile dorite
	alloc_again_one_matrix(arr_mat, index, nr_col, nr_lin, size, mat_aux,
						   nr_col);
	(*arr_mat)[index][0][0] = mat_aux[0][0];
	(*arr_mat)[index][0][1] = mat_aux[0][1];
	(*arr_mat)[index][0][2] = mat_aux[0][2];
	for (int i = 1; i <= nr_col; i++) {
		for (int j = 0; j < nr_lin; j++)
			(*arr_mat)[index][i][j] = mat_aux[i][j];
	}
	free_matrix(mat_aux, nr_col);
}

// ridicarea unei matrice la o putere in timp logaritmic
void operation_R(int ****arr_mat, int index, int size)
{
	int power;
	scanf("%d", &power);
	// conditii
	if (index >= size || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (power < 0) {
		printf("Power should be positive\n");
		return;
	}
	int nr_lin = (*arr_mat)[index][0][0];
	int nr_col = (*arr_mat)[index][0][1];
	if (nr_lin != nr_col) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	// matrice auxiliara
	int **mat_aux = alloc_aux_matrix(nr_lin, nr_lin);
	// Programare defensiva
	if (!mat_aux) {
		free_the_whole_array(*arr_mat, size); // eliberez tot array-ul
		exit(-1);
	}
	// o initializam drept matricea unitate
	mat_aux[0][0] = nr_lin; // cate linii are
	mat_aux[0][1] = nr_lin; // cate coloane are
	mat_aux[0][2] = nr_lin; // suma elementelor initializata
	for (int i = 1; i <= nr_lin; i++) {
		for (int j = 0; j < nr_lin; j++) {
			if (i - 1 == j)
				mat_aux[i][j] = 1;
			else
				mat_aux[i][j] = 0;
		}
	}
	// algoritm exponentiere rapida
	while (power != 0) {
		if (power % 2 == 1)
			matrix_multiplication_R(arr_mat, size, mat_aux, (*arr_mat)[index],
									&mat_aux, nr_lin);
		power /= 2;
		matrix_multiplication_R(arr_mat, size, (*arr_mat)[index],
								(*arr_mat)[index], &(*arr_mat)[index], nr_lin);
	}
	(*arr_mat)[index][0][2] = mat_aux[0][2];
	for (int i = 1; i <= nr_lin; i++) {
		for (int j = 0; j < nr_lin; j++)
			(*arr_mat)[index][i][j] = mat_aux[i][j];
	}
	free_matrix(mat_aux, nr_lin);
}

// eliberarea memoriei unei matrice
void operation_F(int ****arr_mat, int index, int *size, int *capacity)
{
	// conditii
	if (index >= *size || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	// Duc matricea de eliberat la finalul array-ului
	for (int i = index; i < *size - 1; i++)
		swap_matrix(&(*arr_mat)[i], &(*arr_mat)[i + 1]);
	// Eliberez matricea
	int nr_lin = (*arr_mat)[*size - 1][0][0];
	for (int i = 0; i <= nr_lin; i++)
		free((*arr_mat)[*size - 1][i]);
	free((*arr_mat)[*size - 1]);
	(*size)--;

	//Daca am eliberat multe matrice, eliberam o parte din memoria alocata
	//pentru array-ul de matrice, adica arr_mat.
	if (2 * (*size) < *capacity && *size != 0) {
		(*capacity) /= 2;
		alloc_array(arr_mat, *size, *capacity);
	}
}

// eliberarea tuturor resurselor
void operation_Q(int ***matrix_array, int size)
{
	free_the_whole_array(matrix_array, size);
}

// inmultirea a doua matrice folosind algoritmul lui Strassen
void operation_S(int ****arr_mat, int index1, int index2, int *size,
				 int *capacity)
{
	// conditii
	if (index1 >= *size || index2 >= *size || index1 < 0 || index2 < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	int nr_lin_1 = (*arr_mat)[index1][0][0]; // dimensiunea primei matrice
	int nr_lin_2 = (*arr_mat)[index2][0][0]; // cate linii are a doua matrice
	if (nr_lin_1 != nr_lin_2) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	if (*size + 1 > *capacity) {
		*capacity += INC;
		alloc_array(arr_mat, *size, *capacity);
	}
	add_matrix(arr_mat, *size, nr_lin_1, nr_lin_1);
	int **mat_aux = strassen_product(nr_lin_1, (*arr_mat)[index1],
									 (*arr_mat)[index2]);
	for (int i = 1; i <= nr_lin_1; i++) {
		for (int j = 0; j < nr_lin_1; j++)
			(*arr_mat)[*size][i][j] = mat_aux[i][j];
	}
	(*arr_mat)[*size][0][0] = nr_lin_1;
	(*arr_mat)[*size][0][1] = nr_lin_1;
	(*arr_mat)[*size][0][2] = mat_aux[0][2];
	free_matrix(mat_aux, nr_lin_1);
	(*size)++;
}

int main(void)
{
	int ***matrix_array = (int ***)malloc(sizeof(int **));
	if (!matrix_array) {
		fprintf(stderr, "Alocarea array-ului a esuat.\n");
		exit(-1);
	}
	// size matrice in array, capacity elemente alocate dinamic array-ului
	// m linii, respectiv n coloane are o matrice, stop cand oprim citirea
	int size = 0, capacity = 1, m = 0, n = 0, stop = 0, index1, index2;
	char litera;
	while (stop == 0) {
		scanf("%c", &litera);
		switch (litera) {
		case 'L':
			scanf("%d%d", &m, &n);
			operation_L(&matrix_array, m, n, &size, &capacity);
			break;

		case 'D':
			scanf("%d", &index1);
			operation_D(matrix_array, index1, size);
			break;

		case 'P':
			scanf("%d", &index1);
			operation_P(matrix_array, index1, size);
			break;

		case 'C':
			scanf("%d", &index1);
			operation_C(&matrix_array, index1, size);
			break;

		case 'M':
			scanf("%d%d", &index1, &index2);
			operation_M(&matrix_array, index1, index2, &size, &capacity);
			break;

		case 'O':
			operation_O(&matrix_array, size);
			break;

		case 'T':
			scanf("%d", &index1);
			operation_T(&matrix_array, index1, size);
			break;

		case 'R':
			scanf("%d", &index1);
			operation_R(&matrix_array, index1, size);
			break;

		case 'F':
			scanf("%d", &index1);
			operation_F(&matrix_array, index1, &size, &capacity);
			break;

		case 'Q':
			operation_Q(matrix_array, size);
			stop = 1;
			break;

		case 'S':
			scanf("%d%d", &index1, &index2);
			operation_S(&matrix_array, index1, index2, &size, &capacity);
			break;

		case ' ':
			break;

		case '\n':
			break;

		default:
			printf("Unrecognized command\n");
			break;
		}
	}
	return 0;
}
