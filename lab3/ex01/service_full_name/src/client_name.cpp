#include "rclcpp/rclcpp.hpp"
#include "service_full_name/srv/summ_full_name.hpp"
#include <memory>
#include <iostream>

using SummFullName = service_full_name::srv::SummFullName;

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  if (argc != 4) {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Usage: client_name <last_name> <first_name> <patronymic>");
    return 1;
  }

  auto node = rclcpp::Node::make_shared("client_name");
  auto client = node->create_client<SummFullName>("SummFullName");

  while (!client->wait_for_service(std::chrono::seconds(1))) {
    RCLCPP_INFO(node->get_logger(), "Waiting for service to appear...");
  }

  auto request = std::make_shared<SummFullName::Request>();
request->first_name = argv[1];
request->middle_name = argv[2];  
request->last_name = argv[3];

  auto result = client->async_send_request(request);

  if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(node->get_logger(), "Full name: %s", result.get()->full_name.c_str());
  } else {
    RCLCPP_ERROR(node->get_logger(), "Failed to call service SummFullName");
  }

  rclcpp::shutdown();
  return 0;
}
