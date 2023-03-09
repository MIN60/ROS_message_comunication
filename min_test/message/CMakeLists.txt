# 최소 CMake 버전 요구사항
cmake_minimum_required(VERSION 3.0.2)
# 현재 패키지명
project(message)

# catkin을 빌드할 때 필요한 구성 요소 패키지로 사용자가 입력한 의존성 패키지 작성
# message_generation을 추가
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
# 메세지 생성자
# 주석을 풀고 message0~3까지 추가
add_message_files(
  FILES
  Message0.msg
  Message1.msg
  Message2.msg
  Message3.msg
)


## Generate added messages and services with any dependencies listed here
# 메세지/서비스/액션 생성 실행
# 패키지에 서비스/메세지/액션이 있는 경우 주석을 풀어줌 
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES message
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime message_generation
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


