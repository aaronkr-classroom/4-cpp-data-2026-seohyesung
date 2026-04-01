// grade.cpp
#include "grade.h"
#include <stdexcept> // grade()에서 domain_error 예외를 던지기 위해 필요
#include <vector>
#include "median.h"
#include "Student_info.h"


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

// Student_info 계산
double grade(const Student_info& s) {
	return grade(s.midterm, s.final, s.homework);
}
