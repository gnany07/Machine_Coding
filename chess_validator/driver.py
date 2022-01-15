from game import ChessGame
from move import Move
from player import Player, User
from utils import COLOR

class Driver:
    def startGame(self):
        user1 = User("A", 1, "abc", 1, "a", "a", "a", "a", 1, "A", "AAA")
        user2 = User("B", 1, "abc", 1, "a", "a", "a", "a", 1, "B", "BBB")
        chess = ChessGame()
        player1 = Player(COLOR.WHITE, chess.getGameId(), user1.Username)
        player2 = Player(COLOR.BLACK, chess.getGameId(), user2.Username)
        player1.Turn = True
        player2.Turn = False
        chess.resetBoard()
        chess.displayBoard()
        moveobj = Move()
        while True:
            inputmove = input()
            inputmove.split(" ")
            moveobj.setStart(inputmove[0])
            moveobj.setEnd(inputmove[1])
            chess.addMoves(moveobj)
            if player1.Turn == True:
                if chess.isValidMove(moveobj, player1):
                    player1.Turn = False
                    player2.Turn = True
                    chess.makeMove(moveobj, player1)
                else:
                    print("Invalid Move\n")
            else:
                if chess.isValidMove(moveobj, player2):
                    player1.Turn = True 
                    player2.Turn = False 
                    chess.makeMove(moveobj, player2)
                else:
                    print("Invalid Move\n")
        return

if __name__ == "__main__":
    Driver().startGame()