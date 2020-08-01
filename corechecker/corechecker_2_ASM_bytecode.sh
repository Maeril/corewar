#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
PINK='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

clear

if [ "$RES" = "" ]
then
	printf "${RED}Script must be executed from corechecker.sh${NC}\n"
	exit 1
fi
printf "${YELLOW}Comparing bytecode for each instruction${NC}\n"

FILES=$(ls corechecker/asm/instructions)
for INSTRUCTIONS in $FILES
do
	CHAMP=$(echo $INSTRUCTIONS | sed 's/\.s//g')
	printf "${YELLOW}$CHAMP${NC}\n"
	$ASM_REF "corechecker/asm/instructions/$INSTRUCTIONS" > $TMP
	hexdump -vC "corechecker/asm/instructions/$CHAMP.cor" | sed -n 138,138p > $RES
	rm "corechecker/asm/instructions/$CHAMP.cor"
	$ASM "corechecker/asm/instructions/$INSTRUCTIONS" > $TMP
	if [ ! -f corechecker/asm/instructions/$CHAMP.cor ]
	then
		ERR=$(cat $TMP)
		printf "${PINK}$ERR${NC}\n"
		continue
	fi
	hexdump -vC "corechecker/asm/instructions/$CHAMP.cor" | sed -n 138,138p > $REF
	rm "corechecker/asm/instructions/$CHAMP.cor"
	DIFF=$(diff $RES $REF)
	if [ "$DIFF" = "" ]
	then
		printf "${GREEN}Bytecodes are identical${NC}\n"
	else
		printf "${PINK}Bytecodes are different${NC}\n"
		printf "${YELLOW}Compare outputs manually? (Y/N)${NC} "
		read -p "" BOOLEAN
		if [ "$BOOLEAN" = "Y" ]
		then
			printf "${YELLOW}Diff :${NC}\n"
			printf "$DIFF\n"
			printf "${GREEN}Reference :${NC}\n"
			cat $REF
			printf "${PINK}Result :${NC}\n"
			cat $RES
		fi
	fi
done