--This is default configuration file for passman

DEBUG = true

LUA_PREFIX = "[LUA]"
function Lprint(val) 
print(LUA_PREFIX..val);
end

A=3.56

AppDataDir = "/usr/lib/passman"
DataBaseDir = AppDataDir.."/DB.d/"

if DEBUG == true then Lprint(" Using appdata path :"..AppDataDir) end


