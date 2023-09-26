#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2019 C

bool whiteStart;
vector<bool> isCapture;
vector<vector<int>> moves;

vector<pair<int, int>> blackMoves; //from each position, what are the valid black moves?
vector<pair<int, int>> whiteMoves; //from each position, ...

vector<vector<vector<vector<pair<int, int>>>>> possibleMoves;   //all possible moves from every location. 

vector<pair<int, int>> generatePossibleMoves(int pos, char piece);

void initMoves() {
    blackMoves = vector<pair<int, int>>(32, {-1, -1});
    whiteMoves = vector<pair<int, int>>(32, {-1, -1});

    vector<vector<int>> board(8, vector<int>(8, -1));
    {
        int ptr = 0;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if((i + j) % 2 == 1){
                    board[i][j] = ptr ++;
                }
            }
        }
    }

    //find all moves
    {
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j] == -1){
                    continue;
                }
                //black moves 
                if(i != 7){
                    //to the left
                    if(j != 0){
                        blackMoves[board[i][j]].first = board[i + 1][j - 1];
                    }
                    //to the right
                    if(j != 7){
                        blackMoves[board[i][j]].second = board[i + 1][j + 1];
                    }
                }
                //white moves
                if(i != 0){
                    //to the left
                    if(j != 0){
                        whiteMoves[board[i][j]].first = board[i - 1][j - 1];
                    }
                    //to the right
                    if(j != 7) {
                        whiteMoves[board[i][j]].second = board[i - 1][j + 1];
                    }
                }
            }
        }
    }

    possibleMoves = vector<vector<vector<vector<pair<int, int>>>>>(32, vector<vector<vector<pair<int, int>>>>(2, vector<vector<pair<int, int>>>(2)));
    //isWhite, isKing
    for(int i = 0; i < 32; i++){
        possibleMoves[i][0][0] = (generatePossibleMoves(i, 'b'));
        possibleMoves[i][1][0] = (generatePossibleMoves(i, 'w'));
        possibleMoves[i][0][1] = (generatePossibleMoves(i, 'B'));
        possibleMoves[i][1][1] = (generatePossibleMoves(i, 'W'));
    }
}

int leftMove(int pos, bool isWhite) {
    return isWhite? whiteMoves[pos].first : blackMoves[pos].first;
}

int rightMove(int pos, bool isWhite) {
    return isWhite? whiteMoves[pos].second : blackMoves[pos].second;
}

int move(int pos, bool isWhite, bool isLeft) {
    return isLeft? leftMove(pos, isWhite) : rightMove(pos, isWhite);
}

//returns the position after doing a capture jump. 
int capture(int pos, bool isWhite, bool isLeft) {
    int movePos = move(pos, isWhite, isLeft);
    return movePos == -1? -1 : move(movePos, isWhite, isLeft);
}

bool isWhiteMove(int from, int to) {
    return whiteMoves[from].first == to || whiteMoves[from].second == to;
}

bool isWhiteCapture(int from, int to) {
    if(whiteMoves[from].first != -1 && whiteMoves[whiteMoves[from].first].first == to){
        return true;
    }
    if(whiteMoves[from].second != -1 && whiteMoves[whiteMoves[from].second].second == to){
        return true;
    }
    return false;
}

bool isLeftMove(int from, int to) {
    return whiteMoves[from].first == to || blackMoves[from].first == to;
}

bool isLeftCapture(int from, int to) {
    if(whiteMoves[from].first != -1 && whiteMoves[whiteMoves[from].first].first == to){
        return true;
    }
    if(blackMoves[from].first != -1 && blackMoves[blackMoves[from].first].first == to){
        return true;
    }
    return false;
}

bool isWhitePiece(char piece) {
    return piece == 'w' || piece == 'W';
}

bool isBlackPiece(char piece) {
    return piece == 'b' || piece == 'B';
}

bool isKing(char piece) {
    return piece == 'W' || piece == 'B';
}

bool shouldPromote(int pos, char piece) {
    if(piece == 'w' && pos <= 3) {
        return true;
    }
    if(piece == 'b' && pos >= 28) {
        return true;
    }
    return false;
}

char promote(char piece) {
    return piece == 'b'? 'B' : 'W';
}

vector<pair<int, int>> generatePossibleMoves(int pos, char piece) {
    vector<pair<int, int>> ans(0);
    ans.push_back({move(pos, isWhitePiece(piece), true), capture(pos, isWhitePiece(piece), true)});
    ans.push_back({move(pos, isWhitePiece(piece), false), capture(pos, isWhitePiece(piece), false)});
    if(isKing(piece)) {
        ans.push_back({move(pos, !isWhitePiece(piece), true), capture(pos, !isWhitePiece(piece), true)});
        ans.push_back({move(pos, !isWhitePiece(piece), false), capture(pos, !isWhitePiece(piece), false)});
    }
    return ans;
}

