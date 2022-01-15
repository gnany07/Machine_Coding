class Subscriber:
    def __init__(self, id):
        self.Id = id
        return
    
    def Receive(self, msg):
        print(f"Message Received at subscriber {self.Id}")
        print(f" Id:{msg.Id}")
        print(f" Topic:{msg.Topic}")
        print(f" Content:{msg.Content}")
        return