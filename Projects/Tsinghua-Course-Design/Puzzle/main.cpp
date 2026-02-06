#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream> // 新增：用于文件读写
#include <windows.h> // 新增：用于设置控制台编码
#include <ctime>   // 新增
#include <cstdlib> // 新增
#include <queue> // 用于优先队列
#include <map>   // 用于记录访问过的状态
using namespace std;

#pragma pack(push,1)
struct BMPFileHeader
{
    uint16_t bfType; // 文件类型，必须是0x4D42
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
struct BMPInfoHeader
{
    uint32_t biSize;
    int32_t  biWidth;   // 改为 int32_t
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct Pixel
{
    uint8_t b,g,r;
};
class BMPImage
{
public:
    int width = 0;
    int height = 0;
    vector<Pixel> pixels;

    bool Load(const string& filename)
    {
        ifstream file(filename, ios::binary);
        if(!file)
        {
            cerr << "Error: Cannot open file path!" << endl;
            return false;
        }

        BMPFileHeader fileHeader;
        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

        if(fileHeader.bfType != 0x4D42)
        {
            cerr << "Error: Not a valid BMP file!" << endl;
            return false;
        }

        BMPInfoHeader infoHeader;
        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

        // 修正宽高读取
        width = infoHeader.biWidth;
        // 高度可能是负数，取绝对值
        height = abs(infoHeader.biHeight);

        // 检查位深
        if(infoHeader.biBitCount != 24)
        {
            cerr << "Error: Only 24-bit BMP is supported. Current: " << infoHeader.biBitCount << endl;
            return false;
        }

        // 计算对齐
        int rowStride = (width * 3 + 3) & (~3);
        int padding = rowStride - (width * 3);

        pixels.resize(width * height);
        
        // 移动文件指针到数据区
        file.seekg(fileHeader.bfOffBits, ios::beg);

        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                Pixel p;
                file.read(reinterpret_cast<char*>(&p), 3);
                pixels[y * width + x] = p;
            }
            // 跳过填充
            file.seekg(padding, ios::cur);
        }
        
        // 这里的输出改成英文
        cout << "Success! Image Loaded: " << width << "x" << height << endl;
        return true;
    }
    bool Save(const string& filename,const vector<int>& board,int M,int N)
    {
        if(pixels.empty()) return false;
        ofstream file(filename, ios::binary);
        if (!file) return false;
        int rowStride = (width * 3 + 3) & (~3); // 4字节对齐的行宽
        int padding = rowStride - (width * 3);  // 填充字节数
        uint32_t dataSize = rowStride * height;
        uint32_t fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + dataSize;
        BMPFileHeader fileHeader;
        fileHeader.bfType = 0x4D42; // 'BM'
        fileHeader.bfSize = fileSize;
        fileHeader.bfReserved1 = 0;
        fileHeader.bfReserved2 = 0;
        fileHeader.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
        BMPInfoHeader infoHeader;
        infoHeader.biSize = 40;
        infoHeader.biWidth = width;
        infoHeader.biHeight = height; // 正数，代表数据从下到上存储
        infoHeader.biPlanes = 1;
        infoHeader.biBitCount = 24;
        infoHeader.biCompression = 0;
        infoHeader.biSizeImage = dataSize;
        infoHeader.biXPelsPerMeter = 0;
        infoHeader.biYPelsPerMeter = 0;
        infoHeader.biClrUsed = 0;
        infoHeader.biClrImportant = 0;

        // 写入头部
        file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
        file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
        // 2. 写入像素数据
        // 关键点：BMP文件通常是从下到上存储的 (y=0 是最底下一行)
        // 我们的 pixels vector 也是按读取顺序存的（也是从下到上）
        
        int blockWidth = width / N;
        int blockHeight = height / M;

        // 遍历文件的每一行（从底部 y=0 开始写到顶部）
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                // A. 计算当前坐标(x,y)属于拼图板的哪一块(Grid)?
                // 因为y是从底部开始的，而Board Row 0是在顶部，所以要做个转换
                // BoardRow 0 (Top) 对应 y 范围 [height-blockHeight, height-1]
                
                int boardRow = (height - 1 - y) / blockHeight;
                int boardCol = x / blockWidth;

                // 防止边界计算误差导致越界
                if (boardRow >= M) boardRow = M - 1; 
                if (boardCol >= N) boardCol = N - 1;
                
                // B. 获取这块位置当前放的是几号图块
                int tileID = board[boardRow * N + boardCol];
                
                Pixel p;
                if (tileID == -1) 
                {
                    // 空格：白色
                    p = {0,0,0}; // 黑色
                }
                else 
                {
                    // C. 找到 tileID 在原图中的位置
                    int srcRow = tileID / N; 
                    int srcCol = tileID % N;

                    // D. 计算像素在图块内部的偏移量
                    int offsetX = x % blockWidth;
                    int offsetY = y % blockHeight; // 这里的y是相对底部的

                    // E. 计算原图中的真实像素坐标 (Source X, Source Y)
                    // 原图存储也是从下到上的，所以逻辑要一致
                    // SrcRow 0 (顶部) 的起始 Y 是 (M-1-0)*blockHeight
                    
                    int baseSrcY = (M - 1 - srcRow) * blockHeight;
                    int finalSrcY = baseSrcY + offsetY;
                    int finalSrcX = srcCol * blockWidth + offsetX;

                    // 边界保护
                    if (finalSrcX >= width) finalSrcX = width - 1;
                    if (finalSrcY >= height) finalSrcY = height - 1;

                    p = pixels[finalSrcY * width + finalSrcX];
                }

                file.write(reinterpret_cast<char*>(&p), 3);
            }
            // 写入每行的填充字节
            for (int k = 0; k < padding; k++) 
            {
                char pad = 0;
                file.write(&pad, 1);
            }
        }
        
        cout << "Snapshot saved to " << filename << endl;
        return true;
    }
};

