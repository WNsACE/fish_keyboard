import os
import platform

def joinPath(root, subdir):
    return os.path.normpath(os.path.join(root, subdir))

MACH        = platform.machine()
OS_NAME     = platform.system()
TARGET_ARCH = ""


ROOT        = os.getcwd();
BIN_DIR     = joinPath(ROOT, "bin");
LIB_DIR     = joinPath(ROOT, "lib");


if MACH == 'i686' or MACH == 'i386' or MACH == 'x86':
    TARGET_ARCH = 'x86'


CCFLAGS=""
LINKFLAGS=""
OS_SUBSYSTEM_CONSOLE=""
OS_SUBSYSTEM_WINDOWS=""

LIBS = [ ]
LIBPATH = [ LIB_DIR ] 
CPPPATH = [
  ROOT,
  joinPath(ROOT, "3rd"),
  joinPath(ROOT, "src"),
  joinPath(ROOT, "src/base"),
  joinPath(ROOT, '3rd/gtest/googletest'),
  joinPath(ROOT, '3rd/gtest/googletest/include'),
]


if OS_NAME == "Windows" :
  CCFLAGS += " -DWIN32 -D_WIN32 -DWINDOWS /EHsc -D_CONSOLE  /DEBUG /Od  /FS /Z7 /utf-8 /MD "
  if TARGET_ARCH == 'x86':
      LINKFLAGS += '/MACHINE:X86 /DEBUG '
      OS_SUBSYSTEM_CONSOLE += '/SUBSYSTEM:CONSOLE,5.01  '
      OS_SUBSYSTEM_WINDOWS += '/SUBSYSTEM:WINDOWS,5.01  '
  else:
      CCFLAGS += ' -D_WIN64 '
      LINKFLAGS += '/MACHINE:X64 /DEBUG '
      OS_SUBSYSTEM_CONSOLE += '/SUBSYSTEM:CONSOLE  '
      OS_SUBSYSTEM_WINDOWS += '/SUBSYSTEM:WINDOWS  '

os.environ['ROOT'] = ROOT;
os.environ['BIN_DIR'] = BIN_DIR;
os.environ['LIB_DIR'] = LIB_DIR;
os.environ['GTEST_ROOT'] = joinPath(ROOT, '3rd/gtest/googletest');

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
  'src/SConscript', 
  'tools/SConscript', 
  'tests/SConscript', 
  ]

SConscript(SConscriptFiles)

