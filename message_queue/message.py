import enum

class TOPICS(enum.Enum):
    TOPIC1 = 0
    TOPIC2 = 1
    TOPIC3 = 2
    TOPIC4 = 3

class Message:
    def __init__(self, id, topic, content):
        self.Id = id
        self.Topic = topic 
        self.Content = content
        return