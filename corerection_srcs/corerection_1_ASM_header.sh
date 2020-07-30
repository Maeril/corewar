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
	printf "${RED}Script must be executed from corerection.sh${NC}\n"
	exit 1
fi
printf "${YELLOW}Comparing header: magic number + name${NC}\n"
hexdump -vC corerection_srcs/champs/instructions.cor | head -n 8 > $RES
hexdump -vC corerection_srcs/champs/instructions_ref.cor | head -n 8 > $REF
DIFF=$(diff $REF $RES)
if [ "$DIFF" = "" ]
then
	printf "${GREEN}Bytes are identical${NC}\n"
else
	printf "${PINK}Bytes are different${NC}\n"
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
printf "${YELLOW}Comparing header: comment + code size${NC}\n"
hexdump -vC corerection_srcs/champs/instructions.cor | sed -n 9,137p > $RES
hexdump -vC corerection_srcs/champs/instructions_ref.cor | sed -n 9,137p > $REF
DIFF= $(diff $REF $RES)
if [ "$DIFF" = "" ]
then
	printf "${GREEN}Bytes are identical\n${NC}"
else
	printf "${PINK}Bytes are different\n${NC}"
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
