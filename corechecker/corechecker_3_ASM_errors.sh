#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
PINK='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

clear

if [ "$ASM_REF" = "" ]
then
	printf "${RED}Script must be executed from corechecker.sh${NC}\n"
	exit 1
fi

printf "${YELLOW}Testing various champions that should not get assembled by the ASM${NC}\n\n"

printf "${YELLOW}• Missing name:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/no-name.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/no-name.s
if [ -f "corechecker/asm/errors/no-name.cor" ]
then
	printf "${RED}A champion was created${NC}\n"
	rm corechecker/asm/errors/no-name.cor
fi

printf "${YELLOW}\n• Missing comment :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/no-comment.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/no-comment.s
if [ -f "corechecker/asm/errors/no-comment.cor" ]
then
	printf "${RED}A champion was created${NC}\n"
	rm corechecker/asm/errors/no-comment.cor
fi

printf "${YELLOW}\n• Wrong number of parameters :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/parameter-number.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/parameter-number.s
if [ -f "corechecker/asm/errors/parameter-number.cor" ]
then
	printf "${RED}A champion was created${NC}\n"
	rm corechecker/asm/errors/parameter-number.cor
fi

printf "${YELLOW}\n• Wrong parameter type :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/parameter-type.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/parameter-type.s
if [ -f "corechecker/asm/errors/parameter-type.cor" ]
then
	printf "${RED}A champion was created${NC}\n"
	rm corechecker/asm/errors/parameter-type.cor
fi

printf "${YELLOW}\n• Unknown instruction :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/unknown-instruction.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/unknown-instruction.s
if [ -f "corechecker/asm/errors/unknown-instruction.cor" ]
then
	printf "${RED}A champion was created${NC}\n"
	rm corechecker/asm/errors/unknown-instruction.cor
fi

printf "${YELLOW}\n• Reference to a non-existing label :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/unknown-label.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/unknown-label.s
if [ -f "corechecker/asm/errors/unknown-label.cor" ]
then
	printf "${RED}A champion was created${NC}\n"
	rm corechecker/asm/errors/unknown-label.cor
fi

printf "${YELLOW}\n• Label contains a wrong char :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/wrong-label-char.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/wrong-label-char.s
if [ -f "corechecker/asm/errors/wrong-label-char.cor" ]
then
	printf "${RED}A champion was created${NC}\n"
	rm corechecker/asm/errors/wrong-label-char.cor
fi

printf "${YELLOW}\n\nTesting various champions that can be considered as errors or can be handled by the asm${NC}\n"

printf "${YELLOW}\n• Wrong type of file :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/wrong-file-type
if [ -f ".cor" ]
then
	rm .cor
fi
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/wrong-file-type

printf "${YELLOW}\n• Name too big :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/too-big-name.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/too-big-name.s
if [ -f "corechecker/asm/errors/too-big-name.cor" ]
then
	printf "${ORANGE}A champion was created${NC}\n"
	printf "${YELLOW}Check created champion? (Y/N)${NC} "
	read -p "" BOOLEAN
	if [ "$BOOLEAN" = "Y" ]
	then
		hexdump -vC corechecker/asm/errors/too-big-name.cor
	fi
	rm corechecker/asm/errors/too-big-name.cor
fi

printf "${YELLOW}\n• Comment too big :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/too-big-comment.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/too-big-comment.s
if [ -f "corechecker/asm/errors/too-big-comment.cor" ]
then
	printf "${ORANGE}A champion was created${NC}\n"
	printf "${YELLOW}Check created champion? (Y/N)${NC} "
	read -p "" BOOLEAN
	if [ "$BOOLEAN" = "Y" ]
	then
		hexdump -vC corechecker/asm/errors/too-big-comment.cor
	fi
	rm corechecker/asm/errors/too-big-comment.cor
fi

printf "${YELLOW}\n• Empty name :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/empty-name.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/empty-name.s
if [ -f "corechecker/asm/errors/empty-name.cor" ]
then
	printf "${ORANGE}A champion was created${NC}\n"
	printf "${YELLOW}Check created champion? (Y/N)${NC} "
	read -p "" BOOLEAN
	if [ "$BOOLEAN" = "Y" ]
	then
		hexdump -vC corechecker/asm/errors/empty-name.cor
	fi
	rm corechecker/asm/errors/empty-name.cor
fi

printf "${YELLOW}\n• Empty comment :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corechecker/asm/errors/empty-comment.s
printf "${PINK}Result :${NC}\n"
$ASM corechecker/asm/errors/empty-comment.s
if [ -f "corechecker/asm/errors/empty-comment.cor" ]
then
	printf "${ORANGE}A champion was created${NC}\n"
	printf "${YELLOW}Check created champion? (Y/N)${NC} "
	read -p "" BOOLEAN
	if [ "$BOOLEAN" = "Y" ]
	then
		hexdump -vC corechecker/asm/errors/empty-comment.cor
	fi
	rm corechecker/asm/errors/empty-comment.cor
fi
