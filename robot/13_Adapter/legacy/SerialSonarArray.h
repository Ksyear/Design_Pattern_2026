#ifndef LEGACY_SERIALSONARARRAY_H
#define LEGACY_SERIALSONARARRAY_H

// Adaptee - 10년 된 초음파 센서 보드.
//
// 형식이 전부 다르다.
//   - 단위가 cm (표준은 m)
//   - 한 번에 하나씩 읽어야 한다 (표준은 배열 한 방)
//   - 측정 실패를 -1 로 준다 (표준은 0.0)
//   - 프레임 이름 같은 개념이 아예 없다
//
// 이 코드는 고칠 수 없다고 가정한다. 벤더가 준 바이너리이거나,
// 다른 장비 열 대가 이미 이 인터페이스에 의존하고 있거나, 검증이 끝난 코드다.
// 어댑터가 필요한 상황은 대개 "고칠 수 없다" 에서 시작한다.
class SerialSonarArray {
public:
	void openPort(const char* device);

	int sensorCount() const;
	int pingCentimeters(int index) const;  // 실패하면 -1

private:
	bool open_ = false;
};

#endif
