#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include"ConsoleColor.h"

using namespace std;

static int whiteNumber;
static int blackNumber;


//Kullanilan fonksiyonlar
int value(char); //kullanicinin girdigi alfabetik karakterleri sayisal degerlere cevirir
void draw(FILE* fptr); //dama tahtasini ekrana cizer
void move(FILE* fptr); //ta��n hareket etmesi ve t�m kontroller
char getTurn(FILE* fptr); // s�ran�n kimde oldu�unu belirtir
void setTurn(FILE* fptr); //s�ran�n kime ge�ti�ini olu�turur
void newGame(); // yeni oyun ba�lat�r
void continueGame(); // �nceki oyundan devam ettirir
void endGame();
bool isEmpty(char); // ta��n gidece�i yerin doluluk kontrol�n� yapar
char readFile(FILE* fptr, int m, int n); //dosyadan karakter okur
void writeFile(FILE* fptr, int k, int l, int m, int n); // dosyada update i�lemi yapar
void capture(FILE* fptr, int m, int n, char a); //ta� yeme fonksiyonu
void count(FILE* fptr);//devam eden oyundaki ta� say�lar�n� sayar
void seqFile(char t1, char field1, char field2, char field3, char field4);//oynanan her hamleyi dosyaya s�ral� yazan fonksiyon



void seqFile(char t1, char field1, char field2, char field3, char field4) {

	char field[8];
	field[0] = t1;
	field[1] = ':';
	field[2] = ' ';
	field[3] = field1;
	field[4] = field2;
	field[5] = field3;
	field[6] = field4;
	field[7] = '\n';

	FILE* sptr;
	sptr = fopen("sequential.dat", "ab+");
	fseek(sptr, 0, SEEK_CUR);
	fwrite(field, sizeof(field), sizeof(char), sptr);
	
}


bool isEmpty(char cm) {
	if (cm == 'w' || cm == 'b') {		
		return false;
	}
	else {
		return true;
	}
}

int value(char x) {
	if (x == 'a')
		return 1;
	else if (x == 'b')
		return 2;
	else if (x == 'c')
		return 3;
	else if (x == 'd')
		return 4;
	else if (x == 'e')
		return 5;
	else if (x == 'f')
		return 6;
	else if (x == 'g')
		return 7;
	else if (x == 'h')
		return 8;
	else
		return 0;
}

void draw(FILE* fptr) {
	int a = 0;
	char dama[206];	
	fseek(fptr, 0, SEEK_SET);
	fread(dama, sizeof(dama), 1, fptr);
	cout << "------------------------------------------" << endl << endl;
	for (int i = 0; i < 204; i++) {
		
		if (i >= 0 && i < 24) {
			cout << dama[i];
			if (i == 23) {
				cout << yellow  << a << white << endl;
				a++;
			}
		}
		else if (i> 25 && i < 50) {
			cout << dama[i];
			if (i == 49) {
				cout << yellow << a << white << endl;
				a++;
			}
				
		}
		else if (i > 51 && i < 76) {
			cout << dama[i];
			if (i == 75) {
				cout << yellow << a << white << endl;
				a++;
			}
		}
		else if (i > 77 && i < 102) {
			cout << dama[i];
			if (i == 101) {
				cout << yellow << a << white << endl;
				a++;
			}
		}
		else if (i > 103 && i < 128) {
			cout << dama[i];
			if (i == 127) {
				cout << yellow << a << white << endl;
				a++;
			}
		}
		else if (i > 129 && i < 154) {
			cout << dama[i];
			if (i == 153) {
				cout << yellow << a << white << endl;
				a++;
			}
		}
		else if (i > 155 && i < 180) {
			cout << dama[i];
			if (i == 179) {
				cout << yellow << a << white << endl;
				a++;
			}
		}
		else if (i > 181 && i < 198) {
			cout << dama[i];
			if (i == 197) {
				cout << yellow <<"        "<< a << white << endl;
				a++;
			}
		}
		
	}
	
	cout << yellow << endl << "A  B  C  D  E  F  G  H" << white << endl;
	cout << "------------------------------------------";
}

