cmake_minimum_required(VERSION 3.0.2)
# 현재 패키지명
project(ros_node0)

# catkin을 빌드할 때 필요한 구성 요소 패키지로 사용자가 입력한 의존성 패키지 작성
# message_generation을 추가하고 message 패키지 안에 있는 파일을 이용해야 하므로 message 추
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  message
)

# 메세지/서비스/액션 생성 실행
# 패키지에 서비스/메세지/액션이 있는 경우 주석을 풀어줌 
generate_messages(
  DEPENDENCIES
  std_msgs
)

# 패키지 빌드 정보
# LIBRARIES(설정 패키지의 라이브러리 사용)
# CATKIN_DEPENDS의 주석을 풀고 CATKIN_DEPENDS(의존하는 패키지)에 message_runtime, message 추가
catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES ros_node0
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime message
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

# C++ 사용 시 실행 가능한 노드 추가
# 실행시킬 노드의 이름과 진짜 파일 이름 입력
add_executable(ros_node0 src/ros_node0.cpp)

# C++사용시 주석 해제
add_dependencies(ros_node0 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# C++ 사용 시 주석 해제, 노드명 작성
target_link_libraries(ros_node0
  ${catkin_LIBRARIES}
)


# 파이썬 사용을 위해 주석을 풀어주고 파일명을 작성한다.
catkin_install_python(PROGRAMS
  src/ros_node0.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

