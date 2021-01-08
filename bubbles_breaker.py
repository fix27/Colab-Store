import sys
from copy import deepcopy
from threading import Timer

  

  
hard_bubble_board = (
           'pbgpbpyggrbpbgr',
           'bgyrbpprgyrgpbb',
           'bgyprypbpbbbrpb',
           'bpprpbpbgrrrgrr',
           'ppbrbpygpryryrb',
           'rgrgpbyyypggrbr',
           'gygrprrybbrrgrr',
           'rgpbpggrbypyryr',
           )
 
simple_bubble_board = (
                'rgrgpbyyypggrbr',
                'gygrprrybbrrgrr',
                'rgpbpggrbypyryr',
                )
 
X_VALUE = 5
SPACE_VALUE = 6
NUM_COLORS = 5
 
SOLVER_COUNT = 0
TOTAL_SOLVER_COUNT = 0
SOLVER_MEMOIZED = 0
USE_MEMOIZED = True
USE_PSYCO = sys.platform == 'win32'
STILL_SOLVING = True
MEMOIZATION = {'': {'t': 0}}



def PrintStats():
    global SOLVER_COUNT, TOTAL_SOLVER_COUNT, STILL_SOLVING
    TOTAL_SOLVER_COUNT += SOLVER_COUNT
    print ("TOTAL_SOLVER_COUNT:", TOTAL_SOLVER_COUNT, "SOLVER_COUNT PER 10s:", SOLVER_COUNT, "SOLVER_COUNT PER 1s:", SOLVER_COUNT / 10, "MEMOIZATION SIZE:", len(MEMOIZATION), "MEMOIZATION HIT:", SOLVER_MEMOIZED)
    SOLVER_COUNT = 0
    if STILL_SOLVING:
        Timer(10.0, PrintStats).start()
 




try:
    # Python 2
    xrange
except NameError:
    # Python 3, xrange is now named range
    xrange = range

conversion_c2i = {'p':0, 'b':1, 'g':2, 'y':3, 'r':4, 'x':X_VALUE, ' ':SPACE_VALUE}
conversion_i2c = ('p', 'b', 'g', 'y', 'r', 'x', ' ')
 
i2c_converter = lambda x: conversion_i2c[x]
identity_converter = lambda x: x
 
# convert to a faster underlying representation of the board
bubble_board = [[conversion_c2i[c] for c in row] for row in simple_bubble_board]
 
def compute_ball_adjacency(board, color, adjacency_table, adjacency_list, row_idx, col_idx):
    # Check the four bubbles adjacent for the same color value
    #          (x+0,y-1)
    # (x+1,y+0)(x+0,y+0)(x-1, y+0)
    #          (x+0,y+1)
    # plan: upgrade recursion to stack
 
    # Number of bubbles adjacent
    num_bubles_adjacent = 1
 
    # Check (x+1,y+0) .. first check whether we are in range
 
    r = row_idx
    c = col_idx + 1
    if c < len(board[0]):
        # if (0 or 1) that means we already figured out the ball count
        # Check whether we scored this one already
        if adjacency_table[r][c] == -1:
            # Make sure it is the same color
            if board[r][c] == color:
                # Same color update our score card
                adjacency_table[r][c] = 1
                adjacency_list.append((r, c))
                # go down the recursive path
                num_bubles_adjacent += compute_ball_adjacency(board, color, adjacency_table, adjacency_list, r, c)
            else:
                # We are not the same color so mark it as a 0
                adjacency_table[r][c] = 0
 
    # Check (x+0,y-1) .. first check whether we are in range
    c = col_idx - 1
    if c >= 0:
        # if (0 or 1) that means we already figured out the ball count
        # Check whether we scored this one already
        if adjacency_table[r][c] == -1:
            # Make sure it is the same color
            if board[r][c] == color:
                # Same color
                # update our score card
                adjacency_table[r][c] = 1
                adjacency_list.append((r, c))
                # go down the recursive path
                num_bubles_adjacent += compute_ball_adjacency(board, color, adjacency_table, adjacency_list, r, c)
            else:
                # We are not the same color so mark it as a 0
                adjacency_table[r][c] = 0
   
  
    # Check (x+0,y-1) .. first check whether we are in range
    r = row_idx - 1
    c = col_idx
    if r >= 0:
        # if (0 or 1) that means we already figured out the ball count
        # Check whether we scored this one already
        if adjacency_table[r][c] == -1:
            # Make sure it is the same color
            if board[r][c] == color:
                # Same color update our score card
                adjacency_table[r][c] = 1
                adjacency_list.append((r, c))
                # go down the recursive path
                num_bubles_adjacent += compute_ball_adjacency(board, color, adjacency_table, adjacency_list, r, c)
            else:
                # We are not the same color so mark it as a 0
                adjacency_table[r][c] = 0
 
   
    # Check (x+0,y+1) .. first check whether we are in range
    r = row_idx + 1
    if r < len(board):
        # if (0 or 1) that means we already figured out the ball count
        # Check whether we scored this one already
        if adjacency_table[r][c] == -1:
            # Make sure it is the same color
            if board[r][c] == color:
                # Same color
                # update our score card
                adjacency_table[r][c] = 1
                adjacency_list.append((r, c))
                # go down the recursive path
                num_bubles_adjacent += compute_ball_adjacency(board, color, adjacency_table, adjacency_list, r, c)
            else:
                # We are not the same color so mark it as a 0
                adjacency_table[r][c] = 0
    return num_bubles_adjacent
 
