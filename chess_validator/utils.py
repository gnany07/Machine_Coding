import enum

BOARD_SIZE = 8

class COLOR(enum.Enum):
    WHITE = 0
    BLACK = 1

class INVALID_MOVES_STR(str, enum.Enum):
    EMPTY_PIECE_AT_THE_START = "Empty piece at the start"
    PIECE_AND_PLAYER_COLOR_MISMATCH = "Piece and player color mismatched"
    INVALID_MOVE = "Invalid move"
    INVALID_START_POS = "Invalid start position"
    INVALID_END_POS = "Invalid end position"