# 自动每日打卡脚本

$today = Get-Date -Format "yyyy-MM-dd"
$year = Get-Date -Format "yyyy"
$monthday = Get-Date -Format "MM-dd"

# 目录路径
$algopath = "Algorithms/$year/$monthday"
$mlpath = "Machine-Learning/$year/$monthday"
$logpath = "Daily-Logs/$today.md"

# 创建目录
New-Item -ItemType Directory -Force -Path $algopath
New-Item -ItemType Directory -Force -Path $mlpath
New-Item -ItemType Directory -Force -Path "Daily-Logs" | Out-Null

# 日记内容模板
$content = @"
# $today Daily Log

## ✅ 今日完成
- Codeforces:
- Machine Learning:
- 项目开发:

## 🔍 今日反思
- 

## 🚀 明日目标
-

"@

# 创建或跳过日志文件
if (!(Test-Path $logpath)) {
    $content | Out-File $logpath -Encoding UTF8
}

# Git 自动提交（如果没有文件改动也不报错）
git add .
git commit -m "Daily auto-setup for $today" 2>$null
git push
