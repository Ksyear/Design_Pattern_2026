#ifndef SUBJECT_BATTERYPUBLISHER_H
#define SUBJECT_BATTERYPUBLISHER_H

#include <vector>

#include "msg/BatteryState.h"
#include "subject/Publisher.h"

class BatteryPublisher : public Publisher {
public:
	void subscribe(Subscriber* sub) override;
	void unsubscribe(Subscriber* sub) override;
	void notify() override;

	void publish(const BatteryState& msg);

	const BatteryState& state() const;

private:
	std::vector<Subscriber*> subscribers_;
	BatteryState state_{};
};

#endif
