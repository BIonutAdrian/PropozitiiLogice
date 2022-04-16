#include <conio.h>
#include <stdio.h>
#include <string.h>

char propozitie_complexa[10], relatii[5][4];
int lungime, i, j, nr_relatii, nr_propozitii, tabel[50][50], nr_linii, valoare_de_adevar, n, el,OK1,OK0;
int q,y;

void si(int a, int b, int &nr_relatii) {
	q = nr_relatii;
	for(int k=1;k<=nr_linii;k++)
		if ((tabel[k][a] == 1) && (tabel[k][b] == 1))
			tabel[k][nr_relatii] = 1;
		else
			tabel[k][nr_relatii] = 0;
	relatii[nr_relatii][0] = '0' + a;
	relatii[nr_relatii][1] = '&';
	relatii[nr_relatii][2] = '0' + b;
	relatii[nr_relatii][3] = '0' + nr_relatii;
	nr_relatii = q + 1;
}

void sau(int a, int b, int &nr_relatii) {
	q = nr_relatii;
	for (int k = 1;k <= nr_linii;k++)
		if ((tabel[k][a] == 1) || (tabel[k][b] == 1))
			tabel[k][nr_relatii] = 1;
		else
			tabel[k][nr_relatii] = 0;
	relatii[nr_relatii][0] = '0' + a;
	relatii[nr_relatii][1] = '|';
	relatii[nr_relatii][2] = '0' + b;
	relatii[nr_relatii][3] = '0' + nr_relatii;
	nr_relatii = q + 1;
}

void implicatie(int a, int b,int &nr_relatii) {
	q = nr_relatii;
	for (int k = 1;k <= nr_linii;k++)
		if ((tabel[k][a] == 1) && (tabel[k][b] == 0))
			tabel[k][nr_relatii] = 0;
		else
			tabel[k][nr_relatii] = 1;
	relatii[nr_relatii][0] = '0' + a;
	relatii[nr_relatii][1] = '-';
	relatii[nr_relatii][2] = '0' + b;
	relatii[nr_relatii][3] = '0' + nr_relatii;
	nr_relatii = q + 1;
}

void echivalenta(int a, int b, int &nr_relatii) {
	q = nr_relatii;
	for (int k = 1;k <= nr_linii;k++)
		if (tabel[k][a] == tabel[k][b])
			tabel[k][nr_relatii] = 1;
		else
			tabel[k][nr_relatii] = 0;
	relatii[nr_relatii][0] = '0' + a;
	relatii[nr_relatii][1] = '=';
	relatii[nr_relatii][2] = '0' + b;
	relatii[nr_relatii][3] = '0'+ nr_relatii;
	nr_relatii = q + 1;
}

void negatie(int a,int &nr_relatii) {
	q = nr_relatii;
	for (int k = 1;k <= nr_linii;k++)
		if (tabel[k][a] == 1)
			tabel[k][nr_relatii] = 0;
		else
			tabel[k][nr_relatii] = 1;
	relatii[nr_relatii][0] = '0' + a;
	relatii[nr_relatii][1] = '~';
	relatii[nr_relatii][3] = '0' + nr_relatii;
	nr_relatii = q + 1;
}



void propozitie_simpla(int a, int b,char semn, int &valoare) {
	if (semn == '&')
		si(a, b, nr_relatii);
	if (semn == '|')
		sau(a, b, nr_relatii);
	if (semn == '-')
		implicatie(a, b, nr_relatii);
	if (semn == '=')
		echivalenta(a, b, nr_relatii);
	valoare = nr_relatii - 1;
}