int M,N;
vector<int> board;
int emptyPos;
BMPImage gameImage;
void InitBoard()
{
    board.resize(M * N);
    for(int i=0;i<M * N - 1;i++)
    {
        board[i] = i;
    }
    board[M * N - 1] = -1;
    emptyPos = M * N - 1;
}

void PrintBoard()
{
    // system("cls");
    cout << "----------------------" << endl;
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            int idx = i * N + j;
            if(board[idx] == -1)
            {
                cout << setw(4) << "__";
            }
            else cout<<setw(4)<<board[idx];
        }
        cout<<endl;
    }
    cout << "----------------------" << endl;
    cout << "Current Empty Pos(Index): " << emptyPos << endl;
}

void Move(char cmd)
{
    int row = emptyPos / N;
    int col = emptyPos % N;
    int targetPos = -1;
    switch(cmd)
    {
        case 'w':
        case 'W':
            if(row > 0) targetPos = emptyPos - N;
            break;
        case 's':
        case 'S':
            if(row < M - 1) targetPos = emptyPos + N;
            break;
        case 'a':
        case 'A':
            if(col > 0) targetPos = emptyPos - 1;
            break;
        case 'd':
        case 'D':
            if(col < N - 1) targetPos = emptyPos + 1;
            break;
    }
    if(targetPos != -1)
    {
        swap(board[emptyPos], board[targetPos]);
        emptyPos = targetPos;
    }
    else
    {
        cout << "Cannot Move! Hit Wall." << endl;
        // system("pause"); // Removed pause to avoid input buffer issues
    }
}

int GetInversions(const vector<int>& b)
{
    int inv = 0;
    vector<int> nums;
    for(int x : b)
    {
        if(x != -1) nums.push_back(x);
    }
    for(int i=0;i<nums.size();i++)
    {
        for(int j = i+1;j<nums.size();j++)
        {
            if(nums[i] > nums[j]) inv ++;
        }
    }
    return inv;
}

bool IsSolvable(int m,int n,const vector<int>& b)
{
    int inversions = GetInversions(b);
    if(n % 2 == 1)
    {
        return (inversions % 2 == 0);
    }
    else
    {
        int emptyIdx = -1;
        for(int i=0;i<b.size();i++)
        {
            if(b[i] == -1)
            {
                emptyIdx = i;
                break;
            }
        }
        int emptyRowFromTop = emptyIdx / n; // 0-based
        int emptyRowFromBottom = (m - 1) - emptyRowFromTop;
        return ((inversions + emptyRowFromBottom) % 2 == 0);
    }
}

void ShuffleBoard()
{
    for(int i=0;i<board.size();i++)
    {
        int j = rand() % board.size();
        swap(board[i], board[j]);
    }
    for(int i=0;i<board.size();i++)
    {
        if(board[i] == -1)
        {
            emptyPos = i;
            break;
        }
    }
    if(!IsSolvable(M,N,board))
    {
        int idx1 = -1, idx2 = -1;
        for(int i=0;i<board.size();i++)
        {
            if(board[i] != -1)
            {
                if(idx1 == -1) idx1 = i;
                else
                {
                    idx2 = i;
                    break;
                }
            }
        }
        if(idx1 != -1 && idx2 != -1)
        {
            swap(board[idx1], board[idx2]);
            cout << "[Info] 原状态不可解，已自动修复。" << endl;
        }
    }
    cout << "打乱完成！当前状态可解性分析: 可解" << endl;   
}

