cmake_minimum_required(VERSION 3.8)
project(drone_test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(px4_msgs REQUIRED)

add_executable(gps_bridge_node src/gps_bridge_node.cpp)
ament_target_dependencies(gps_bridge_node rclcpp std_msgs sensor_msgs px4_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS gps_bridge_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
