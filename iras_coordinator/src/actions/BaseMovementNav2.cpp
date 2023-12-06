#include <iras_coordinator/actions/BaseMovementNav2.h>

void BaseMovementNav2::on_send(NavigateToPoseROS2Nav::Goal &goal)
{
    // Check if Optional is valid. If not, throw its error
    BT::Optional<std::string> frame_id = getInput<std::string>("frame_id");
    BT::Optional<float> x_input = getInput<float>("x");
    BT::Optional<float> y_input = getInput<float>("y");
    BT::Optional<float> quaternion_x = getInput<float>("quaternion_x");
    BT::Optional<float> quaternion_y = getInput<float>("quaternion_y");
    BT::Optional<float> quaternion_z = getInput<float>("quaternion_z");
    BT::Optional<float> quaternion_w = getInput<float>("quaternion_w");

    if (!x_input.has_value())
    {
        throw BT::RuntimeError("missing required input [x]: ", x_input.error());
    }

    if (!y_input.has_value())
    {
        throw BT::RuntimeError("missing required input [y]: ", y_input.error());
    }

    if (quaternion_x.has_value())
    {
        goal.pose.pose.orientation.x = quaternion_x.value();
    }

    if (quaternion_y.has_value())
    {
        goal.pose.pose.orientation.y = quaternion_y.value();
    }

    if (quaternion_z.has_value())
    {
        goal.pose.pose.orientation.z = quaternion_z.value();
    }

    if (quaternion_w.has_value())
    {
        goal.pose.pose.orientation.w = quaternion_w.value();
    }
    else
    {
        goal.pose.pose.orientation.w = 1;
    }

    if (frame_id.has_value())
    {
        goal.pose.header.frame_id = frame_id.value();
    }
    else
    {
        goal.pose.header.frame_id = "map";
    }

    goal.pose.pose.position.x = x_input.value();
    goal.pose.pose.position.y = y_input.value();

    goal.pose.pose.position.z = 0; // z-value not neccessary
    goal.pose.header.stamp = get_node_handle()->now();

    log("Goal: (x=" + convert::ftos(goal.pose.pose.position.x) + ", y=" + convert::ftos(goal.pose.pose.position.y) + ")");
}

void BaseMovementNav2::on_feedback(const std::shared_ptr<const NavigateToPoseROS2Nav::Feedback>)
{
    // log("Current position: (x=" + convert::ftos((float)feedback->current_pose.pose.position.x) +
    //     ", y=" + convert::ftos((float)feedback->current_pose.pose.position.y) +
    //     "), Time elapsed: " + std::to_string(feedback->navigation_time.sec) + "s");
}

void BaseMovementNav2::on_result(const rclcpp_action::ClientGoalHandle<NavigateToPoseROS2Nav>::WrappedResult &, const NavigateToPoseROS2Nav::Goal &goal)
{
    log("Goal reached! (x=" + convert::ftos(goal.pose.pose.position.x) +
        ", y=" + convert::ftos(goal.pose.pose.position.y) +
        "), Total time: " + std::to_string((int)get_node_handle()->now().seconds() - goal.pose.header.stamp.sec) + "s");
}