int CalcManhattan(const vector<int>& b,int m,int n)
{
    int dist = 0;
    for(int i=0;i<b.size();i++)
    {
        int val = b[i];
        if(val == -1) continue;
        int curRow = i / n;
        int curCol = i % n;
        int targetRow = val / n;
        int targetCol = val % n;
        dist += abs(curRow - targetRow) + abs(curCol - targetCol);
    }
    return dist;
}
struct Node
{
    vector<int> currnetBoard;
    int emptyIdx;
    string path;
    int g;
    int h;
    bool operator > (const Node& other) const{
        return g + h > (other.g + other.h);
    }
};
string SolvePuzzle(vector<int>& startBoard,int m,int n)
{
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    map<vector<int>,bool> visited;
    int startEmpty = -1;
    for(int i=0;i<startBoard.size();i++)
    {
        if(startBoard[i] == -1)
        {
            startEmpty = i;
            break;
        }
    }
    int startH = CalcManhattan(startBoard, m, n);
    pq.push({startBoard, startEmpty, "", 0, startH});
    visited[startBoard] = true;
    int dr[] = {-n, n, -1, 1}; 
    char dc[] = {'W', 'S', 'A', 'D'};
    cout << "正在思考中(A* Search)..." << endl;
    while(!pq.empty())
    {
        Node cur = pq.top(); pq.pop();
        if(cur.h == 0) return cur.path;
        int row = cur.emptyIdx / n;
        int col = cur.emptyIdx % n;
        for(int i=0;i<4;i++)
        {
            if(i == 0 && row == 0) continue; // W
            if(i == 1 && row == m - 1) continue; // S
            if(i == 2 && col == 0) continue; // A
            if(i == 3 && col == n - 1) continue; // D
            int targetIdx = cur.emptyIdx + dr[i];
            vector<int> nextBoard = cur.currnetBoard;
            swap(nextBoard[cur.emptyIdx], nextBoard[targetIdx]);
            if (visited.find(nextBoard) == visited.end()) {
                visited[nextBoard] = true;
                int newH = CalcManhattan(nextBoard, m, n);
                // 存入新节点：路径加一步，g+1
                pq.push({nextBoard, targetIdx, cur.path + dc[i], cur.g + 1, newH});
            }
        }
    }
    return "";
}
bool CheckWin()
{
    for(int i=0;i<board.size();i++)
    {
        if (board[i] != i) return false;
    }
    return true;
}
int main() {
    // 0. 设置随机种子 (必须加，否则每次运行产生的随机序列都一样)
    srand((unsigned)time(0));
    SetConsoleOutputCP(65001); 

    string imagePath;
    cout << "Please input BMP image path: ";
    cin >> imagePath;
    
    // 尝试读取，忽略失败（为了测试纯数字版）
    gameImage.Load(imagePath);

    cout << "Please input difficulty (M rows N cols, e.g. 3 3): ";
    if (!(cin >> M >> N)) return 0;

    // 初始化是有序的
    InitBoard();
    cout << "初始化完成，正在随机打乱..." << endl;
    
    // Step 4: 立即打乱
    ShuffleBoard();

    char cmd;
    while (true) {
        PrintBoard();

        if (CheckWin()) {
            cout << "\n★ ★ ★ 恭喜！拼图还原成功！ ★ ★ ★" << endl;
            cout << "输入 R 重新开始，或 P 退出。" << endl;
        }
        
        cout << "Command (W/A/S/D:Move, F:Auto-Solve, G:Save, R:Restart, P:Exit): ";
        cin >> cmd;

        if (cmd == 'P' || cmd == 'p') {
            cout << "Bye!" << endl;
            break;
        } 
        else if (cmd == 'G' || cmd == 'g') {
            string saveName;
            cout << "Save as (e.g. out.bmp): ";
            cin >> saveName;
            gameImage.Save(saveName, board, M, N);
            cout << "Press Enter..." << endl;
            cin.ignore(); cin.get();
        } 
        else if (cmd == 'R' || cmd == 'r') {
            cout << "Restarting..." << endl;
            ShuffleBoard();
        }
        else if (cmd == 'F' || cmd == 'f') { // 自动还原
            if (CheckWin()) {
                cout << "已经还原了，无需计算。" << endl;
                continue;
            }
            // 1. 计算路径
            string solution = SolvePuzzle(board, M, N);
            
            if (solution.empty()) {
                cout << "计算失败或无解！" << endl;
            } else {
                cout << "找到解法! 步数: " << solution.length() << endl;
                cout << "路径: " << solution << endl;
                cout << "正在自动演示..." << endl;
                
                // 2. 自动演示
                // 为了让用户看清楚，可以用 Sleep 暂停一下
                for (char step : solution) {
                    Move(step);
                    PrintBoard();
                    cout << "自动执行: " << step << endl;
                    Sleep(300); // 暂停 300 毫秒 (需包含 windows.h)
                }
                cout << "自动还原完成！" << endl;
            }
        }
        else {
            Move(cmd);
        }
    }
    return 0;
}