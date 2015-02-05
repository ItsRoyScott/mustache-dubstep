dofile "../Premake/Setup.lua"

NewSolution("TestFramework")
NewProject("TestFramework", "StaticLib")
NewProject("TestFramework.Test", "ConsoleApp")