from position import Position

class Move:
    def __init__(self):
        self.Start = Position()
        self.End = Position() 
        return

    def getStart(self):
        return self.Start
    
    def setStart(self, start):
        self.Start.X = '8' - start[1]
        self.Start.Y = start[0] - 'a'
        return
    
    def getEnd(self):
        return self.End

    def setEnd(self, end):
        self.End.X = '8' - end[1]
        self.End.Y = end[0] - 'a'
        return