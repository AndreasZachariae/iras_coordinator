/** *******************************************************
 * IRAS - University of Applied Sciences Karlsruhe
 * Module : ROS2-Node "IRASoordinator"
 * Purpose : Checks the ROS2-Topic "BatteryState"
 *
 * @author Andreas Zachariae
 * @author Moritz Weisenböhler
 * @since 1.0.0 (2020.08.26)
 *********************************************************/
#pragma once

#include <iras_coordinator/default.h>

#include <sensor_msgs/msg/battery_state.hpp>

#include <iras_behaviortree_ros2/components/RosCondition.h>

// TODO: add port with threshold battery level

class CheckBattery : public RosCondition
{
public:
    static BT::PortsList providedPorts() { return BT::PortsList(); }

    CheckBattery(const std::string &name, const BT::NodeConfiguration &config);

    BT::NodeStatus on_check() override;

private:
    rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr battery_state_subscription_;

    float battery_percentage_ = 1;
};