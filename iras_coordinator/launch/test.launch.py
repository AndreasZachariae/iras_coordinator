import launch.substitutions
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import LogInfo


def generate_launch_description():

    emit_shutdown_action = launch.actions.Shutdown(
        reason='launch is shutting down')

    return LaunchDescription([
        Node(
            package='iras_coordinator',
            executable='Coordinator',
            # name='Coordinator',
            output='screen',
            parameters=[
                {'main_tree_path': "/home/docker/ros2_ws/src/iras_coordinator/behaviors/tests/TestCmdVelAction.xml"}],
            on_exit=[LogInfo(
                msg=["Coordinator has stopped. Stopping everything..."]), emit_shutdown_action],
        )
    ])