#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "px4_msgs/msg/sensor_gps.hpp"

using std::placeholders::_1;

class GpsBridgeNode : public rclcpp::Node
{
  public:
    GpsBridgeNode(): Node("gps_bridge_node")
    {
      subscription_ = this->create_subscription<px4_msgs::msg::SensorGps>
        ("/fmu/out/vehicle_gps_position", rclcpp::SensorDataQoS(),std::bind(&GpsBridgeNode::gps_callback, this, _1));
      publisher_ = this->create_publisher<sensor_msgs::msg::NavSatFix>("/gps/fix", rclcpp::SensorDataQoS());

      RCLCPP_INFO(this->get_logger(), "GPS Bridge Initialized");
    }

  private:
    void gps_callback(const px4_msgs::msg::SensorGps::SharedPtr msg)
    {
      sensor_msgs::msg::NavSatFix fix;

      fix.header.stamp = this->now();
      fix.header.frame_id = "gps_link";

      fix.latitude  = msg->latitude_deg;
      fix.longitude = msg->longitude_deg;
      fix.altitude  = msg->altitude_msl_m;

      fix.status.status =
        (msg->fix_type >= 3)
          ? sensor_msgs::msg::NavSatStatus::STATUS_FIX
          : sensor_msgs::msg::NavSatStatus::STATUS_NO_FIX;

      fix.status.service = sensor_msgs::msg::NavSatStatus::SERVICE_GPS;

      publisher_->publish(fix);
    }

  rclcpp::Subscription<px4_msgs::msg::SensorGps>::SharedPtr subscription_;
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GpsBridgeNode>());
  rclcpp::shutdown();
  return 0;
}