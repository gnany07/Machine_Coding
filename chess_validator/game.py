import logging
import random
import pdb

from player import Player
from cell import Cell
from piece import Pawn, Rook, Knight, Bishop, Queen, King
from utils import BOARD_SIZE, COLOR, INVALID_MOVES_STR 

class ChessGame:
    def __init__(self):
        self.Board = [[None] * BOARD_SIZE]*BOARD_SIZE 
        for i in range(BOARD_SIZE):
            for j in range(BOARD_SIZE):
                self.Board[i][j] = Cell()
        pdb.set_trace()
        self.GameId = random.randint(0, 10000)
        self.Moves = []
        logging.basicConfig(filename="invalid_moves.log",
                    format='%(asctime)s %(message)s',
                    filemode='w')
        self.logger = logging.getLogger()
        self.logger.setLevel(logging.DEBUG)
        return

    def getGameId(self):
        return self.GameId

    def resetBoard(self):
        '''
            BR BN BB BQ BK BB BN BR
            BP BP BP BP BP BP BP BP
            -- -- -- -- -- -- -- --
            -- -- -- -- -- -- -- --
            -- -- -- -- -- -- -- --
            -- -- -- -- -- -- -- --
            WP WP WP WP WP WP WP WP
            WR WN WB WQ WK WB WN WR
            '''
        # initialize black pieces
        br1 = Rook("BR", COLOR.BLACK)
        bn1 = Knight("BN", COLOR.BLACK)
        bb1 = Bishop("BB", COLOR.BLACK)
        bq1 = Queen("BQ", COLOR.BLACK)
        bk1 = King("BK", COLOR.BLACK)
        bb2 = Bishop("BB", COLOR.BLACK)
        bn2 = Knight("BN", COLOR.BLACK)
        br2 = Rook("BR", COLOR.BLACK)
        bp1 = Pawn("BP", COLOR.BLACK)
        bp2 = Pawn("BP", COLOR.BLACK)
        bp3 = Pawn("BP", COLOR.BLACK)
        bp4 = Pawn("BP", COLOR.BLACK)
        bp5 = Pawn("BP", COLOR.BLACK)
        bp6 = Pawn("BP", COLOR.BLACK)
        bp7 = Pawn("BP", COLOR.BLACK)
        bp8 = Pawn("BP", COLOR.BLACK)

        self.Board[0][0].setPiece(br1)
        self.Board[0][1].setPiece(bn1)
        self.Board[0][2].setPiece(bb1)
        self.Board[0][3].setPiece(bq1)
        self.Board[0][4].setPiece(bk1)
        self.Board[0][5].setPiece(bb2)
        self.Board[0][6].setPiece(bn2)
        self.Board[0][7].setPiece(br2)
        self.Board[1][0].setPiece(bp1)
        self.Board[1][1].setPiece(bp2)
        self.Board[1][2].setPiece(bp3)
        self.Board[1][3].setPiece(bp4)
        self.Board[1][4].setPiece(bp5)
        self.Board[1][5].setPiece(bp6)
        self.Board[1][6].setPiece(bp7)
        self.Board[1][7].setPiece(bp8)

        # initialize white pieces
        wr1 = Rook("WR", COLOR.WHITE)
        wn1 = Knight("WN", COLOR.WHITE)
        wb1 = Bishop("WB", COLOR.WHITE)
        wq1 = Queen("WQ", COLOR.WHITE)
        wk1 = King("WK", COLOR.WHITE)
        wb2 = Bishop("WB", COLOR.WHITE)
        wn2 = Knight("WN", COLOR.WHITE)
        wr2 = Rook("WR", COLOR.WHITE)
        wp1 = Pawn("WP", COLOR.WHITE)
        wp2 = Pawn("WP", COLOR.WHITE)
        wp3 = Pawn("WP", COLOR.WHITE)
        wp4 = Pawn("WP", COLOR.WHITE)
        wp5 = Pawn("WP", COLOR.WHITE)
        wp6 = Pawn("WP", COLOR.WHITE)
        wp7 = Pawn("WP", COLOR.WHITE)
        wp8 = Pawn("WP", COLOR.WHITE)

        self.Board[7][0].setPiece(wr1)
        self.Board[7][1].setPiece(wn1)
        self.Board[7][2].setPiece(wb1)
        self.Board[7][3].setPiece(wq1)
        self.Board[7][4].setPiece(wk1)
        self.Board[7][5].setPiece(wb2)
        self.Board[7][6].setPiece(wn2)
        self.Board[7][7].setPiece(wr2)
        self.Board[6][0].setPiece(wp1)
        self.Board[6][1].setPiece(wp2)
        self.Board[6][2].setPiece(wp3)
        self.Board[6][3].setPiece(wp4)
        self.Board[6][4].setPiece(wp5)
        self.Board[6][5].setPiece(wp6)
        self.Board[6][6].setPiece(wp7)
        self.Board[6][7].setPiece(wp8)

        # initialize rest of cells to empty pieces
        '''
        for i in range(2, 6):
            for j in range(BOARD_SIZE):
                self.Board[i][j].setPiece(None)
        '''
        pdb.set_trace()
        return
    
    def isValidMove(self, move, player):
        if not move.Start.isValid():
            self.logger.error(INVALID_MOVES_STR.INVALID_START_POS.value)
            return False
        if not move.End.isValid():
            self.logger.error(INVALID_MOVES_STR.INVALID_END_POS.value)
            return False
        piece = self.Board[move.Start.X][move.Start.Y].getPiece()
        if piece == None:
            self.logger.error(INVALID_MOVES_STR.EMPTY_PIECE_AT_THE_START.value)
            return False
        if piece.Color != player.Color:
            self.logger.error(INVALID_MOVES_STR.EMPTY_PIECE_AT_THE_START.value)
            return False
        if piece.isValidMove() == False:
            self.logger.error(INVALID_MOVES_STR.INVALID_MOVE.value)
            return False
        return True

    def makeMove(self, move, player):
        start_cell = self.Board[move.Start.X][move.Start.Y]
        end_cell = self.Board[move.End.X][move.End.Y]
        # move piece at start_cell to end_cell
        end_cell.setPiece(start_cell.getPiece())
        # empty start_cell
        start_cell.setPiece(None)
        return

    def displayBoard(self):
        for i in range(BOARD_SIZE):
            for j in range(BOARD_SIZE):
                if self.Board[i][j].isEmpty() == True:
                    print("--")
                else:
                    pdb.set_trace()
                    print(self.Board[i][j].getPiece().getId())
                print(" ")
            print("\n")
        return

    def addMoves(self, move):
        self.Moves.append(move)
        return