import os
import platform

def joinPath(root, subdir):
    return os.path.normpath(os.path.join(root, subdir))

OS_NAME = platform.system()
ROOT        = os.getcwd();
BIN_DIR     = joinPath(ROOT, "bin");
LIB_DIR     = joinPath(ROOT, "lib");


CCFLAGS=""
LINKFLAGS=""
OS_SUBSYSTEM_CONSOLE=""
OS_SUBSYSTEM_WINDOWS=""

LIBS = [ ]
LIBPATH = [ LIB_DIR ] 
CPPPATH = [
  ROOT,
  joinPath(ROOT, "3rd"),
  joinPath(ROOT, "base"),
]

os.environ['BIN_DIR'] = BIN_DIR;
os.environ['LIB_DIR'] = LIB_DIR;

DefaultEnvironment(
  CCFLAGS = CCFLAGS,
  LIBS = LIBS,
  LIBPATH = LIBPATH,
  CPPPATH = CPPPATH,
  LINKFLAGS = LINKFLAGS,
  OS_SUBSYSTEM_CONSOLE = OS_SUBSYSTEM_CONSOLE,
  OS_SUBSYSTEM_WINDOWS = OS_SUBSYSTEM_WINDOWS
)

SConscriptFiles= [
  '3rd/cjson/SConscript',
  'tools/SConscript', 
  ]

SConscript(SConscriptFiles)