char getTurn(FILE* fptr) {
	//FILE* fptr = fopen("checker.txt", "rb+");
	char dama[206];
	fseek(fptr, 1, SEEK_SET);
	fread(dama, sizeof(dama), 1, fptr);
	return dama[199];
}

void setTurn(FILE* fptr) {
	char turn = getTurn(fptr);
	char dama[206];
	fseek(fptr, 1, SEEK_SET);
	fread(dama, sizeof(dama), 1, fptr);
	char field[1];
	
	if (turn == 'w') { // s�ra beyazdaysa siyaha ge�er
		field[0] = 'b';
		
		
	}
	else if (turn == 'b') {// s�ra siyahtaysa beyaza ge�er
		field[0] = 'w';
	
	}
	fseek(fptr, 200, SEEK_SET);
	fwrite(field, sizeof(field), sizeof(char), fptr);


}

void newGame() {
	ofstream file("checkers.dat", ios::out);
	ifstream ifile("checkers.dat", ios::in);
	file << "                        \nw  w  w  w  w  w  w  w  \nw  w  w  w  w  w  w  w  \n                        \n                        \nb  b  b  b  b  b  b  b  \nb  b  b  b  b  b  b  b  \n                \nw";
	file.close();
	whiteNumber = 16;
	blackNumber = 16;
	FILE* fptr = fopen("checkers.dat", "rb+");
	FILE* cptr = fopen("sequential.dat", "wb+");
	fclose(cptr);
	move(fptr);
	fclose(fptr);
}

void continueGame() {
	FILE* fptr = fopen("checkers.dat", "rb+");
	count(fptr);
	move(fptr);
}

void endGame() {

	if (whiteNumber > blackNumber)
		cout << blue << "THE WINNER IS WHITE, CONGRATULATIONS" << white << endl;
	if (whiteNumber < blackNumber)
		cout << blue << "THE WINNER IS BLACK, CONGRATULATIONS" << white << endl;
	if (whiteNumber == blackNumber)
		cout << blue << "BLACK AND WHITE ARE EQUAL, NO WINNER " << white << endl;

	exit(1);
}

char readFile(FILE* fptr, int col, int row) {

	char cm[3];
	fseek(fptr, row * (24 + 2) + (col - 1) * 3, SEEK_SET);
	fread(cm, sizeof(cm), 1, fptr);	
	return cm[0];
}

void writeFile(FILE* fptr, int k, int l, int m, int n) {
	char field[3];
	char ch[3];
	char cm[3];
	field[0] = ' ';
	field[1] = ' ';
	field[2] = ' ';

	fseek(fptr, l * (24 + 2) + (k - 1) * 3, SEEK_SET);
	fread(ch, sizeof(ch), 1, fptr);
	fseek(fptr, n * (24 + 2) + (m - 1) * 3, SEEK_SET);
	fread(cm, sizeof(cm), 1, fptr);

	fseek(fptr, l * (24 + 2) + (k - 1) * 3, SEEK_SET);
	fwrite(field, sizeof(field), sizeof(char), fptr);


	if (ch[0] == 'w') { // oynanan ta� siyah m� beyaz m� kontrol�
		if (n >= 7) { // dama olma kontrol� (beyazsa son sat�ra gelmeli)
			ch[1] = 'w';
		}
	}
	else if (ch[0] == 'b') {
		if (n <= 0) { //siyahsa ilk sat�ra gelmeli
			ch[1] = 'b';
		}		
	}
	

	fseek(fptr, n * (24 + 2) + (m - 1) * 3, SEEK_SET);
	fwrite(ch, sizeof(ch), sizeof(char), fptr);
}

void capture(FILE* fptr, int col, int row, char a) {
	char field[3];
	field[0] = ' ';
	field[1] = ' ';
	field[2] = ' ';

	fseek(fptr, row * (24 + 2) + (col - 1) * 3, SEEK_SET);
	fwrite(field, sizeof(field), sizeof(char), fptr);

	if (a == 'w')
		whiteNumber--;
	else if (a == 'b')
		blackNumber--;
	if (whiteNumber == 0) {
		cout << "GAME OVER WINNER BLACK " << endl;
	}
	else if (blackNumber == 0) {
		cout << "GAME OVER WINNER WHITE " << endl;
	}
}