def print_board(board, msg, converter=i2c_converter):
    print (msg)
    print (' |' + ''.join(['%3d ' % i for i in xrange(len(board[0]))]))
    print (' +' + ('----' * (len(board[0]))))
    for row in xrange(len(board)):
        print (str(row) + '|')
        for col in xrange(len(board[0])):
             print('%3s ' % converter(board[row][col]))
        print
 
def mark_bubble_group(board, adj_count_list, row_idx, col_idx,
                      X_VALUE=X_VALUE):
    # Go through the adj_count_list and exchange all the bubbles with a count > 0 with Xs
    for row, col in adj_count_list:
        assert board[row][col] != X_VALUE
        # convert to an x
        board[row][col] = X_VALUE
 
def pick_bubble_group(bubbles_board, adj_count_list, row_idx, col_idx,
                      X_VALUE=X_VALUE, SPACE_VALUE=SPACE_VALUE, mark_bubble_group=mark_bubble_group):
 
    # Make a copy of our bubbles, we are going to return this reduced board
    board = [[c for c in r] for r in bubbles_board]
    #print_board(board, "Bubbles: Before Updating Board")
 
    # Go through the adj_count_list and exchange all the bubbles with a count > 0 with Xs
    mark_bubble_group(board, adj_count_list, row_idx, col_idx)
    #print_board(board, "Bubbles: After marking with Xs picking (row,col)=(%d,%d)" % (row_idx, col_idx))
    #print
 
    # Determine the rows with a bubble we are going to remove
    rows_with_x = []
    # Determine the columns with a bubble we are going to remove
    cols_with_x = []
 
    # keep track of the last row and last column
    first_row = 0
    first_col = 0
    last_row = adj_count_list[0][0]
    last_col = adj_count_list[0][1]
 
    for row, col in adj_count_list:
        if row > last_row:
            last_row = row
        if col > last_col:
            last_col = col
        if row < first_row:
            first_row = row
        if col < first_col:
            first_col = col
        if not row in rows_with_x:
            rows_with_x.append(row)
        if not col in cols_with_x:
            cols_with_x.append(col)
 
    # make some extra copies
    last_row_copy, first_row_copy, last_col_copy, first_col_copy = last_row, first_row, last_col, first_col
 
    ####################
    # Shift down phase
    ####################
 
    while 1:
        ## Now go through from the last row to the first column and move any balls down into X spaces
        found_x = False
 
        # Go through from the last row to the first row we know will have xs
        for row in xrange(last_row, first_row - 1, -1):
            for col in cols_with_x:
                if board[row][col] == X_VALUE:
                    found_x = True
                    # copy columns down: row-1..0
                    for row_copy in xrange(row, first_row, -1):
                        board[row_copy][col] = board[row_copy - 1][col]
 
                    # Clear top row
                    board[first_row][col] = SPACE_VALUE
 
        # We know the first row will not have xs anymore as we have shifted down
        first_row += 1
 
        if not found_x:
            break
 
    #print_board(board, "Bubbles: After shift down")
    #print
    ####################
    # Shift right phase
    ####################
    while 1:
        found_hole = False
        for row in xrange(last_row, -1, -1):
            for col in xrange(last_col, first_col - 1, -1):
                assert board[row][col] != X_VALUE
                # if we did not hit a space we can continue
                if board[row][col] != SPACE_VALUE:
                    continue
                # Search to the left to see if there are any columns that have a ball
                for col_search in xrange(col - 1, first_col - 1, -1):
                    if board[row][col_search] != SPACE_VALUE:
                        found_hole = True
                        # shift right from this point to the first column
                        for col_copy in xrange(col_search, -1, -1):
                            board[row][col + col_copy - col_search] = board[row][col_copy]
 
                        # Where we shifted we need to fill in with empty spaces
                        for col_fill in xrange(col - col_search - 1, -1, -1):
                            board[row][col_fill] = SPACE_VALUE
 
                        # end our search
                        break
        last_col -= 1
        first_col += 1
        if not found_hole:
            break
 
    #print_board(board, "Bubbles: After shift right")
    #print 'p',
 
    # Find any empty rows
    empty_row = -1
    for row in xrange(last_row_copy, -1, -1):
        for col in xrange(len(board[0])):
            if board[row][col] != SPACE_VALUE:
                break
        else:
            empty_row = row
            break
 
    # Find any empty columns
    empty_col = -1
    for col in xrange(last_col_copy, -1, -1):
        for row in xrange(len(board) - 1, -1, -1):
            if board[row][col] != SPACE_VALUE:
                break
        else:
            empty_col = col
            break
 
    #Prune our table of empty rows and columns
    for row in xrange(empty_row + 1):
        board.pop(0)
 
    for col in xrange(empty_col + 1):
        for row in xrange(len(board)):
            board[row].pop(0)
 
    #print_board(board, "Bubbles: After pruning")
    #print 'p',
 
    return board
 
