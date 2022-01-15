import pdb

from piece import Piece

class Cell:
    def __init__(self, id=None, color=None, piece_obj=None):
        self.Id = id
        self.Color = color
        self.PieceObj = piece_obj 
        return
    
    def isEmpty(self):
        pdb.set_trace()
        return True if not self.PieceObj else False

    def getPiece(self):
        return self.PieceObj

    def setPiece(self, piece_obj):
        self.PieceObj = piece_obj
        return