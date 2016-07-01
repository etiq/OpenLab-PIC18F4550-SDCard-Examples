#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=fat_access.c fat_cache.c fat_filelib.c fat_format.c fat_misc.c fat_string.c fat_table.c fat_write.c main.c mmc_pic24f.c delay.c spi_1.c uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/fat_access.p1 ${OBJECTDIR}/fat_cache.p1 ${OBJECTDIR}/fat_filelib.p1 ${OBJECTDIR}/fat_format.p1 ${OBJECTDIR}/fat_misc.p1 ${OBJECTDIR}/fat_string.p1 ${OBJECTDIR}/fat_table.p1 ${OBJECTDIR}/fat_write.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/mmc_pic24f.p1 ${OBJECTDIR}/delay.p1 ${OBJECTDIR}/spi_1.p1 ${OBJECTDIR}/uart.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/fat_access.p1.d ${OBJECTDIR}/fat_cache.p1.d ${OBJECTDIR}/fat_filelib.p1.d ${OBJECTDIR}/fat_format.p1.d ${OBJECTDIR}/fat_misc.p1.d ${OBJECTDIR}/fat_string.p1.d ${OBJECTDIR}/fat_table.p1.d ${OBJECTDIR}/fat_write.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/mmc_pic24f.p1.d ${OBJECTDIR}/delay.p1.d ${OBJECTDIR}/spi_1.p1.d ${OBJECTDIR}/uart.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/fat_access.p1 ${OBJECTDIR}/fat_cache.p1 ${OBJECTDIR}/fat_filelib.p1 ${OBJECTDIR}/fat_format.p1 ${OBJECTDIR}/fat_misc.p1 ${OBJECTDIR}/fat_string.p1 ${OBJECTDIR}/fat_table.p1 ${OBJECTDIR}/fat_write.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/mmc_pic24f.p1 ${OBJECTDIR}/delay.p1 ${OBJECTDIR}/spi_1.p1 ${OBJECTDIR}/uart.p1

