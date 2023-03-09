#include "ros/ros.h" //ROS 기본 헤더파일
#include "message/Message0.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "ros_node0"); //노드명 초기화
    ros::NodeHandle nh; //ROS 시스템과 통신을 위한 노드 핸들 선언

    //퍼블리셔 선언, 퍼블리셔 ros_node0_publisher를 작성한다.
    //토픽명은 ros_node0_msg이며, 퍼블리셔 큐 사이즈는 10이다.
    ros::Publisher ros_node0_pub = nh.advertise<message::Message0>("ros_node0_msg", 10);

    //루프 주기를 10(1초에 10번)으로 설정
    ros::Rate loop_rate(10);

    message::Message0 msg; //message 메세지 파일 형식으로 msg라는 메세지를 선언
    int count = 0; //메세지에 사용될 변수 선언

    while(ros::ok()){
        msg.header.seq= count; //count라는 변수 값을 msg의 하위 seq 메세지에 담는다
        msg.header.stamp = ros::Time::now(); //현재 시간을 msg의 하위 stamp메세지에 담는다
        msg.header.frame_id = "frame_id"; //frame_id를 msg의 하위 frame_id에 담는다
        msg.random = 16; // 16을 msg 하위 random에 담는다

        //메세지 표시
        ROS_INFO("send msg seq = %d", msg.header.seq);
        ROS_INFO("send msg stamp = %d", msg.header.stamp);
        ROS_INFO("send msg frame_id = %s", msg.header.frame_id);
        ROS_INFO("send msg random = %d", msg.random);

        ros_node0_pub.publish(msg); //메세지 발행

        loop_rate.sleep(); //루프 주기에 따라 슬립

        ++count; //count 변수 1씩 증가

    }

     return 0;

}