def pick_color(color, color_map, color_list, SPACE_VALUE=SPACE_VALUE):
    # Space 'color' must always return as space
    if color == SPACE_VALUE:
        return ' '
 
    # Otherwise if we have not picked a color yet than we pop one of our list
    if color_map[color] is None:
        color_map[color] = color_list.pop()
    return color_map[color]
 
def normalized_hasher(board, NUM_COLORS=NUM_COLORS, pick_color=pick_color):
    """
   Since there are many combinations of boards that yield the same score we need to optimize the hasher to only
   store one version of the combinations. So we exchange the colors such that the colors are always ordered.
   The first ball(s) is color1, the second balls(s) is color2, etc..
   """
    color_map = [None] * NUM_COLORS
    color_list = ['p', 'b', 'g', 'y', 'r']
 
    # We add '|' as the salt between rows, so a board X x Y doesn't memoize as Y x X
    return '|'.join(''.join([pick_color(col_x, color_map, color_list) for col_x in rows]) for rows in board)
 
def print_solver_best(best):
 
    num_rows = best['r']
    num_cols = best['c']
 
    uncompressed_board = [[conversion_c2i[best['b'][row_x * num_cols + col_x]] for col_x in range(num_cols)] for row_x in range(num_rows)]
 
    print_board(uncompressed_board, "Bubbles: Best Pick(row,col) = (%(y)d, %(x)d) TotalScore = %(t)d PickScore = %(p)d" % best)
    if best['s']:
        print
        print_solver_best(best['s'])
 
