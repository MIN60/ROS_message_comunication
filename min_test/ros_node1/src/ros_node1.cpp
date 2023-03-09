#include "ros/ros.h"
#include "message/Message0.h" //Node0으로부터 Message0 받아야 됨
#include "message/Message1.h" //Node2에게 Message1 보내야 됨
#include "message/Message3.h" //Node3으로부터 Message3 받아야됨

message::Message1 msg1;

class Node1{
    public: //main함수에서 접근할 수 있도록 접근지정자 public
        Node1(){
            //데이터 초기화
            msg1.from0 = 0;
            msg1.from3 = 0;

            //퍼블리셔 선언, ros_node1_pub을 작성한다.
            //토픽명은 ros_node1_msg이며, 퍼블리셔 큐 사이즈는 10이다.
            //정적 멤버 변수가 아니므로 ros:: 를 붙일 필요가 없다.
            ros_node1_pub = nh.advertise<message::Message1>("ros_node1_msg", 10);

            //서브스크라이버 선언, ros_node1_sub을 작성한다.
            //토픽명은 "ros_node0_msg"와 "ros_node3_msg" 이고 큐 사이즈는 10 이다.
            //호출되는 콜백 함수(Node1클래스의 멤버함수인 msgCallbackfrom0,3)에 대한 포인터 this
            //새로운 메시지가 수신될 때마다 콜백 함수들을 호출하도록 설정
            ros_node1_sub_from0 = nh.subscribe("ros_node0_msg", 10, &Node1::msgCallbackfrom0, this);
            ros_node1_sub_from3 = nh.subscribe("ros_node3_msg", 10, &Node1::msgCallbackfrom3, this);
        }

        void msgCallbackfrom0(const message::Message0::ConstPtr& msg){ //메세지 콜백함수
            //message패키지의 Message0 메세지를 받는다
            ROS_INFO("recieve msg0 seq = %d", msg->header.seq);
            ROS_INFO("recieve msg0 stamp = %d", msg->header.stamp);
            ROS_INFO("recieve msg0 frame_id = %s", msg->header.frame_id);
            ROS_INFO("recieve msg0 random = %d", msg->random);

            //다른 노드로 전달되는 헤더 필드를 보존
            //Message0의 데이터를 msg1로 복사
            msg1.header.seq = msg->header.seq;
            msg1.header.stamp = msg->header.stamp;
            msg1.header.frame_id = msg->header.frame_id;

            msg1.from0 = msg->random + 3;

            publish();
        }

        void msgCallbackfrom3(const message::Message3::ConstPtr& msg){
             //message패키지의 Message3 메세지를 받는다
            ROS_INFO("recieve msg3 seq = %d", msg->header.seq);
            ROS_INFO("recieve msg3 stamp = %d", msg->header.stamp);
            ROS_INFO("recieve msg3 frame_id = %s", msg->header.frame_id);
            ROS_INFO("recieve msg3 frandom2 = %lf", msg->frandom3);

            //다른 노드로 전달되는 헤더 필드를 보존
            //Message3의 데이터를 msg1로 복사
            msg1.header.seq = msg->header.seq;
            msg1.header.stamp = msg->header.stamp;
            msg1.header.frame_id = msg->header.frame_id;

            msg1.from3 = msg->frandom3 / 10;

            publish();
        }

        void publish(){
            ros::Rate loop_rate(10);

            msg1.random = 60;

             //메세지 표시
            ROS_INFO("msg1 send seq = %d", msg1.header.seq);
            ROS_INFO("msg1 send stamp = %d", msg1.header.stamp);
            ROS_INFO("msg1 send frame_id = %s", msg1.header.frame_id);
            ROS_INFO("msg1 send random = %d", msg1.random);
            ROS_INFO("msg1 send from0 = %d", msg1.from0);
            ROS_INFO("msg1 send from3 = %d", msg1.from3);

            //메세지 발행
            ros_node1_pub.publish(msg1);

            //루프 주기에 따라 슬립
            loop_rate.sleep();
        }

    private:
        ros::NodeHandle nh; //ROS 시스템과 통신을 위한 노드 핸들 선언
        ros::Publisher ros_node1_pub; //퍼블리셔 선언
        ros::Subscriber ros_node1_sub_from0; //서브 스크라이버 선언
        ros::Subscriber ros_node1_sub_from3; //서브 스크라이버 선언
};



int main(int argc, char **argv){
    ros::init(argc, argv, "ros_node1"); //노드명 초기화
    Node1 node1;

    //콜백함수 호출을 위한 함수로써 메세지가 수신되기를 기다렸다가 수신시 콜백함수를 실행
    ros::spin();

    return 0;
}