# Source Files
SOURCEFILES=fat_access.c fat_cache.c fat_filelib.c fat_format.c fat_misc.c fat_string.c fat_table.c fat_write.c main.c mmc_pic24f.c delay.c spi_1.c uart.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4620
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/fat_access.p1: fat_access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_access.p1.d 
	@${RM} ${OBJECTDIR}/fat_access.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_access.p1  fat_access.c 
	@-${MV} ${OBJECTDIR}/fat_access.d ${OBJECTDIR}/fat_access.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_access.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_cache.p1: fat_cache.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_cache.p1.d 
	@${RM} ${OBJECTDIR}/fat_cache.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_cache.p1  fat_cache.c 
	@-${MV} ${OBJECTDIR}/fat_cache.d ${OBJECTDIR}/fat_cache.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_cache.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_filelib.p1: fat_filelib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_filelib.p1.d 
	@${RM} ${OBJECTDIR}/fat_filelib.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_filelib.p1  fat_filelib.c 
	@-${MV} ${OBJECTDIR}/fat_filelib.d ${OBJECTDIR}/fat_filelib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_filelib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_format.p1: fat_format.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_format.p1.d 
	@${RM} ${OBJECTDIR}/fat_format.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_format.p1  fat_format.c 
	@-${MV} ${OBJECTDIR}/fat_format.d ${OBJECTDIR}/fat_format.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_format.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_misc.p1: fat_misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_misc.p1.d 
	@${RM} ${OBJECTDIR}/fat_misc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_misc.p1  fat_misc.c 
	@-${MV} ${OBJECTDIR}/fat_misc.d ${OBJECTDIR}/fat_misc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_misc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_string.p1: fat_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_string.p1.d 
	@${RM} ${OBJECTDIR}/fat_string.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_string.p1  fat_string.c 
	@-${MV} ${OBJECTDIR}/fat_string.d ${OBJECTDIR}/fat_string.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_string.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_table.p1: fat_table.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_table.p1.d 
	@${RM} ${OBJECTDIR}/fat_table.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_table.p1  fat_table.c 
	@-${MV} ${OBJECTDIR}/fat_table.d ${OBJECTDIR}/fat_table.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_table.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_write.p1: fat_write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_write.p1.d 
	@${RM} ${OBJECTDIR}/fat_write.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_write.p1  fat_write.c 
	@-${MV} ${OBJECTDIR}/fat_write.d ${OBJECTDIR}/fat_write.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_write.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mmc_pic24f.p1: mmc_pic24f.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc_pic24f.p1.d 
	@${RM} ${OBJECTDIR}/mmc_pic24f.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/mmc_pic24f.p1  mmc_pic24f.c 
	@-${MV} ${OBJECTDIR}/mmc_pic24f.d ${OBJECTDIR}/mmc_pic24f.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mmc_pic24f.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/delay.p1: delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/delay.p1.d 
	@${RM} ${OBJECTDIR}/delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/delay.p1  delay.c 
	@-${MV} ${OBJECTDIR}/delay.d ${OBJECTDIR}/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/spi_1.p1: spi_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi_1.p1.d 
	@${RM} ${OBJECTDIR}/spi_1.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/spi_1.p1  spi_1.c 
	@-${MV} ${OBJECTDIR}/spi_1.d ${OBJECTDIR}/spi_1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/spi_1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/uart.p1: uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.p1.d 
	@${RM} ${OBJECTDIR}/uart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/uart.p1  uart.c 
	@-${MV} ${OBJECTDIR}/uart.d ${OBJECTDIR}/uart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/uart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/fat_access.p1: fat_access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_access.p1.d 
	@${RM} ${OBJECTDIR}/fat_access.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_access.p1  fat_access.c 
	@-${MV} ${OBJECTDIR}/fat_access.d ${OBJECTDIR}/fat_access.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_access.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_cache.p1: fat_cache.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_cache.p1.d 
	@${RM} ${OBJECTDIR}/fat_cache.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_cache.p1  fat_cache.c 
	@-${MV} ${OBJECTDIR}/fat_cache.d ${OBJECTDIR}/fat_cache.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_cache.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_filelib.p1: fat_filelib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_filelib.p1.d 
	@${RM} ${OBJECTDIR}/fat_filelib.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_filelib.p1  fat_filelib.c 
	@-${MV} ${OBJECTDIR}/fat_filelib.d ${OBJECTDIR}/fat_filelib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_filelib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_format.p1: fat_format.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_format.p1.d 
	@${RM} ${OBJECTDIR}/fat_format.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_format.p1  fat_format.c 
	@-${MV} ${OBJECTDIR}/fat_format.d ${OBJECTDIR}/fat_format.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_format.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_misc.p1: fat_misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_misc.p1.d 
	@${RM} ${OBJECTDIR}/fat_misc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_misc.p1  fat_misc.c 
	@-${MV} ${OBJECTDIR}/fat_misc.d ${OBJECTDIR}/fat_misc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_misc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_string.p1: fat_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_string.p1.d 
	@${RM} ${OBJECTDIR}/fat_string.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_string.p1  fat_string.c 
	@-${MV} ${OBJECTDIR}/fat_string.d ${OBJECTDIR}/fat_string.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_string.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_table.p1: fat_table.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_table.p1.d 
	@${RM} ${OBJECTDIR}/fat_table.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_table.p1  fat_table.c 
	@-${MV} ${OBJECTDIR}/fat_table.d ${OBJECTDIR}/fat_table.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_table.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fat_write.p1: fat_write.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fat_write.p1.d 
	@${RM} ${OBJECTDIR}/fat_write.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/fat_write.p1  fat_write.c 
	@-${MV} ${OBJECTDIR}/fat_write.d ${OBJECTDIR}/fat_write.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fat_write.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mmc_pic24f.p1: mmc_pic24f.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc_pic24f.p1.d 
	@${RM} ${OBJECTDIR}/mmc_pic24f.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/mmc_pic24f.p1  mmc_pic24f.c 
	@-${MV} ${OBJECTDIR}/mmc_pic24f.d ${OBJECTDIR}/mmc_pic24f.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mmc_pic24f.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/delay.p1: delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/delay.p1.d 
	@${RM} ${OBJECTDIR}/delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/delay.p1  delay.c 
	@-${MV} ${OBJECTDIR}/delay.d ${OBJECTDIR}/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/spi_1.p1: spi_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi_1.p1.d 
	@${RM} ${OBJECTDIR}/spi_1.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/spi_1.p1  spi_1.c 
	@-${MV} ${OBJECTDIR}/spi_1.d ${OBJECTDIR}/spi_1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/spi_1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/uart.p1: uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.p1.d 
	@${RM} ${OBJECTDIR}/uart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/uart.p1  uart.c 
	@-${MV} ${OBJECTDIR}/uart.d ${OBJECTDIR}/uart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/uart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     --rom=default,-fd30-ffff --ram=default,-ef4-eff,-f9c-f9c,-fd4-fd4,-fdb-fdf,-fe3-fe7,-feb-fef,-ffd-fff  -odist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=ignore --mode=std -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -odist/${CND_CONF}/${IMAGE_TYPE}/Example_7.5.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
