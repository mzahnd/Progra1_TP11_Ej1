#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/args/arguments.o \
	${OBJECTDIR}/frontend/frontend.o \
	${OBJECTDIR}/frontend/term.o \
	${OBJECTDIR}/keyboard/keyboard.o \
	${OBJECTDIR}/keyboard/term_keyboard_input.o \
	${OBJECTDIR}/libs/PortEmul/PortEmul.o \
	${OBJECTDIR}/libs/termlib.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/audio_ejer1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/audio_ejer1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/audio_ejer1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/args/arguments.o: args/arguments.c
	${MKDIR} -p ${OBJECTDIR}/args
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/args/arguments.o args/arguments.c

${OBJECTDIR}/frontend/frontend.o: frontend/frontend.c
	${MKDIR} -p ${OBJECTDIR}/frontend
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/frontend/frontend.o frontend/frontend.c

${OBJECTDIR}/frontend/term.o: frontend/term.c
	${MKDIR} -p ${OBJECTDIR}/frontend
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/frontend/term.o frontend/term.c

${OBJECTDIR}/keyboard/keyboard.o: keyboard/keyboard.c
	${MKDIR} -p ${OBJECTDIR}/keyboard
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/keyboard/keyboard.o keyboard/keyboard.c

${OBJECTDIR}/keyboard/term_keyboard_input.o: keyboard/term_keyboard_input.c
	${MKDIR} -p ${OBJECTDIR}/keyboard
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/keyboard/term_keyboard_input.o keyboard/term_keyboard_input.c

${OBJECTDIR}/libs/PortEmul/PortEmul.o: libs/PortEmul/PortEmul.c
	${MKDIR} -p ${OBJECTDIR}/libs/PortEmul
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/PortEmul/PortEmul.o libs/PortEmul/PortEmul.c

${OBJECTDIR}/libs/termlib.o: libs/termlib.c
	${MKDIR} -p ${OBJECTDIR}/libs
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/termlib.o libs/termlib.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