vector<string> boardToStrings(vector<char> board) {
    vector<string> ans(8, string(8, ' '));
    int ptr = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((i + j) % 2 == 0){
                ans[i][j] = '-';
            }
            else {
                ans[i][j] = board[ptr ++];
            }
        }
    }
    return ans;
}

void printBoard(vector<char> board) {
    vector<string> sarr = boardToStrings(board);
    for(int i = 0; i < 8; i++){
        cout << sarr[i] << "\n";
    }
}

bool solve(vector<char>& startPos) {
    //cout << "SOLVING : " << "\n";
    //printBoard(startPos);
    //check for invalid placements of men
    for(int i = 0; i < 32; i++){
        if(shouldPromote(i, startPos[i])) {
            startPos[i] = promote(startPos[i]);
        }
    }
    vector<pair<char, int>> curPos(32, {'.', -1});  //piece type, start position. 
    while(true) {
        //cout << "ITERATE : " << "\n";
        //printBoard(startPos);
        bool inconsistencyFound = false;
        for(int i = 0; i < 32; i++){
            if(startPos[i] != '.') {
                curPos[i] = {startPos[i], i};
            }
            else {
                curPos[i] = {'.', -1};
            }
        }
        bool whiteMove = whiteStart;
        //play through all the moves and check for inconsistencies. 
        for(int i = 0; i < moves.size(); i++){
            //cout << "CHECKING MOVE : " << i << "\n";
            //first, make sure that there is some sort of piece to move. 
            if(curPos[moves[i][0]].first == '.') {
                //add the piece in, and try again. 
                startPos[moves[i][0]] = whiteMove? 'w' : 'b';
                inconsistencyFound = true;
                break;
            }
            //make sure that the piece we are moving is on the correct team
            if(isWhitePiece(curPos[moves[i][0]].first) != whiteMove) {
                //this won't work
                return false;
            }
            //next, make sure that the all of the squares we move to are empty. 
            //if we go on a long chain capture, then it is possible to move back to the same square
            //we started on. 
            for(int j = 1; j < moves[i].size(); j++){
                if(moves[i][j] == moves[i][0]) {
                    //this might be possible. 
                    continue;
                }
                if(curPos[moves[i][j]].first != '.') {
                    //found a not empty position. Try again
                    return false;
                }
            }
            if(!isCapture[i]) {
                //cout << "NOT A CAPTURE\n";
                int from = moves[i][0];
                int to = moves[i][1];
                //check if we should turn this piece into a king. 
                if(!isKing(curPos[from].first) && (whiteMove ^ isWhiteMove(from, to))) {
                    startPos[curPos[from].second] = whiteMove? 'W' : 'B';
                    inconsistencyFound = true;
                    break;
                }
                //check if there are any forced captures that we should block. 
                {
                    int blockerPos = -1;
                    for(int j = 0; j < 32; j++){
                        if(curPos[j].first == '.' || (whiteMove && isBlackPiece(curPos[j].first)) || (!whiteMove && isWhitePiece(curPos[j].first))) {
                            //wrong team
                            continue;
                        }
                        bool isWhite = whiteMove;
                        bool is_King = isKing(curPos[j].first);
                        for(int k = 0; k < possibleMoves[j][isWhite][is_King].size(); k++){
                            int movePos = possibleMoves[j][isWhite][is_King][k].first;
                            int capturePos = possibleMoves[j][isWhite][is_King][k].second;
                            if(curPos[movePos].first == '.' || curPos[capturePos].first != '.') {
                                continue;
                            }
                            if(isWhitePiece(curPos[movePos].first) == whiteMove) {
                                continue;
                            }
                            //this is a possible capture
                            blockerPos = capturePos;
                            break;
                        }
                        if(blockerPos != -1){
                            break;
                        }
                    }
                    if(blockerPos != -1){
                        //try white
                        {
                            vector<char> nextStartPos = startPos;
                            nextStartPos[blockerPos] = 'w';
                            if(solve(nextStartPos)){
                                return true;
                            }
                        }
                        //try black
                        {
                            vector<char> nextStartPos = startPos;
                            nextStartPos[blockerPos] = 'b';
                            if(solve(nextStartPos)){
                                return true;
                            }
                        }
                        return false;
                    }
                }
                //all checks have passed, perform the move. 
                swap(curPos[from], curPos[to]);
            }
            else {
                //if the piece that we are moving is a man, then check if we should make him into a king. 
                //he should be made into a king if he needs to make a move that is not valid according to his 
                //piece color. 
                bool backwards = false;
                //also make sure that there are pieces to take. If there is a piece of the wrong color that
                //needs to be taken, then this start pos cannot be valid. 
                bool addedMan = false;
                for(int j = 0; j < moves[i].size() - 1; j++){
                    int from = moves[i][j];
                    int to = moves[i][j + 1];
                    bool whiteDir = isWhiteCapture(from, to);
                    backwards |= whiteDir ^ whiteMove;
                    bool leftCapture = isLeftCapture(from, to);
                    int takePos = move(from, whiteDir, leftCapture);
                    if(curPos[takePos].first == '.') {
                        addedMan = true;
                        startPos[takePos] = whiteMove? 'b' : 'w';
                    }
                    if((whiteMove && isWhitePiece(curPos[takePos].first)) || (!whiteMove && isBlackPiece(curPos[takePos].first))) {
                        //trying to take a piece of the same team, this board isn't going to produce a correct answer. 
                        return false;
                    }
                }
                if(backwards && !isKing(curPos[moves[i][0]].first)) {
                    //replace piece with a king and try again. 
                    int rpos = curPos[moves[i][0]].second;
                    startPos[rpos] = whiteMove? 'W' : 'B';
                    inconsistencyFound = true;
                    break;
                }
                if(addedMan) {
                    //go ahead and try again, we already replaced stuff
                    inconsistencyFound = true;
                    break;
                }
                //all the checks passed, let's perform the move. 
                for(int j = 0; j < moves[i].size() - 1; j++){
                    int from = moves[i][j];
                    int to = moves[i][j + 1];
                    bool whiteDir = isWhiteCapture(from, to);
                    bool leftCapture = isLeftCapture(from, to);
                    int takePos = move(from, whiteDir, leftCapture);
                    curPos[takePos] = {'.', -1};
                    swap(curPos[from], curPos[to]);
                }
                //make sure that there aren't any forced captures left for this piece to perform. 
                //if there are, then we have to install blockers. 
                int finalPos = moves[i][moves[i].size() - 1];
                {
                    int blockerPos = -1;
                    bool isWhite = whiteMove;
                    bool is_King = isKing(curPos[finalPos].first);
                    for(int k = 0; k < possibleMoves[finalPos][isWhite][is_King].size(); k++){
                        int movePos = possibleMoves[finalPos][isWhite][is_King][k].first;
                        int capturePos = possibleMoves[finalPos][isWhite][is_King][k].second;
                        if(curPos[movePos].first == '.' || curPos[capturePos].first != '.') {
                            continue;
                        }
                        if(isWhitePiece(curPos[movePos].first) == whiteMove) {
                            continue;
                        }
                        //this is a possible capture
                        blockerPos = capturePos;
                        break;
                    }
                    if(blockerPos != -1){
                        //try white
                        {
                            vector<char> nextStartPos = startPos;
                            nextStartPos[blockerPos] = 'w';
                            if(solve(nextStartPos)){
                                return true;
                            }
                        }
                        //try black
                        {
                            vector<char> nextStartPos = startPos;
                            nextStartPos[blockerPos] = 'b';
                            if(solve(nextStartPos)){
                                return true;
                            }
                        }
                        return false;
                    }
                }
            }
            //check if we should promote the piece. 
            int finalPos = moves[i][moves[i].size() - 1];
            if(shouldPromote(finalPos, curPos[finalPos].first)) {
                curPos[finalPos].first = promote(curPos[finalPos].first);
            }
            whiteMove = !whiteMove;
            //cout << "MOVE : " << i << " IS GOOD" << endl;
        }
        if(!inconsistencyFound) {
            break;
        }
    }
    //if there are no inconsistencies, then we can just return whatever starting position we have. 
    //go ahead and print the answer
    vector<char> curBoard(32, '.');
    for(int i = 0; i < 32; i++){
        curBoard[i] = curPos[i].first;
    }
    vector<string> sarr = boardToStrings(startPos);
    vector<string> earr = boardToStrings(curBoard);
    for(int i = 0; i < 8; i++){
        cout << sarr[i] << " " << earr[i] << "\n";
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    initMoves();
    char c;
    int n;
    cin >> c >> n;
    whiteStart = c == 'W';
    isCapture = vector<bool>(n, false);
    moves = vector<vector<int>>(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int cell = 0;
        for(int j = 0; j < s.size(); j++){
            if(s[j] == '-' || s[j] == 'x') {
                if(s[j] == 'x'){
                    isCapture[i] = true;
                }
                cell --;
                moves[i].push_back(cell);
                cell = 0;
            }
            else {
                cell *= 10;
                cell += s[j] - '0';
            }
        }
        cell --;
        moves[i].push_back(cell);
    }
    vector<char> startPos(32, '.');
    if(!solve(startPos)) {
        cout << "DIDNT GENERATE ANSWER" << endl;
        throw runtime_error("didn't generate an answer D:");
    }
    
    return 0;
}
