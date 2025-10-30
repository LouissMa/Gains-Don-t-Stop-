@echo off
setlocal enabledelayedexpansion

:: 获取当前日期 YYYY MM DD
for /f "tokens=1-3 delims=-" %%a in ('powershell -command "Get-Date -Format yyyy-MM-dd"') do (
    set YEAR=%%a
    set DATE=%%a-%%b-%%c
    set MONTH=%%b
    set DAY=%%c
)

echo Today: %DATE%

:: 设置仓库路径，请替换成你的路径
set REPO=D:\GithubProjects\Gains-Don-t-Stop

cd %REPO%

:: 创建目录结构
mkdir Algorithms\%YEAR%\%MONTH%-%DAY% 2>nul
mkdir Machine-Learning\%YEAR%\%MONTH%-%DAY% 2>nul
mkdir Daily-Logs 2>nul

:: 创建每日日志文件
set LOGFILE=Daily-Logs\%DATE%.md
if not exist %LOGFILE% (
    echo # %DATE% ✅> %LOGFILE%
    echo 今日练习内容记录：>> %LOGFILE%
)

:: 自动添加到 Git
git add .
git commit -m "Daily Commit %DATE%"
git push

echo 成功 ✅ 今日打卡已记录到 GitHub！
pause
