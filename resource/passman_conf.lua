--This is default configuration file for passman

DEBUG = true

LUA_PREFIX = "[LUA]"
function Lprint(val) 
print(LUA_PREFIX..val);
end

AppDataDir = "/usr/lib/passman"
RandomAsciiLenght = 30

if DEBUG == true then Lprint(" Using appdata path :"..AppDataDir) end


