#!/usr/bin/env python3
import random
import time

from mq import MessageQueue
from producer import Producer
from subscriber import Subscriber
from message import Message,TOPICS

p1 = Producer("p1")
p2 = Producer("p2")
s1 = Subscriber("s1")
s2 = Subscriber("s2")
msg1 = Message("m1", TOPICS.TOPIC1, "content1")
msg2 = Message("m2", TOPICS.TOPIC2, "content2")
msg3 = Message("m3", TOPICS.TOPIC2, "content3")
msg4 = Message("m4", TOPICS.TOPIC3, "content4")
msg5 = Message("m5", TOPICS.TOPIC4, "content5")

Producers = [p1, p2]
Subscribers = [s1, s2]
Messages = [msg1, msg2, msg3, msg4, msg5]

TopicVsSubscribersMap = {
    TOPICS.TOPIC1: [s1],
    TOPICS.TOPIC2: [s1, s2],
    TOPICS.TOPIC3: [s1, s2],
    TOPICS.TOPIC4: [s2],
}

class Driver:
    def __init__(self):
        return
    
    def Start(self):
        mq = MessageQueue("mq1", TopicVsSubscribersMap)
        while True:
            # randomly send messages from producers to subscribers
            n = random.randint(0, len(Messages))
            while n >= 0:
                n -= 1
                p = random.choice(Producers)
                m = random.choice(Messages)
                p.Send(mq, m)
            # randomly generate messages after every 10 seconds
            time.sleep(10)

if __name__ == "__main__":
    Driver().Start()