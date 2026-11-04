#ifndef SPEC_ROBOTSPEC_H
#define SPEC_ROBOTSPEC_H

#include <memory>
#include <string>
#include <vector>

// Prototype - "나를 닮은 새 것을 하나 만들어 달라" 고 할 수 있는 로봇 명세.
//
// 자바의 clone() 과 다른 점 : C++ 에서는 가상 clone() 이 unique_ptr<Base> 를 돌려준다.
//   - 슬라이싱을 피하려면 값이 아니라 포인터로 돌려줘야 한다
//   - 소유권을 누가 갖는지 분명해야 하므로 원시 포인터가 아니라 unique_ptr
//
// 로봇에서의 자리 : Gazebo 에 같은 기종을 여러 대 띄울 때
//   spawn_entity 로 URDF 를 넘기는 대신, 이미 설정이 끝난 객체를 복제한다.
//   센서 목록과 파라미터를 처음부터 다시 조립하지 않아도 된다는 것이 이득이다.
class RobotSpec {
public:
	RobotSpec(std::string model, std::vector<std::string> sensors, double maxSpeed);
	virtual ~RobotSpec() = default;

	virtual std::unique_ptr<RobotSpec> clone() const = 0;
	virtual std::string role() const = 0;

	void placeAt(std::string namespaceName, double x, double y);
	void addSensor(const std::string& sensor);

	void describe() const;

protected:
	// 복사 생성자는 파생 클래스의 clone() 이 쓴다.
	// 멤버가 전부 값 타입(string / vector / double)이라 기본 복사로 충분하다
	// -> 깊은 복사가 공짜로 된다. 포인터 멤버가 생기는 순간 직접 써야 한다.
	RobotSpec(const RobotSpec&) = default;

private:
	std::string model_;
	std::vector<std::string> sensors_;
	double maxSpeed_;
	std::string namespace_ = "(미배치)";
	double x_ = 0.0;
	double y_ = 0.0;
};

#endif
