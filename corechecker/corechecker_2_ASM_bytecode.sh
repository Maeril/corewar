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
printf "${YELLOW}Comparing bytecode${NC}\n"
hexdump -vC corechecker/asm/instructions.cor | tail -n +138 > $RES
hexdump -vC corechecker/asm/instructions_ref.cor | tail -n +138 > $REF
DIFF=$(diff $REF $RES)
if [ "$DIFF" = "" ]
then
	printf "${GREEN}Bytecodes are identical${NC}\n"
else
	printf "${PINK}Bytecodes are different${NC}\n"
fi
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
