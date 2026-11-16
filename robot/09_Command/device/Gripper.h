#ifndef DEVICE_GRIPPER_H
#define DEVICE_GRIPPER_H

// Receiver - 그리퍼. 열고 닫는 것만 안다.
class Gripper {
public:
	void open();
	void close();
	bool isClosed() const;

private:
	bool closed_ = false;
};

#endif
