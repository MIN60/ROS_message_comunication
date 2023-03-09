#!/usr/bin/env python

import rospy
from message.msg import Message0

def main():
    # 노드명 초기화
    rospy.init_node("ros_node0")
    # ROS 시스템과 통신을 위한 노드 핸들 선언
    nh = rospy.NodeHandle()
    # 토픽명은 ros_node0_msg이며, 퍼블리셔 큐 사이즈는 10이다.
    ros_node0_pub = rospy.Publisher("ros_node0_msg", Message0, queue_size=10)
    # 루프 주기를 10(1초에 10번)으로 설정
    loop_rate = rospy.Rate(10)

    # message 메세지 파일 형식으로 msg라는 메세지를 선언
    msg = Message0()
    # 메세지에 사용될 변수 선언
    count = 0

    while not rospy.is_shutdown():
        # count라는 변수 값을 msg의 하위 seq 메세지에 담는다
        msg.header.seq = count
        # 현재 시간을 msg의 하위 stamp메세지에 담는다
        msg.header.stamp = rospy.Time.now()
        # frame_id를 msg의 하위 frame_id에 담는다
        msg.header.frame_id = "frame_id"
        # 16을 msg 하위 random에 담는다
        msg.random = 16

        # 메세지 표시
        rospy.loginfo("send msg seq = %d", msg.header.seq)
        rospy.loginfo("send msg stamp = %d", msg.header.stamp)
        rospy.loginfo("send msg frame_id = %s", msg.header.frame_id)
        rospy.loginfo("send msg random = %d", msg.random)

        # 메세지 발행
        ros_node0_pub.publish(msg)

        # 루프 주기에 따라 슬립
        loop_rate.sleep()

        # count 변수 1씩 증가
        count += 1

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
