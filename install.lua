#!/bin/lua

ExecName = "passman"
RelType = "release"
Nproc = 8

function Print_finished()
print("\n!!! INSTALL SCRIPT FINISHED !!!")
end

for i = 1,#arg do
if arg[i] == "--arch" then
	os.execute("makepkg -si")
	Print_finished()
	os.exit(0)
elseif arg[i] == "-g" then
	RelType = "debug"
	end
end

if(RelType == "release")then
os.execute("sudo mkdir /usr/lib/passman")
os.execute("sudo cp ./resource/passman_conf.lua /usr/lib/passman")
end

os.execute("mkdir build")
os.execute("mkdir build/"..RelType)
os.execute("cmake -DCMAKE_BUILD_TYPE="..RelType.." -B build/"..RelType)
os.execute("cd build/"..RelType.." && make -j"..Nproc)

if(RelType == "release")then
os.execute("sudo cp build/"..RelType.."/"..ExecName.." /bin")
end

os.execute("cd ../../")

Print_finished()
