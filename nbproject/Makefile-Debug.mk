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
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/darray/d_array.o \
	${OBJECTDIR}/dtable/d_table.o \
	${OBJECTDIR}/fileio/fileio.o \
	${OBJECTDIR}/interpreter.o \
	${OBJECTDIR}/lex.yy.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/parser.o \
	${OBJECTDIR}/semantic.o \
	${OBJECTDIR}/syntax.o \
	${OBJECTDIR}/y.tab.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yarl.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yarl.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yarl ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/darray/d_array.o: darray/d_array.c 
	${MKDIR} -p ${OBJECTDIR}/darray
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/darray/d_array.o darray/d_array.c

${OBJECTDIR}/dtable/d_table.o: dtable/d_table.c 
	${MKDIR} -p ${OBJECTDIR}/dtable
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dtable/d_table.o dtable/d_table.c

${OBJECTDIR}/fileio/fileio.o: fileio/fileio.c 
	${MKDIR} -p ${OBJECTDIR}/fileio
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fileio/fileio.o fileio/fileio.c

${OBJECTDIR}/interpreter.o: interpreter.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/interpreter.o interpreter.c

${OBJECTDIR}/lex.yy.o: lex.yy.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lex.yy.o lex.yy.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/parser.o: parser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser.o parser.c

${OBJECTDIR}/semantic.o: semantic.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/semantic.o semantic.c

${OBJECTDIR}/syntax.o: syntax.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/syntax.o syntax.c

lex.yy.c: token.l y.tab.h
	@echo Running flex...
	flex token.l

.NO_PARALLEL:y.tab.c y.tab.h
y.tab.c y.tab.h: token.y 
	@echo Running yacc...
	yacc -d token.y

${OBJECTDIR}/y.tab.o: y.tab.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/y.tab.o y.tab.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yarl.exe
	${RM} lex.yy.c
	${RM} y.tab.c y.tab.h

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
