#include "ros/ros.h"
#include "message/Message2.h" //Node2으로부터 Message2 받아야 됨
#include "message/Message3.h" //Node3,4,5 Message3

message::Message3 msg5;

class Node5{
    public: //main함수에서 접근할 수 있도록 접근지정자 public
        Node5(){
            //데이터 초기화
            msg5.frandom3 = 0;

            //퍼블리셔 선언, ros_node5_pub을 작성한다.
            //토픽명은 ros_node5_msg이며, 퍼블리셔 큐 사이즈는 10이다.
            //정적 멤버 변수가 아니므로 ros:: 를 붙일 필요가 없다.
            ros_node5_pub = nh.advertise<message::Message3>("ros_node5_msg", 10);

            //서브스크라이버 선언, ros_node4_sub을 작성한다.
            //토픽명은 "ros_node2_msg"이고 큐 사이즈는 10 이다.
            ros_node5_sub_from2 = nh.subscribe("ros_node2_msg", 10, &Node5::msgCallbackfrom2, this);
        }

        void msgCallbackfrom2(const message::Message2::ConstPtr& msg){ //메세지 콜백함수
            //message패키지의 Message0 메세지를 받는다
            ROS_INFO("recieve msg2 seq = %d", msg->header.seq);
            ROS_INFO("recieve msg2 stamp = %d", msg->header.stamp);
            ROS_INFO("recieve msg2 frame_id = %s", msg->header.frame_id);
            ROS_INFO("recieve msg2 frandom2 = %lf", msg->frandom2);

            //다른 노드로 전달되는 헤더 필드를 보존
            //Message2의 데이터를 msg5로 복사
            msg5.header.seq = msg->header.seq;
            msg5.header.stamp = msg->header.stamp;
            msg5.header.frame_id = msg->header.frame_id;

            msg5.frandom3 = msg->frandom2 * 1000;

            publish();
        }

        void publish(){
            ros::Rate loop_rate(10);

             //메세지 표시
            ROS_INFO("msg5 send seq = %d", msg5.header.seq);
            ROS_INFO("msg5 send stamp = %d", msg5.header.stamp);
            ROS_INFO("msg5 send frame_id = %s", msg5.header.frame_id);
            ROS_INFO("msg5 send frandom3 = %lf", msg5.frandom3);

            //메세지 발행
            ros_node5_pub.publish(msg5);

            //루프 주기에 따라 슬립
            loop_rate.sleep();
        }

    private:
        ros::NodeHandle nh; //ROS 시스템과 통신을 위한 노드 핸들 선언
        ros::Publisher ros_node5_pub; //퍼블리셔 선언
        ros::Subscriber ros_node5_sub_from2; //서브 스크라이버 선언
};



int main(int argc, char **argv){
    ros::init(argc, argv, "ros_node5"); //노드명 초기화
    Node5 node5;

    //콜백함수 호출을 위한 함수로써 메세지가 수신되기를 기다렸다가 수신시 콜백함수를 실행
    ros::spin();

    return 0;
}
