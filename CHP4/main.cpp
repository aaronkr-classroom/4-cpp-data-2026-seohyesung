// main.cpp
// 중간고사, 기말고사, 그리고 과제 점수 몇개를 받고
// 마지막 평균 결과 점수를 계산하기.

#include <iostream>
#include <vector>
#include <ios>
#include <string>
#include <iomanip>
#include <algorithm>
#include <stdexcept> // istream& read_hw()에서 domain_error 예외를 던지기 위해 필요
#include "Student_info.h"
#include "grade.h"

using namespace std;

typedef vector<double>::size_type vec_sz;
vector<Student_info>::size_type si_sz;

// 함수 원형 정의문
double grade(double, double, const vector<double>&);
double grade(double, double, double);
double median(vector<double>);

int main(void) {
	//새로운 구조 자료형 선언
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	// 프로그램 설명하기
	cout << "For every student, enter\n: " << endl <<
		"  name midterm final hw1 hw2 ..." << endl;

	while (read(cin, record)) {
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
	}

	// 학생 정보를 알파벳순으로 정렬
	sort(students.begin(), students.end(), compare);

	// 모든 학생의 결과를 출력
	for (si_sz i = 0; i != students.size(); ++i) {
		// 이름과 오른쪽 공백을 포함하여 maxlen + 1개의 문자를 출력
		cout << students[i].name << 
			string(maxlen + 1 - students[i].name.size(), ' ');

		// 최종 점수를 계산하여 출력
		try {
			double final_grade = grade(students[i]); // NEW 계산하는 함수 grade()
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade 
				<< setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what();
		}
		cout << endl;
	}


	return 0;
}

// 중간고사 점수, 기말고사 점수, 그리고 과제 점수 벡터로 학생의 종합
// 점수를 구함, 이 함수는 인수를 복사하지 않고 median 함수가
// 해당 작업을 실행
double grade(double mid, double fin, const vector<double>& hw) {
	if (hw.size() == 0) {
		throw domain_error("no homework");
	}

	//return 0.2 * mid + 0.4 * fin + 0.4 * (hw1 + hw2 ...) / hw.size();
	// 또는 NEW grade() 함수
	return grade(mid, fin, median(hw));
}

//계산하는 grade 함수
double grade(double midterm, double final, double homework) {
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
	return 0.2 * midterm + 0.4 * final + 0.4 * homework * 0.4;
}

//vector<double>의 중앙값을 구함
// 함수를 호출하면 인수로 제공된 벡터를 통째로 복사
double median(vector<double> vec) {
	vec_sz size = vec.size();

	if (size == 0) {
		throw domain_error("median of empty vector!");
		return 1;
	}

	sort(vec.begin(), vec.end());
	vec_sz mid = size / 2;
	return size % 2 == 0
		? (vec[mid] + vec[mid - 1]) / 2 // 참일 때 반환
		: vec[mid]; // 거짓일 때 반환
}

