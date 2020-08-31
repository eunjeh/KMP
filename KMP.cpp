#include <stdio.h>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

//�Լ�����
int* Preprocessing(const char* P);
void KMP(string A, const char* P);

void main() {

	const char* P = "Further Reading about Standards";      //���Ϲ��ڿ�
	//const char* P = "17650    20000818";
	ifstream in("test1.txt");
	string A;      //�ؽ�Ʈ���ڿ�

	if (in.is_open()) {

		//��ġ �����ڸ� ������ ������ �ű�
		in.seekg(0, ios::end);

		//������ �� ��ġ�� �д´�. (��, ������ ũ��)
		int size = in.tellg();

		//���� ũ�⸸ŭ�� ���ڿ��� �Ҵ��Ѵ�.
		A.resize(size);

		// ��ġ �����ڸ� ������ �������� �ű�
		in.seekg(0, ios::beg);

		// ���� ��ü ������ �о ���ڿ��� �����Ѵ�.
		in.read(&A[0], size);

	}
	else {
		printf("������ ã�� �� �����ϴ�!");

	}
	printf("<�⺻����>\n\n\t���Ϲ��ڿ� P ={");
	for (int i = 0; i < strlen(P); i++) {
		printf("%c", P[i]);
	}
	printf("}\n\n");

	//KMP�Լ�ȣ��
	KMP(A, P);

}

//pi�迭�� ����� �Լ��Դϴ�.
int* Preprocessing(const char* P) {      //���Ϲ��ڿ������� �м��ϴ� ��.

	int j = 1; int k = 0;

	int* pi = new int[strlen(P) + 2];      //pi�迭 ��������, indexing��1���� +1 ��Ÿ���ڿ� ó�� +1
	memset(pi, 0, _msize(pi));      //������ pi�迭�� ���� 0���� �ʱ�ȭ

	/*�������� pi�迭�� �޸� ��ü������ -1�� �ؾ��Ѵ�.
	�ؽ�Ʈ���ڿ��� ���Ϲ��ڿ��� indexing�� 0�����̱⶧��.*/
	pi[0] = -1;
	while (j <= strlen(P) + 1) {

		if (k == 0 || P[j-1] == P[k-1]) {

			j++;
			k++;
			pi[j] = k - 1; //pi�迭�� ���ư� index���� 

		}
		else {
			k = pi[k - 1];   //mismatching�̸� k�� �ٽ� ó������.
		}
	}

	//pi�迭 ����غ��� �κ�.
	printf("\tpi�迭��");
	for (int i = 1; i < j; i++) {
		printf("%d ", pi[i]);
	}

	return pi;      //�ϼ��� pi�迭�� �ּڰ� return.
}

//pi�迭�� �̿��ؼ� �ؽ�Ʈ���ڿ����� ���Ϲ��ڿ����� matching�� ã�� �Լ�
void KMP(string A, const char* P) {

	double kmp_elapsed_time;
	clock_t before = clock();   //���� �ð� ����

	int j = 0; int i = 0; int count = 0; int jcount = 0;
	int textlen = A.length();
	int patlen = strlen(P);
	printf("\t�ؽ�Ʈ���ڿ��� ���̴� %d, ���Ϲ��ڿ��� ���̴� %d \n\n", textlen, patlen);      //�⺻��������� ����.

	int* pi = Preprocessing(P);      //�̸� ������ pi�迭 ȣ��.

	printf("\n\n<KMP Matching Algorithm ���� ���>");
	while (i < textlen) {

		if (j == -1 || A[i] == P[j]) {      //�ռ� ���� pi[0] = -1������ j�� -1.
			i++; j++;
		}
		else {
			j = pi[j];     //mismatchig�� �Ͼ�� pi�迭�� �����д�� jump
		}

		if (j == patlen) {

			printf("\n\n\tã���ô� ���Ϲ��ڿ��� �ؽ�Ʈ���ڿ��� [%d] ��ġ���� ��Ī�Ǿ����ϴ�!", i - patlen);
			j = pi[j];      //matching�� �Ͼ�� ���� ���� ���ڿ� index�� �ʱ�ȭ.
			count++;      //matching�� �Ͼ ��


		}
	}
	if (count == 0) printf("\n\n\t���Ϲ��ڿ��� ã�� ���߽��ϴ�.");


	kmp_elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;  // �� ������ ��� �ð��� ������
	fprintf(stdout, "\n\n\tKMP Matching���� ���Ϲ��ڿ��� ã�µ� �ɸ� �ð�(��): %5.2f\n\n", kmp_elapsed_time);

}