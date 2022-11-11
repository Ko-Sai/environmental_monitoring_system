#include "master_node/dummy_publisher.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "dummy_node");
  dummyPublisher dummy_obj;
  dummy_obj.run();
  ros::spin();
  return 0;
}