local clean = nil

if os.getenv("OS") and os.getenv("OS"):find("Windows") then
    clean = ".\\tools\\bin\\clean.exe"
else
    clean = "./tools/bin/clean"
end

local targets = {
    ".xmake",
    ".cache",
    "build"
}

for _, j in ipairs(targets) do
    os.execute(clean .. " " .. j)
end
