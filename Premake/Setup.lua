ObjDir = "../Intermediate/"
ProjectDir = "../Projects/"
TargetDir = "../Build/"

function NewSolution(solutionName)
  solution(solutionName)
    defines { "_CRT_SECURE_NO_WARNINGS" }
    flags
    {
      "FatalWarnings",
      "No64BitChecks",
      "NoEditAndContinue",
      "NoIncrementalLink",
      "NoManifest",
      "NoMinimalRebuild",
      "Symbols",
    }
    floatingpoint "Fast"
    includedirs   "."
    language      "C++"
    location      (ProjectDir)
    objdir        (ObjDir)
    warnings      "Extra"
    
    configurations { "Debug", "DebugFast", "ReleaseSlow", "Release" }

    configuration "Debug"
      defines { "_DEBUG" }
      targetsuffix ("-" .. _ACTION .. "-Debug")
      
    configuration "DebugFast"
      buildoptions "/MDd"
      defines { "_DEBUG" }
      optimize "Speed"
      targetsuffix ("-" .. _ACTION .. "-DebugFast")
      
    configuration "ReleaseSlow"
      defines { "NDEBUG" }
      targetsuffix ("-" .. _ACTION .. "-ReleaseSlow")
      
    configuration "Release"
      defines { "NDEBUG" }
      optimize "Speed"
end

function NewProject(projectName, projectKind)
  project(projectName)
    files
    {
      projectName .. "/**.cpp",
      projectName .. "/**.h",
      projectName .. "/**.hpp"
    }
    kind      (projectKind)
    location  (ProjectDir)
    targetdir (TargetDir)
end