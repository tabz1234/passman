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
	else
		print("Unknown cmd argument :"..arg[i]..",abort")
		os.exit(1)
	end
end

if(RelType == "release")then
os.execute("sudo mkdir /usr/lib/passman")
os.execute("sudo cp ./resource/passman_conf.lua /usr/lib/passman")
os.execute("sudo cp ./resource/help_message.txt /usr/lib/passman")

os.execute("sudo mkdir /usr/share/bash-completion/completions")
os.execute("sudo mkdir /usr/share/fish/completions")
os.execute("sudo cp ./resource/passman.bash /usr/share/bash-completion/completions/passman")
os.execute("sudo cp ./resource/passman.fish /usr/share/fish/completions/passman.fish")
end

os.execute("mkdir build")
os.execute("mkdir build/"..RelType)
os.execute("cmake -DCMAKE_BUILD_TYPE="..RelType.." -B build/"..RelType)
os.execute("cd build/"..RelType.." && make -j"..Nproc)

if(RelType == "release")then
os.execute("sudo cp build/"..RelType.."/"..ExecName.." /bin")
end


Print_finished()