def solver(board,
           conversion_i2c=conversion_i2c, normalized_hasher=normalized_hasher,
           USE_MEMOIZED=USE_MEMOIZED, MEMOIZATION=MEMOIZATION):
    global SOLVER_COUNT, SOLVER_MEMOIZED
 
    SOLVER_COUNT += 1
    if USE_MEMOIZED:
        hashed_board = normalized_hasher(board)
        has_best = MEMOIZATION.get(hashed_board, None)
 
        if has_best is not None:
            SOLVER_MEMOIZED += 1
            return has_best
 
    # best score for the current board
    # t = Total Score
    # p = The score for the picked bubble group
    # x = The column position of the picked bubble group
    # y = The row position of the picked bubble group
    # b = a compressed version of the board
    # r = number of rows in our board
    # c = number of columns in our board
    # s = solved board
    best = {'t': 0, 'p': 0, 'x': 0, 'y': 0, 's': None}
 
    # keep track of bubble groups we already picked so we don't go down that path again
    tried_board = [[c for c in row] for row in board]
 
    #print_board(board, "Bubbles: Before solver()")
    #score_card = [[0] * len(board[0]) for x in xrange(len(board))]
 
    for row_idx in xrange(len(board)):
        for col_idx in xrange(len(board[0])):
             # if we have already attempted this bubble group. Skip it or if empty space. Skip it
            if tried_board[row_idx][col_idx] == X_VALUE or board[row_idx][col_idx] == SPACE_VALUE:
                continue
            
            # Create a adjacency count table with x,y set as 1 all others as -1
            adj_count_table = [[-1] * len(board[0]) for x in xrange(len(board))]
            adj_count_table[row_idx][col_idx] = 1
            adj_count_list = [(row_idx, col_idx)]
            color = board[row_idx][col_idx]
 
            n = compute_ball_adjacency(board, color, adj_count_table, adj_count_list, row_idx, col_idx)
            score = n * (n - 1)
 
            #score_card[row_idx][col_idx] = score
            #print_board(adj_count_table, "Color: %s Score(%d,%d)=%d Adjacent Balls(%d,%d)=%d Adjacency Table:" % \
            #    (conversion_i2c[color], row_idx, col_idx, score, row_idx, col_idx, n),
            #    converter=identity_converter)
 
            if score > 0:
 
                # mark down in our tried board that we attempted this bubble group
                mark_bubble_group(tried_board, adj_count_list, row_idx, col_idx)
 
                solved = solver(pick_bubble_group(board, adj_count_list, row_idx, col_idx))
 
                # If picking this bubble group leads to no points
                if solved['t'] == 0 and score > best['t']:
                    # then our best score is just picking this bubble group
                    best['t'] = score
                    best['x'] = col_idx
                    best['y'] = row_idx
                    best['s'] = None
                    best['p'] = score
                    #best['a'] = tuple(adj_count_list)
 
                # If picking this bubble group leads to a score then add the bubble group score plus the solved board score
                if (solved['t'] + score) > best['t']:
                    # We found a better score
                    best['t'] = solved['t'] + score
                    best['x'] = col_idx
                    best['y'] = row_idx
                    best['s'] = solved
                    best['p'] = score
                    #best['a'] = tuple(adj_count_list)
 
    #print_board(score_card, "Score Card:", converter=identity_converter)
    #print 's',
    if USE_MEMOIZED:
        # Store board if
        if best['t'] > 0:
            best['b'] = ''.join(''.join([conversion_i2c[col_x] for col_x in row]) for row in board)
            best['r'] = len(board)
            best['c'] = len(board[0])
            MEMOIZATION[hashed_board] = best
    return best
 
if __name__ == '__main__':
    PrintStats()
    if USE_PSYCO:
        import psyco
        psyco.full()
    best = solver(bubble_board)
   
    print_solver_best(best)
    global STILL_SOLVING
    STILL_SOLVING = False
