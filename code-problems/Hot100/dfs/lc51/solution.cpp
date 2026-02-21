class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        vector<vector<string>> res;
        backtrack(board, 0, res);
        return res;
    }
private:
    void backtrack(vector<string>& board, int row, vector<vector<string>>& res) {
        if (row == board.size()) {
            res.push_back(board);
            return;
        }
        int n = board[row].size();
        for (int col = 0; col < n; col++) {
            if (!isvalid(board, row, col)) {
                continue;
            }
            board[row][col] = 'Q';
            backtrack(board, row + 1, res);
            board[row][col] = '.';
        }
    }
    bool isvalid(vector<string>& board, int row,int  col) {
        int n = board.size();
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
            //只需看这一行之上的，排除列冲突
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
            //排除左上方
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
            //排除右上方
        }
        return true;
    }
};