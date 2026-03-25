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

using namespace std;

typedef vector<double>::size_type vec_sz;

// 함수 원형 정의문
istream& read_hw(istream&, vector<double>&); 
double grade(double, double, const vector<double>&);
double grade(double, double, double);
double median(vector<double>);

int main(void) {
	// 학생의 이름을 묻고 읽음
	cout << "First name: ";
	string name;
	cin >> name;
	cout << "Hello, " << name << "!" << endl;

	// 학생의 중간고사, 기말고사, 그리고 과제 점수를 묻고 읽음
	cout << "Midterm + Final grades :";
	double midterm, final;
	cin >> midterm >> final;

	// 학생의 과제 점수를 묻고 읽음
	cout << "Enter all HW grades, then EOF: ";
	vector<double> homework;

	// NEW 함수 read_hw()
	read_hw(cin, homework); // 사실 객체 필요해서 참조로 보냄

	// 종합 점수를 계산하기
	double final_grade = grade(midterm, final, homework); // NEW 계산하는 함수 grade()
	streamsize prec = cout.precision();
	cout << "final grade: " << setprecision(3) << 
		final_grade << setprecision(prec) << endl;

	return 0;
}

// 입력 스트림에서 과제 점수를 읽어서 vector<double>에 저장하는 함수
istream& read_hw(istream& in, vector<double>& hw) {
	if (in) {
		// 이전 내용 제거
		hw.clear();

		// 과제 점수를 읽어서 벡터에 저장
		double x;

		while (in >> x) {
			hw.push_back(x);
		}

		// 다음 학생의 점수 입력 작업을 고려해 스트림을 지움
		in.clear();
	}
	return in;
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

