import threading
import time

class MessageQueue:
    def __init__(self, id, topic_subscibers_map):
        self.Id = id
        self.TopicVsSubscribers = topic_subscibers_map
        self.Queue = []
        # creating a lock
        self.lock = threading.Lock()
        self.main_thread=threading.Thread(target=self.HandleMessages,args=[])
        self.main_thread.start()
        return

    def Receive(self, msg):
        self.Queue.append(msg)
        return

    def Send(self, msg):
        topic = msg.Topic
        subscribers_list = self.TopicVsSubscribers[topic]
        for sub in subscribers_list:
            sub.Receive(msg)
        return


    def HandleMessages(self):
        """
        handle received messages
        """
        def thread_task(self, lock, id):
            """
            task for thread
            send the messages to subscribers
            """ 
            lock.acquire()
            if len(self.Queue) > id:
                self.Send(self.Queue[id])
                self.Queue.pop(id)
            lock.release()
            return

        while True:
            while len(self.Queue):
                threads=[]
                # create multiple threads
                for i in range(0, 100):
                    thread=threading.Thread(target=thread_task,args=[self.lock, i])
                    # start multiple threads to handle messages
                    thread.start()
                    threads.append(thread)
                for thread in threads:
                    # wait for threads to finish
                    thread.join()
            # check for new messages after every 5 seconds
            time.sleep(5)
        return