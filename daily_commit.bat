@echo off
setlocal enabledelayedexpansion

:: 获取当前日期（格式：YYYY-MM-DD）
for /f "tokens=2 delims==" %%I in ('wmic os get localdatetime /value') do set datetime=%%I
set yyyy=%datetime:~0,4%
set mm=%datetime:~4,2%
set dd=%datetime:~6,2%
set today=%yyyy%-%mm%-%dd%

:: 目录路径
set algo_path=Algorithms\%yyyy%\%mm%-%dd%
set log_path=Daily-Logs\%today%.md

:: 创建文件夹
if not exist %algo_path% mkdir %algo_path%
if not exist Daily-Logs mkdir Daily-Logs

:: 创建算法总结模板
if not exist %algo_path%\README.md (
    echo # 🧩 %today% Algorithm Practice > %algo_path%\README.md
    echo. >> %algo_path%\README.md
    echo ## ✅ Solved Problems >> %algo_path%\README.md
    echo - [ ] A >> %algo_path%\README.md
    echo - [ ] B >> %algo_path%\README.md
    echo - [ ] C >> %algo_path%\README.md
    echo - [ ] D >> %algo_path%\README.md
    echo. >> %algo_path%\README.md
    echo ## 🧠 Key Ideas >> %algo_path%\README.md
    echo - 思路分析： >> %algo_path%\README.md
    echo. >> %algo_path%\README.md
    echo ## 💭 Reflection >> %algo_path%\README.md
    echo - 今日收获： >> %algo_path%\README.md
)

:: 创建每日学习日志模板
if not exist %log_path% (
    echo # 📘 Daily Log - %today% > %log_path%
    echo. >> %log_path%
    echo ## 💪 Algorithm Progress >> %log_path%
    echo - 今日题目： >> %log_path%
    echo. >> %log_path%
    echo ## 🧩 思考总结 >> %log_path%
    echo - 今天学到了： >> %log_path%
    echo. >> %log_path%
    echo ## 🕐 用时与计划 >> %log_path%
    echo - 用时： >> %log_path%
    echo - 明日目标： >> %log_path%
)

:: 提交到 GitHub
git add .
git commit -m "%today%: Created daily templates"
git push

echo ✅ 已生成模板并推送至 GitHub！
pause
