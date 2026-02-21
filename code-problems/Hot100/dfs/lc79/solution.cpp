class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        //m*n
        int m = board,size();
        int n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtrack(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
private:
    bool backtrack(vector<vector<char>>& board, const string& word, int r, int c, int index) {
        //检查（r,c）
        if (index == word.length()) {
            return true;
        }
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != word[index]) {
            return false;
        }
        char temp = board[r][c];
        board[r][c] = '\0';//标记已访问
        bool found = backtrack(board, word, r + 1, c, index + 1) || backtrack(board, word, r, c + 1, index + 1) ||
            backtrack(board, word, r, c - 1, index + 1) || backtrack(board, word, r - 1, c, index + 1);
        board[r][c] = temp;
        return found;
    }
};