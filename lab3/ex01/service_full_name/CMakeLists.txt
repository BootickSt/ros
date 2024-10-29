cmake_minimum_required(VERSION 3.5)
project(service_full_name)

# Используемые зависимости
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Указание интерфейсов сервиса
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/SummFullName.srv"
)

# Настройка сервиса
add_executable(service_name src/service_name.cpp)
ament_target_dependencies(service_name rclcpp)

# Настройка клиента
add_executable(client_name src/client_name.cpp)
ament_target_dependencies(client_name rclcpp)

# Получение целевого typesupport
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

# Подключение typesupport к исполняемым файлам
target_link_libraries(service_name ${cpp_typesupport_target})
target_link_libraries(client_name ${cpp_typesupport_target})

# Установка исполняемых файлов
install(TARGETS
  service_name
  client_name
  DESTINATION lib/${PROJECT_NAME}
)

# Финализация
ament_package()
