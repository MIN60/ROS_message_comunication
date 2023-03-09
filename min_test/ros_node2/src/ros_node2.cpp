#include "ros/ros.h"
#include "message/Message1.h" //Node1으로부터 Message1 받아야 됨
#include "message/Message2.h" //Node3,4,5에게 Message2 보내야 됨

message::Message2 msg2;

class Node2{
    public: //main함수에서 접근할 수 있도록 접근지정자 public
        Node2(){
            //데이터 초기화
            msg2.frandom2 = 0;

            //퍼블리셔 선언, ros_node2_pub을 작성한다.
            //토픽명은 ros_node2_msg이며, 퍼블리셔 큐 사이즈는 10이다.
            //정적 멤버 변수가 아니므로 ros:: 를 붙일 필요가 없다.
            ros_node2_pub = nh.advertise<message::Message2>("ros_node2_msg", 10);

            //서브스크라이버 선언, ros_node2_sub을 작성한다.
            //토픽명은 "ros_node1_msg"이고 큐 사이즈는 10 이다.
            ros_node2_sub_from1 = nh.subscribe("ros_node1_msg", 10, &Node2::msgCallbackfrom1, this);
        }

        void msgCallbackfrom1(const message::Message1::ConstPtr& msg){ //메세지 콜백함수
            //message패키지의 Message0 메세지를 받는다
            ROS_INFO("recieve msg1 seq = %d", msg->header.seq);
            ROS_INFO("recieve msg1 stamp = %d", msg->header.stamp);
            ROS_INFO("recieve msg1 frame_id = %s", msg->header.frame_id);
            ROS_INFO("recieve msg1 from0 = %d", msg->from0);

            //다른 노드로 전달되는 헤더 필드를 보존
            //Message1의 데이터를 msg2로 복사
            msg2.header.seq = msg->header.seq;
            msg2.header.stamp = msg->header.stamp;
            msg2.header.frame_id = msg->header.frame_id;

            msg2.frandom2 = msg->from0 * 0.1;

            publish();
        }

        void publish(){
            ros::Rate loop_rate(10);

             //메세지 표시
            ROS_INFO("msg2 send seq = %d", msg2.header.seq);
            ROS_INFO("msg2 send stamp = %d", msg2.header.stamp);
            ROS_INFO("msg2 send frame_id = %s", msg2.header.frame_id);
            ROS_INFO("msg2 send frandom2 = %lf", msg2.frandom2);

            //메세지 발행
            ros_node2_pub.publish(msg2);

            //루프 주기에 따라 슬립
            loop_rate.sleep();
        }

    private:
        ros::NodeHandle nh; //ROS 시스템과 통신을 위한 노드 핸들 선언
        ros::Publisher ros_node2_pub; //퍼블리셔 선언
        ros::Subscriber ros_node2_sub_from1; //서브 스크라이버 선언
};



int main(int argc, char **argv){
    ros::init(argc, argv, "ros_node2"); //노드명 초기화
    Node2 node2;

    //콜백함수 호출을 위한 함수로써 메세지가 수신되기를 기다렸다가 수신시 콜백함수를 실행
    ros::spin();

    return 0;
}
