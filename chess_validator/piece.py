class Piece:
    def __init__(self, id, color):
        self.Id = id
        self.Color = color
        return
    
    def isValidMove(self, start, end):
        return
    
    def getId(self):
        return self.Id

class Pawn(Piece):
    def __init__(self, id, color):
        Piece.__init__(self, id, color)
        return
    
    def isValidMove(self, start, end):
        return

class Rook(Piece):
    def __init__(self, id, color):
        Piece.__init__(self, id, color)
        return
    
    def isValidMove(self, start, end):
        return

class Knight(Piece):
    def __init__(self, id, color):
        Piece.__init__(self, id, color)
        return
    
    def isValidMove(self, start, end):
        return

class Bishop(Piece):
    def __init__(self, id, color):
        Piece.__init__(self, id, color)
        return
    
    def isValidMove(self, start, end):
        return

class Queen(Piece):
    def __init__(self, id, color):
        Piece.__init__(self, id, color)
        return
    
    def isValidMove(self, start, end):
        return

class King(Piece):
    def __init__(self, id, color):
        Piece.__init__(self, id, color)
        return
    
    def isValidMove(self, start, end):
        return