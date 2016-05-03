#include "led_sim.h"

LedSimNode::LedSimNode(int argc, char **argv, int rate, std::string name) {
  ledName = name;
  enabled = false;
  //publisher/param always initiated in this format
  publisher = n.advertise<ram_msgs::Led>("/qubo/led/" + ledName, 1000);
  n.setParam("qubo/led/" + ledName + "/enabled", DEFAULT_ENABLED);
}

LedSimNode::~LedSimNode() {}

void LedSimNode::update() {
  msg.led_name = ledName;
  msg.enabled = enabled;
  publisher.publish(msg);

  ros::spinOnce(); //magic method thats always included in update
}

void LedSimNode::enable() {
  enabled = true;
}

void LedSimNode::disable() {
  enabled = false;
}