int main() {



	printf("In citirea propozitie complexe folositi: \n& pentru si \n| pentru sau\n- pentru implicatie\n= pentru echivalenta\n~ pentru negatie");
	printf("\n\nCititi propozitia complexa din propozitia complexa:");
	scanf("%s", propozitie_complexa);

	lungime = strlen(propozitie_complexa);
	i = 0;
	nr_propozitii = 0;
	while (i < lungime)
		if ((propozitie_complexa[i] != '(') && (propozitie_complexa[i] != ')'))
			if ((propozitie_complexa[i] != '&') && (propozitie_complexa[i] != '|') && (propozitie_complexa[i] != '~') && (propozitie_complexa[i] != '-') && (propozitie_complexa[i] != '=')) {
				nr_propozitii++;
				propozitie_complexa[i] = nr_propozitii + '0';
				i++;
			}
			else {
				i++;
			}
		else
			i++;
	nr_linii = 2;
	for (i = 1;i < nr_propozitii;i++)
		nr_linii = nr_linii * 2;

	n = nr_linii / 2;
	el = 0;
	valoare_de_adevar = 1;
	for (j = 1;j <= nr_propozitii;j++) {
		for (i = 1;i <= nr_linii;i++)
			if (el != n) {
				el++;
				tabel[i][j] = valoare_de_adevar;
			}
			else {
				if (valoare_de_adevar == 1)
					valoare_de_adevar = 0;
				else
					valoare_de_adevar = 1;
				tabel[i][j] = valoare_de_adevar;
				el = 1;
			}
		valoare_de_adevar = 1;
		n = n / 2;
		el = 0;
	}

	nr_relatii = nr_propozitii + 1;

	for (i = 1;i <= nr_propozitii;i++)
		negatie(i, nr_relatii);

	lungime = strlen(propozitie_complexa);

	for (i = 0;i < lungime;i++) {
		if ((propozitie_complexa[i] == '~')&&(propozitie_complexa[i+1]!='(')) {
			propozitie_complexa[i + 1] = propozitie_complexa[i + 1] + nr_propozitii;
			for (j = i + 1;j <= lungime;j++)
				propozitie_complexa[j - 1] = propozitie_complexa[j];
		}
	}

	lungime = strlen(propozitie_complexa);

	for (i = 0;i < lungime;i++)
		if (propozitie_complexa[i] == '(') {
			propozitie_simpla(propozitie_complexa[i + 1]-'0', propozitie_complexa[i + 3]-'0', propozitie_complexa[i + 2], y);
			propozitie_complexa[i] = y+'0';
			for(q=1;q<=4;q++)
				for(j=i+1;j<lungime;j++)
					propozitie_complexa[j] = propozitie_complexa[j+1];
		}

	lungime = strlen(propozitie_complexa);

	for (i = 0;i < lungime;i++) {
		if (propozitie_complexa[i] == '~') {
			negatie(propozitie_complexa[i + 1] - '0', nr_relatii);
			propozitie_complexa[i + 1] = (nr_relatii-1) + '0';
			for (j = i + 1;j <= lungime;j++)
				propozitie_complexa[j - 1] = propozitie_complexa[j];
		}
	}

	lungime = strlen(propozitie_complexa);

	for (i = 0;i < lungime;i++)
		if (((propozitie_complexa[i] == '&') || (propozitie_complexa[i] == '|') || (propozitie_complexa[i] == '-') || (propozitie_complexa[i] == '=')))
			propozitie_simpla(propozitie_complexa[i - 1] - '0', propozitie_complexa[i + 1] - '0', propozitie_complexa[i], y);

	//Aici este afisarea tabelei de adevar care contine si coloane pentru orice propozitie de la inceput, dar negata.
	/*for (i = 1;i <= nr_linii;i++) {
		for (j = 1;j <= nr_relatii-1;j++)
			printf("%d ", tabel[i][j]);
		printf("\n");
	}*/

	//printf("\n\n%s", propozitie_complexa);

	OK0 = 0;
	OK1 = 0;
	for (i = 1;i <= nr_linii;i++)
		if (tabel[i][nr_relatii-1] == 1)
			OK1 = 1;
		else
			if (tabel[i][nr_relatii] == 0)
				OK0 = 1;
	if ((OK1 == 1) && (OK0 == 0))
		printf("Este o tautologie si satisfiabila.");
	else
		if ((OK1 == 1) && (OK0 == 1))
			printf("Este contingenta si satisfiabila.");
		else
			if ((OK1 == 0) && (OK0 == 0))
				printf("Este nesatisfiabila.");

	getch();
    return 0;
}