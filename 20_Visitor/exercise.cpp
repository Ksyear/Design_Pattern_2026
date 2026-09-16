// [연습] 비지터 패턴 - 표현식 트리 (AST)
//
// 컴파일러는 비지터 패턴의 본진이다. AST 노드 종류는 거의 안 늘지만
// 그 위를 도는 연산(평가, 출력, 최적화, 코드 생성)은 계속 늘기 때문이다.
//
// TODO 1. Expr(Element) 계층을 만들 것
//         - NumberExpr(double), AddExpr(l, r), MulExpr(l, r), NegExpr(e)
//         - 각각 accept(ExprVisitor&) 구현
// TODO 2. ExprVisitor 인터페이스에 visit 메소드 4개를 선언
// TODO 3. 구상 비지터 3개를 만들 것 (Expr 클래스는 한 줄도 고치지 말 것)
//         - EvalVisitor      : 값을 계산해 double로 돌려준다
//         - PrintVisitor     : "(1 + (2 * 3))" 형태로 출력
//         - CountNodeVisitor : 노드 개수를 센다
// TODO 4. 비지터가 값을 '반환'하게 하려면 어떻게 하는가?
//         C++에서는 visit이 void라 곤란하다. 두 가지 방법을 다 시도할 것
//         (a) 비지터 안에 result_ 멤버를 두고 마지막에 꺼낸다  <- 고전적 방식
//         (b) std::variant + std::visit 으로 아예 다르게 푼다   <- 모던 C++ 방식
//
// TODO 5. 단점 체험: PowExpr(거듭제곱) 노드를 추가해 볼 것
//         -> 비지터 3개를 전부 고쳐야 한다. 이게 비지터의 비용이다
//
// 표현 문제(Expression Problem)
//   - 상속:   '타입' 추가는 쉽고, '연산' 추가는 어렵다
//   - 비지터: '연산' 추가는 쉽고, '타입' 추가는 어렵다
//   어느 축이 더 자주 변하는지를 보고 고르는 것이 전부다

#include <iostream>

int main() {
	std::cout << "TODO: AST 비지터를 만들어 보세요\n";
	return 0;
}
