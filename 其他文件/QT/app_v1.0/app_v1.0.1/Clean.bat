@echo off
chcp 65001 >nul
echo 正在精准清除 VS2022 缓存文件夹：app\.vs

:: 定义要删除的路径
set "target=app\.vs"
set "target=.vs"
:: 如果存在就强制删除整个文件夹
if exist "%target%" (
    rmdir /s /q "%target%"
    echo ✅ 成功删除：%target%
) else (
    echo ℹ️ 未找到 .vs文件夹，无需清理
)

echo.
echo 清理完成！
pause >nul