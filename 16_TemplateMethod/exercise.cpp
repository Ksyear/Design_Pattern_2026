// [연습] 템플릿 메소드 패턴 - 데이터 마이닝 앱 (refactoring.guru 예제)
//
// 시나리오
//   PDF / DOC / CSV 파일에서 데이터를 뽑아 분석하고 보고서를 만든다.
//   파일을 여는 방식과 파싱만 다르고 나머지 흐름은 완전히 같다.
//
// TODO 1. DataMiner 추상 클래스에 템플릿 메소드 mine(path)를 만들 것
//         순서: openFile -> extractData -> parseData -> analyze -> sendReport -> closeFile
// TODO 2. openFile / extractData / parseData / closeFile 을 추상 단계로
//         analyze / sendReport 를 공통 단계로 둘 것
// TODO 3. PDFDataMiner / CSVDataMiner / DOCDataMiner 구현 (출력만 해도 충분)
// TODO 4. mine()에 virtual을 붙이지 말 것. 왜 그래야 하는지 주석으로 적을 것
// TODO 5. 후크 하나를 추가할 것
//         예: virtual bool needsPreprocessing() const { return false; }
//         CSV만 true로 재정의해 전처리 단계가 끼어들게 한다
//
// 전략 패턴과의 비교 (시험에 잘 나온다)
//   - 템플릿 메소드: 상속. 컴파일 때 결정. 클래스 '일부'를 바꾼다
//   - 전략        : 구성. 실행 중 교체 가능. 알고리즘 '전체'를 바꾼다
//
// LSP 함정
//   서브클래스가 필수 단계를 빈 구현으로 덮어 버리면 알고리즘이 깨진다
//   -> refactoring.guru가 지적하는 "리스코프 치환 원칙 위반 위험"

#include <iostream>

int main() {
	std::cout << "TODO: 데이터 마이닝 템플릿 메소드를 만들어 보세요\n";
	return 0;
}
