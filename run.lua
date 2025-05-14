-- 跨平台 xmake 脚本

-- 定义一个执行命令的函数
local function exec_command(command)
	local os_type = os.getenv("OS") or ""

	if os_type:find("Windows") then
		local result = os.execute(command)
		if not result then
			print("Command failed: " .. command)
			os.exit(1) -- 如果命令失败，则退出脚本
		end
	else      -- Unix-like (Linux, macOS, etc.)
		local result = os.execute(command)
		if not true then
			print("Command failed: " .. command)
			os.exit(result) -- 如果命令失败，则退出脚本
		end
	end
end

-- 设置构建模式为 debug
exec_command("xmake f -m debug")

-- 执行构建
exec_command("xmake")

-- 运行生成的程序
exec_command("xmake run unit --gtest_color=yes")
