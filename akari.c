//Stefan Alexandru Vladut 314CA
#include <stdio.h>
#define NMAX 51
//propagarea luminii de la (i,j) pe verticala si orizontala
int acoperire_bec(int i, int j, char a[][NMAX], int n, int m)
{
	int modificari = 0;
	for (int col = j + 1; col < m; col++) {
		if (a[i][col] == '#' || (a[i][col] >= '0' && a[i][col] <= '4') ||
			a[i][col] == 'L') {
			break;
		}
		if (a[i][col] == '-') {
			a[i][col] = 'x';
			modificari = 1;
		}
	}
	for (int col = j - 1; col >= 0; col--) {
		if (a[i][col] == '#' || (a[i][col] >= '0' && a[i][col] <= '4') ||
			a[i][col] == 'L')
			break;
		if (a[i][col] == '-') {
			a[i][col] = 'x';
			modificari = 1;
		}
	}
	for (int lin = i + 1; lin < n; lin++) {
		if (a[lin][j] == '#' ||
			(a[lin][j] >= '0' &&
			a[lin][j] <= '4') ||
			a[lin][j] == 'L')
			break;
		if (a[lin][j] == '-') {
			a[lin][j] = 'x';
			modificari = 1;
		}
	}
	for (int lin = i - 1; lin >= 0; lin--) {
		if (a[lin][j] == '#' ||
			(a[lin][j] >= '0' &&
			a[lin][j] <= '4') ||
			a[lin][j] == 'L')
			break;
		if (a[lin][j] == '-') {
			a[lin][j] = 'x';
			modificari = 1;
		}
	}
	return modificari;
}

//Marcarea celulelor adiacente dacă este respectata valoarea celulei
int acoperire_cel_neagra(int i, int j, char a[][NMAX], int n, int m)
{
	int ok1 = 0, ok2 = 0, ok3 = 0, ok4 = 0;
	int nr = a[i][j] - '0';
	int cnt = 0;
	int modificari = 0;
	if (j - 1 >= 0) {
		ok1 = 1;
		if (a[i][j - 1] == 'L') {
			cnt++;
			ok1 = 2;
		}
	}
	if (i - 1 >= 0) {
		ok2 = 1;
		if (a[i - 1][j] == 'L') {
			cnt++;
			ok2 = 2;
		}
	}
	if (j + 1 < m) {
		ok3 = 1;
		if (a[i][j + 1] == 'L') {
			cnt++;
			ok3 = 2;
		}
	}
	if (i + 1 < n) {
		ok4 = 1;
		if (a[i + 1][j] == 'L') {
			cnt++;
			ok4 = 2;
		}
	}
	if (cnt == nr) {
		if (ok1 == 1 && a[i][j - 1] == '-') {
			a[i][j - 1] = 'x';
			modificari = 1;
		}
		if (ok2 == 1 && a[i - 1][j] == '-') {
			a[i - 1][j] = 'x';
			modificari = 1;
		}
		if (ok3 == 1 && a[i][j + 1] == '-') {
			a[i][j + 1] = 'x';
			modificari = 1;
		}
		if (ok4 == 1 && a[i + 1][j] == '-') {
			a[i + 1][j] = 'x';
			modificari = 1;
		}
	}
	return modificari;
}

//verificare dacă becul de la (i,j) luminează un alt bec direct
int verif_bec(int i, int j, char a[][NMAX], int n, int m)
{
	for (int col = j + 1; col < m; col++) {
		if (a[i][col] == '#' || (a[i][col] >= '0' && a[i][col] <= '4'))
			break;
		if (a[i][col] == 'L')
			return 0;
	}
	for (int col = j - 1; col >= 0; col--) {
		if (a[i][col] == '#' ||
			(a[i][col] >= '0' &&
			a[i][col] <= '4'))
			break;
		if (a[i][col] == 'L')
			return 0;
	}
	for (int lin = i + 1; lin < n; lin++) {
		if (a[lin][j] == '#' ||
			(a[lin][j] >= '0' &&
			a[lin][j] <= '4'))
			break;
		if (a[lin][j] == 'L')
			return 0;
	}
	for (int lin = i - 1; lin >= 0; lin--) {
		if (a[lin][j] == '#' ||
			(a[lin][j] >= '0' &&
			a[lin][j] <= '4'))
			break;
		if (a[lin][j] == 'L')
			return 0;
	}
	return 1;
}

//verificare dacă numărul de becuri adiacente este compatibil cu nr celulei
int verif_cel_negre(int i, int j, char a[][NMAX], int n, int m)
{
	int nr = a[i][j] - '0';
	int becuri = 0;
	int goale = 0;
	if (j - 1 >= 0) {
		if (a[i][j - 1] == 'L')
			becuri++;
		else if (a[i][j - 1] == '-')
			goale++;
	}
	if (i - 1 >= 0) {
		if (a[i - 1][j] == 'L')
			becuri++;
		else if (a[i - 1][j] == '-')
			goale++;
	}
	if (j + 1 < m) {
		if (a[i][j + 1] == 'L')
			becuri++;
		else if (a[i][j + 1] == '-')
			goale++;
	}
	if (i + 1 < n) {
		if (a[i + 1][j] == 'L')
			becuri++;
		else if (a[i + 1][j] == '-')
			goale++;
	}
	if (becuri > nr) {
		return 0;
	}
	if (becuri + goale < nr)
		return 0;
	return 1;
}

int main(void)
{
	char a[NMAX][NMAX];
	int n, m, o;
	scanf("%d", &o);
	scanf("%d %d", &n, &m);

	//citeste matricea de carcatere
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &a[i][j]);
		}
	}
	//in functie de optiune se alege task-ul de rezolvat
	if (o == 1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				//daca este un bec propagam lumina pe directii
				if (a[i][j] == 'L') {
					acoperire_bec(i, j, a, n, m);
				} else if (a[i][j] >= '0' && a[i][j] <= '4') {
					//daca este celula numerotata marcam vecinii
					acoperire_cel_neagra(i, j, a, n, m);
				}
			}
		}
		// afisam grid-ul completat pana la pasul curent
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%c ", a[i][j]);
			}
			printf("\n");
		}
	} else if (o == 2) {
		int modificari;
		//aplicam functiile anterioare pana nu se mai pot face modificari
		do {
			modificari = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (a[i][j] == 'L') {
						modificari += acoperire_bec(i, j, a, n, m);
					} else if (a[i][j] >= '0' && a[i][j] <= '4') {
						modificari += acoperire_cel_neagra(i, j, a, n, m);
					}
				}
			}
		} while (modificari > 0);
		int rez = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				//daca este bec verificam daca lumineaza altul direct
				if (a[i][j] == 'L') {
					if (verif_bec(i, j, a, n, m) == 0)
						rez = 0;
				} else if (a[i][j] >= '0' && a[i][j] <= '4') {
					//verificam daca numarul de pe celula este compatibil
					if (verif_cel_negre(i, j, a, n, m) == 0)
						rez = 0;
				}
			}
		}
		if (rez == 1) {
			printf("ichi\n");
		} else {
			printf("zero\n");
		}
	}
	return 0;
}
