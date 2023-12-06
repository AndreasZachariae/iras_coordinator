#include <iras_coordinator/conditions/CheckDiagnosticStatus.h>

CheckDiagnosticStatus::CheckDiagnosticStatus(const std::string &name, const BT::NodeConfiguration &config) : RosCondition(name, config)
{
    stop_publisher_ = get_node_handle()->create_publisher<std_msgs::msg::Empty>("Stop", 10);

    diagnostic_status_subscription_ = get_node_handle()->create_subscription<diagnostic_msgs::msg::DiagnosticStatus>("DiagnosticStatus", 10, [&](const diagnostic_msgs::msg::DiagnosticStatus::SharedPtr msg)
                                                                                                                     {
        if (msg->level == diagnostic_msgs::msg::DiagnosticStatus::ERROR)
        {
            //DiagnosticStatuses are recieved from multiple components,
            //if at least one has an ERROR, onCheck has to return FAILURE.
            diagnostic_error_ = true;

            log("[DiagnosticStatus] " + msg->name + " ID:" + msg->hardware_id + "Status NOT OK! /Stop published", LogLevel::Error);

            stop_publisher_->publish(std_msgs::msg::Empty());
        } });
}

BT::NodeStatus CheckDiagnosticStatus::on_check()
{
    if (diagnostic_error_)
    {
        log("Diagnostic failed");
        return BT::NodeStatus::FAILURE;
    }

    return BT::NodeStatus::SUCCESS;
}