void move(FILE* fptr) {
	
	string a;
	char b[5];
	char seq[8];
	char ch[3];
	char cm[3];


	int k = 0;
	while (1) {

		char turn = getTurn(fptr);
		draw(fptr);

		if (turn == 'w') {
			cout << endl << endl << red << "WHITE'S TURN " << white << endl << endl;

		}
		else if (turn == 'b') {
			cout << endl << endl << red << "BLACK'S TURN " << white << endl << endl;

		}
		cout << "Enter your selection," << blue << "press X to end game \n" << white ;
		cin >> a;
		if (a == "X") {
			endGame();
			break;
		}
		strcpy_s(b, a.c_str());
		int col1 = value(b[0]);
		int row1 = b[1] - '0';
		int col2 = value(b[2]);
		int row2 = b[3] - '0';

		fseek(fptr, row1 * (24 + 2) + (col1 - 1) * 3, SEEK_SET);
		fread(ch, sizeof(ch), 1, fptr);
		fseek(fptr, row2 * (24 + 2) + (col2 - 1) * 3, SEEK_SET);
		fread(cm, sizeof(cm), 1, fptr);
		
		
		if (isEmpty(cm[0])) { // Gidece�i yer bo� mu kontrol� 
			if (!(ch[1] == 'w' || ch[1] == 'b')) { //oynayan ta� dama de�il ise
				if (ch[0] == 'w') {   // oynayan tas beyaz m�
					if (row1 <= row2) { // geri gitme kontrol�
						if (col1 == col2) { // ayn� s�tunda m� i�lem yap�l�yor
							if (row1 == row2 - 1) { // ayn� s�tun ve tek ileri hamle yap�l�yor
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('w', b[0], b[1], b[2], b[3]);
								setTurn(fptr);
							}
							else if (row1 == row2 - 2) { //atlama kontrol�
								char readingChar = readFile(fptr, col2, row2-1);
								if (readingChar == 'b') {
									capture(fptr, col2, row2-1, readingChar);
									writeFile(fptr, col1, row1, col2, row2);
									seqFile('w', b[0], b[1], b[2], b[3]);
									
								}
								else if (readingChar == 'w') {
									cout << red << "You can't jump your own stone" << white << endl;
								}
							}
							else {
								cout << red << "You entered incorrectly, Please try again" << white << endl;
							}
						}
						else if (col1 == col2 + 1 || col1 == col2 - 1) {// sa�a ya da sola 1 birim hareket etme kontrol�
							if (row1 == row2) { //�apraz gitme kontrol�
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('w', b[0], b[1], b[2], b[3]);
								setTurn(fptr);
							}
							else {
								cout << red << "You can't move diagonally" << white << endl;
							}
						}
						else if(col1 == col2 + 2 || col1 == col2 - 2) {// sa�a ya da sola 2 birim hareket etme kontrol�
							if (row1 == row2) { //�apraz gitme kontrol�
								char readingChar = readFile(fptr, col2 - 1, row2 );
								if (readingChar == 'b') { //atlamaya �al���lan ta� kendi ta�� m�
									capture(fptr, col2 - 1, row2, readingChar);
									writeFile(fptr, col1, row1, col2, row2);
									seqFile('w', b[0], b[1], b[2], b[3]);

								}
								else if (readingChar == 'w') {
									cout << red << "You can't jump your own stone" << white << endl;
								}
							}
							else {
								cout << red << "You can't move diagonally" << white << endl;
							}
						}
					}
					else {
						cout << red << "You can't move back !!" << white << endl;
					}
				}
				else if (ch[0] == 'b') { // oynayan ta� siyah m�
					if (row1 >= row2) { // geri gitme kontrol�
						if (col1 == col2) { // ayn� s�tunda m� i�lem yap�l�yor
							if (row1 == row2 + 1) { // ayn� s�tun ve tek ileri hamle yap�l�yor
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('b', b[0], b[1], b[2], b[3]);
								setTurn(fptr);
							}
							else if (row1 == row2 + 2) { //atlama kontrol�
								char readingChar = readFile(fptr, col2, row2 + 1);
								if (readingChar == 'w') { //atlamaya �al���lan ta� kendi ta�� m�
									capture(fptr, col2, row2 + 1, readingChar);
									writeFile(fptr, col1, row1, col2, row2);
									seqFile('b', b[0], b[1], b[2], b[3]);

								}
								else if (readingChar == 'b') {
									cout << red << "You can't jump your own stone" << white << endl;
								}
							}
							else {
								cout << red << "You entered incorrectly, Please try again" << white << endl;
							}
						}
						else if (col1 == col2 + 1 || col1 == col2 - 1) {// sa�a ya da sola 1 birim hareket etme kontrol�
							if (row1 == row2) { //�apraz gitme kontrol�
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('b', b[0], b[1], b[2], b[3]);
								setTurn(fptr);
							}
							else {
								cout << red << "You can't move diagonally" << white << endl;
							}
						}
						else if (col1 == col2 + 2 || col1 == col2 - 2) {// sa�a ya da sola 2 birim hareket etme kontrol�
							if (row1 == row2) { //�apraz gitme kontrol�
								char readingChar;
								int temp;
								if (col1 == col2 + 2) {
									readingChar = readFile(fptr, col2 + 1, row2);
									temp = col2 + 1;
								}
								else if (col1 == col2 - 2) {
									
									readingChar = readFile(fptr, col2 - 1, row2);
									temp = col2 - 1;
								}
								
								if (readingChar == 'w') {
									capture(fptr, temp, row2, readingChar);
									writeFile(fptr, col1, row1, col2, row2);
									seqFile('b', b[0], b[1], b[2], b[3]);

								}
								else if (readingChar == 'b') {
									cout << red << "You can't jump your own stone" << white << endl;
								}								
							}
							else {
								cout << red << "You can't move diagonally" << white << endl;
							}
						}
					}
					else {
						cout << red << "You can't move back!" << white << endl;
					}
				}
			}
			else if(ch[1] == 'w' || ch[1] == 'b'){ // oynayan ta� dama ise
				int difference;
				char control, control1;
				bool control2 = true;
				int temp3 = row2;
				if (ch[0] == 'w') { // dama beyaz ise
					if (col1 == col2) { // ileri-geri hareket etmek istiyor ise
						difference = abs(row1 - row2);
						if (row2 > row1) {
							int j;
							int i;
							int temp2 = row1;
							for (j = 0; j < difference; j++) {
								control = readFile(fptr, col2, temp2 + 1);
								control1 = readFile(fptr, col2, temp2 + 2);
								temp2++;
								if (control == 'w') {
									cout << red << "You can't jump your own stone" << white << endl;
									control2 = false;
									break;
								}
								else if (control == 'b' && control1 == 'b' || control == 'b' && control1 == 'w') {
									control2 = false;
								}
							}

							if (control2) {
								int temp = row1;
								for (i = 0; i < difference; i++) {
									control = readFile(fptr, col2, temp + 1);
									temp++;

									if (control == 'b') {
										control = readFile(fptr, col2, temp + 1);
										if (control == ' ') {
											capture(fptr, col2, temp, control);

										}

									}

								}
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('w', b[0], b[1], b[2], b[3]);
							}
						}
						else if (row1 > row2) {
							
							int j;
							int i;
							int temp2 = row1;
							for (j = 0; j < difference; j++) {
								control = readFile(fptr, col2, temp2-1);
								control1 = readFile(fptr, col2, temp2-2);
								temp2--;
								if (control == 'w') {
									cout << red << "You can't jump your own stone" << white << endl;
									control2 = false;
									break;
								}
								else if (control == 'b' && control1 == 'b' || control == 'b' && control1 == 'w') {
									control2 = false;
									cout << red << "You can't jump " << white << endl;
								}
							}

							if (control2) {
								int temp = row1;
								for (i = 0; i < difference; i++) {
									control = readFile(fptr, col2, temp - 1);
									temp--;

									if (control == 'b') {
										control = readFile(fptr, col2, temp - 1);
										if (control == ' ') {
											capture(fptr, col2, temp, control);
											
										}

									}
									
								}
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('w', b[0], b[1], b[2], b[3]);
							}											
						}
					}
					else if(row1 == row2) { // sa�-sol a hareket etmek istiyor ise
						difference = abs(col1 - col2);

						if (col2 > col1) {
							int j;
							int i;
							int temp2 = col1;
							for (j = 0; j < difference; j++) {
								control = readFile(fptr, temp2 + 1, row2 );
								control1 = readFile(fptr, temp2 + 2, row2);
								temp2++;
								if (control == 'w') {
									cout << red << "You can't jump your own stone" << white << endl;
									control2 = false;
									break;
								}
								else if (control == 'b' && control1 == 'b' || control == 'b' && control1 == 'w') {
									cout << "You can't move there" << endl;
									control2 = false;
								}
							}

							if (control2) {
								int temp = col2;
								for (i = 0; i < difference; i++) {
									control = readFile(fptr, temp + 1, row2 );
									temp++;

									if (control == 'b') {
										control = readFile(fptr, temp + 1, row2);
										if (control == ' ') {
											capture(fptr, temp + 1, row2, control);

										}

									}

								}
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('w', b[0], b[1], b[2], b[3]);
							}
						}
						else if (col1 > col2) {

							int j;
							int i;
							int temp2 = col2;
							for (j = 0; j < difference; j++) {
								control = readFile(fptr, temp2 - 1, row2);
								control1 = readFile(fptr, temp2 - 2, row2);
								temp2--;
								if (control == 'w') {
									cout << red << "You can't jump your own stone" << white << endl;
									control2 = false;
									break;
								}
								else if (control == 'b' && control1 == 'b' || control == 'b' && control1 == 'w') {
									control2 = false;
									cout << red << "You can't jump " << white << endl;
								}
							}

							if (control2) {
								int temp = col1;
								for (i = 0; i < difference; i++) {
									control = readFile(fptr, temp - 1, row2);
									temp--;

									if (control == 'b') {
										control = readFile(fptr, temp - 1, row2);
										if (control == ' ') {
											capture(fptr, temp, row2, control);

										}

									}

								}
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('w', b[0], b[1], b[2], b[3]);
							}
						}
					}
					else {
						cout << red << "You ,can't move diagonally!" << white << endl;
					}
				}
				else if (ch[0] == 'b') { // dama siyah ise
					if (col1 == col2) { // ileri-geri hareket
						difference = abs(row1 - row2);
						if (row2 > row1) {
							int j;
							int i;
							int temp2 = row1;
							for (j = 0; j < difference; j++) {
								control = readFile(fptr, col2, temp2 + 1);
								control1 = readFile(fptr, col2, temp2 + 2);
								temp2++;
								if (control == 'b') {
									cout << red << "You can't jump your own stone" << white << endl;
									control2 = false;
									break;
								}
								else if (control == 'b' && control1 == 'b' || control == 'b' && control1 == 'w') {
									control2 = false;
								}
							}

							if (control2) {
								int temp = row1;
								for (i = 0; i < difference; i++) {
									control = readFile(fptr, col2, temp + 1);
									temp++;

									if (control == 'w') {
										control = readFile(fptr, col2, temp + 1);
										if (control == ' ') {
											capture(fptr, col2, temp, control);

										}

									}

								}
								writeFile(fptr, col1, row1, col2, row2); 
								seqFile('b', b[0], b[1], b[2], b[3]);
							}
						}
						else if (row1 > row2) {

							int j;
							int i;
							int temp2 = row1;
							for (j = 0; j < difference; j++) {
								control = readFile(fptr, col2, temp2 - 1);
								control1 = readFile(fptr, col2, temp2 - 2);
								temp2--;
								if (control == 'b') {
									cout << red << "You can't jump your own stone" << white << endl;
									control2 = false;
									break;
								}
								else if (control == 'w' && control1 == 'w' || control == 'w' && control1 == 'b') {
									control2 = false;
									cout << red << "You can't jump " << white << endl;
								}
							}

							if (control2) {
								int temp = row1;
								for (i = 0; i < difference; i++) {
									control = readFile(fptr, col2, temp - 1);
									temp--;

									if (control == 'w') {
										control = readFile(fptr, col2, temp - 1);
										if (control == ' ') {
											capture(fptr, col2, temp, control);

										}

									}

								}
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('b', b[0], b[1], b[2], b[3]);
							}
						}
					}
					else if (row1 == row2) { // sa�-sol a hareket etmek istiyor ise
						difference = abs(col1 - col2);

						if (col2 > col1) {
							int j;
							int i;
							int temp2 = col1;
							for (j = 0; j < difference; j++) {
								control = readFile(fptr, temp2 + 1, row2);
								control1 = readFile(fptr, temp2 + 2, row2);
								temp2++;
								if (control == 'b') {
									cout << red << "You can't jump your own stone" << white << endl;
									control2 = false;
									break;
								}
								else if (control == 'w' && control1 == 'w' || control == 'w' && control1 == 'b') {
									cout << "You can't move there" << endl;
									control2 = false;
								}
							}

							if (control2) {
								int temp = col2;
								for (i = 0; i < difference; i++) {
									control = readFile(fptr, temp + 1, row2);
									temp++;

									if (control == 'w') {
										control = readFile(fptr, temp + 1, row2);
										if (control == ' ') {
											capture(fptr, temp + 1, row2, control);

										}

									}

								}
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('b', b[0], b[1], b[2], b[3]);
							}
						}
						else if (col1 > col2) {

							int j;
							int i;
							int temp2 = col2;
							for (j = 0; j < difference; j++) {
								control = readFile(fptr, temp2 - 1, row2);
								control1 = readFile(fptr, temp2 - 2, row2);
								temp2--;
								if (control == 'b') {
									cout << red << "You can't jump your own stone" << white << endl;
									control2 = false;
									break;
								}
								else if (control == 'w' && control1 == 'w' || control == 'w' && control1 == 'b') {
									control2 = false;
									cout << red << "You can't jump " << white << endl;
								}
							}

							if (control2) {
								int temp = col1;
								for (i = 0; i < difference; i++) {
									control = readFile(fptr, temp - 1, row2);
									temp--;

									if (control == 'w') {
										control = readFile(fptr, temp - 1, row2);
										if (control == ' ') {
											capture(fptr, temp, row2, control);

										}

									}

								}
								writeFile(fptr, col1, row1, col2, row2);
								seqFile('b', b[0], b[1], b[2], b[3]);
							}
						}
					}
					else {
						cout << red << "You ,can't move diagonally!" << white << endl;
					}									   					 
				}
			}
			else if (!(ch[0] == 'w' || ch[0] == 'b')) {
			cout << red << "Your choice is empty, Please make another selection!" << white << endl;
			}
		}
		else {
			cout << red << "Your choice is full, Please make another selection" << white << endl;
		}
	}
}

void count(FILE * fptr) {
	char dama[206];
	fseek(fptr, 1, SEEK_SET);
	fread(dama, sizeof(dama), 1, fptr);

	for (int i = 0; i < 199; i++) {
		if (dama[i] == 'w') {
			whiteNumber++;
			i = i + 2;
		}
		else if (dama[i] == 'b') {
			blackNumber++;
			i = i + 2;
		}
	}
}









int main() {

	int choice = 0;
	cout << blue << "******************************************** " << white << endl;
	cout << "WELCOME TO CHECKERS GAME" << endl;
	cout << "1 ---> New Game" << endl;
	cout << "2 ---> Continue Game" << endl;
	cout << "3 ---> End Game" << endl << endl;
	cout << blue << "******************************************** " << white << endl;
	cout << red << "Please enter your selection" << white << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		newGame();
		
		break;
	case 2:
		continueGame();
		break;
	case 3:
		endGame();
		break;
	default:
		break;
	}


}
