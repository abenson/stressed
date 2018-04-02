#
# Stress Test
#

include $(GNUSTEP_MAKEFILES)/common.make

LDFLAGS="-lm"

CTOOL_NAME = stress

stress_C_FILES =      main.c                            \
                      modules.c                         \
                      modules/cpu.c                     \
                      modules/mem.c                     \
                      modules/proc.c                    \

stress_HEADER_FILES = modules.h                    \
                      modules/cpu.h                \
                      modules/mem.h                \
                      modules/proc.h               \

-include GNUmakefile.preamble

include $(GNUSTEP_MAKEFILES)/ctool.make

-include GNUmakefile.postamble

