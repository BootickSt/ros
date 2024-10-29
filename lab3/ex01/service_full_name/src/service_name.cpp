#include "rclcpp/rclcpp.hpp"
#include "service_full_name/srv/summ_full_name.hpp" // Замените на ваш правильный путь к файлу

using std::placeholders::_1;
using std::placeholders::_2;

class FullNameService : public rclcpp::Node {
public:
    FullNameService() : Node("service_name") {
        // Инициализация сервиса
        service_ = this->create_service<service_full_name::srv::SummFullName>(
            "SummFullName",
            std::bind(&FullNameService::handle_service, this, _1, _2)
        );
        RCLCPP_INFO(this->get_logger(), "Service 'SummFullName' ready.");
    }

private:
    void handle_service(
        const std::shared_ptr<service_full_name::srv::SummFullName::Request> request,
        std::shared_ptr<service_full_name::srv::SummFullName::Response> response
    ) {
        // Склеивание имени, отчества и фамилии
        response->full_name = request->first_name + " " + request->middle_name + " " + request->last_name;
        RCLCPP_INFO(this->get_logger(), "Request received: %s %s %s", 
                    request->first_name.c_str(), request->middle_name.c_str(), request->last_name.c_str());
        RCLCPP_INFO(this->get_logger(), "Response sent: %s", response->full_name.c_str());
    }

    rclcpp::Service<service_full_name::srv::SummFullName>::SharedPtr service_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<FullNameService>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
