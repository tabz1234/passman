--This is default configuration file for passman.
--Passman will execute this file and then get specific variable names for internal use.
--All variables that affect passman behavior is initialized here by default.
--If you don't want to use this config, run "passman --no-config" and pass your settings through command line argumnets(see "passman --help")

--All static data sush as database or known_id's file stored here.
--Override with --appdatadir=
local homepath = os.getenv("HOME")
AppDataDir = homepath.."/.local/share/passman"

--Override with --lenght=
PasswordLenght = 30

--Override with --no-encryption.
UseEncryption = true

--Set UseDefaultMasterPassword to true if you lazy and don't want to always type master password.

if(UseEncryption) then
UseDefaultMasterPassword = false
   if(UseDefaultMasterPassword) then
	MasterPassword = "ChangeMe"
   end
end

--Display only raw result and nothing else?
--Override with --quiet or -q
Quiet = false
