class Producer:
    def __init__(self, id):
        self.Id = id
        return
    
    def Send(self, mq, msg):
        print(f"Message Send at producer {self.Id}")
        print(f" Id:{msg.Id}")
        print(f" Topic:{msg.Topic}")
        print(f" Content:{msg.Content}")
        mq.Receive(msg)
        return