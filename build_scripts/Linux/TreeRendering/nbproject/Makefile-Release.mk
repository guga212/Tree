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
CC=gcc-5
CCC=g++-5
CXX=g++-5
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
	${OBJECTDIR}/_ext/516c69aa/Main_Tree_Render.o


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
LDLIBSOPTIONS=-L../../../libs/Linux -Wl,-rpath,'../../../libs/Linux' ../../../libs/Linux/libsfml-graphics.so.2.5.1 ../../../libs/Linux/libsfml-system.so.2.5.1 ../../../libs/Linux/libsfml-window.so.2.5.1 '-Wl,-rpath=$$ORIGIN'  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/../../../../bin/Linux/TreeRendering

${CND_DISTDIR}/../../../../bin/Linux/TreeRendering: ../../../libs/Linux/libsfml-graphics.so.2.5.1

${CND_DISTDIR}/../../../../bin/Linux/TreeRendering: ../../../libs/Linux/libsfml-system.so.2.5.1

${CND_DISTDIR}/../../../../bin/Linux/TreeRendering: ../../../libs/Linux/libsfml-window.so.2.5.1

${CND_DISTDIR}/../../../../bin/Linux/TreeRendering: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/../../../../bin/Linux
	${LINK.cc} -o ${CND_DISTDIR}/../../../../bin/Linux/TreeRendering ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/516c69aa/Main_Tree_Render.o: ../../../source/Main_Tree_Render.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/516c69aa
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -std=c++17 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/516c69aa/Main_Tree_Render.o ../../../source/Main_Tree_Render.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/../../../../bin/Linux/libsfml-graphics.so.2.5.1 ${CND_DISTDIR}/../../../../bin/Linux/libsfml-system.so.2.5.1 ${CND_DISTDIR}/../../../../bin/Linux/libsfml-window.so.2.5.1
	${RM} ${CND_DISTDIR}/../../../../bin/Linux/TreeRendering

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
