#ifndef GURU_CLIENT_CODE_H
#define GURU_CLIENT_CODE_H

namespace guru {

// 클라이언트 : 구상 전략을 골라 Context 에 꽂고, 도중에 갈아끼운다.
// 전략을 '고르는' 주체가 클라이언트라는 점이 상태 패턴(21_State)과 갈리는 지점이다.
void clientCode();

}   // namespace guru

#endif
