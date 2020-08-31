#include <stdio.h>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

//함수선언
int* Preprocessing(const char* P);
void KMP(string A, const char* P);

void main() {

	const char* P = "Further Reading about Standards";      //패턴문자열
	//const char* P = "17650    20000818";
	ifstream in("test1.txt");
	string A;      //텍스트문자열

	if (in.is_open()) {

		//위치 지정자를 파일의 끝으로 옮김
		in.seekg(0, ios::end);

		//파일의 끝 위치를 읽는다. (즉, 파일의 크기)
		int size = in.tellg();

		//파일 크기만큼의 문자열을 할당한다.
		A.resize(size);

		// 위치 지정자를 파일의 시작으로 옮김
		in.seekg(0, ios::beg);

		// 파일 전체 내용을 읽어서 문자열에 저장한다.
		in.read(&A[0], size);

	}
	else {
		printf("파일을 찾을 수 없습니다!");

	}
	printf("<기본정보>\n\n\t패턴문자열 P ={");
	for (int i = 0; i < strlen(P); i++) {
		printf("%c", P[i]);
	}
	printf("}\n\n");

	//KMP함수호출
	KMP(A, P);

}

//pi배열을 만드는 함수입니다.
int* Preprocessing(const char* P) {      //패턴문자열만으로 분석하는 것.

	int j = 1; int k = 0;

	int* pi = new int[strlen(P) + 2];      //pi배열 동적생성, indexing은1부터 +1 기타문자열 처리 +1
	memset(pi, 0, _msize(pi));      //생성된 pi배열의 값을 0으로 초기화

	/*교과서의 pi배열과 달리 전체적으로 -1씩 해야한다.
	텍스트문자열과 패턴문자열의 indexing이 0부터이기때문.*/
	pi[0] = -1;
	while (j <= strlen(P) + 1) {

		if (k == 0 || P[j-1] == P[k-1]) {

			j++;
			k++;
			pi[j] = k - 1; //pi배열에 돌아갈 index저장 

		}
		else {
			k = pi[k - 1];   //mismatching이면 k는 다시 처음으로.
		}
	}

	//pi배열 출력해보는 부분.
	printf("\tpi배열은");
	for (int i = 1; i < j; i++) {
		printf("%d ", pi[i]);
	}

	return pi;      //완성된 pi배열의 주솟값 return.
}

//pi배열을 이용해서 텍스트문자열에서 패턴문자열과의 matching을 찾는 함수
void KMP(string A, const char* P) {

	double kmp_elapsed_time;
	clock_t before = clock();   //현재 시간 저장

	int j = 0; int i = 0; int count = 0; int jcount = 0;
	int textlen = A.length();
	int patlen = strlen(P);
	printf("\t텍스트문자열의 길이는 %d, 패턴문자열의 길이는 %d \n\n", textlen, patlen);      //기본정보출력을 위함.

	int* pi = Preprocessing(P);      //미리 만들어둔 pi배열 호출.

	printf("\n\n<KMP Matching Algorithm 실행 결과>");
	while (i < textlen) {

		if (j == -1 || A[i] == P[j]) {      //앞서 만든 pi[0] = -1때문에 j도 -1.
			i++; j++;
		}
		else {
			j = pi[j];     //mismatchig이 일어나면 pi배열로 만들어둔대로 jump
		}

		if (j == patlen) {

			printf("\n\n\t찾으시는 패턴문자열은 텍스트문자열의 [%d] 위치에서 매칭되었습니다!", i - patlen);
			j = pi[j];      //matching이 일어나고 나서 패턴 문자열 index를 초기화.
			count++;      //matching이 일어난 빈도


		}
	}
	if (count == 0) printf("\n\n\t패턴문자열을 찾지 못했습니다.");


	kmp_elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;  // 초 단위로 경과 시간을 측정함
	fprintf(stdout, "\n\n\tKMP Matching으로 패턴문자열을 찾는데 걸린 시간(초): %5.2f\n\n", kmp_elapsed_time);

}