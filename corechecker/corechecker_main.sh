#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
PINK='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

if [ ! -f "corewar" ]
then
	printf "${RED}Couldn't run script: corewar executable not found.${NC}\n"
	exit 1
fi

if [ ! -f "asm" ]
then
	printf "${RED}Couldn't run script: asm executable not found.${NC}\n"
	exit 1
fi

if [ -f "corechecker/asm/header.cor" ]
then
	rm corechecker/asm/header.cor
fi
if [ -f "corechecker/asm/header_ref.cor" ]
then
	rm corechecker/asm/header_ref.cor
fi

export ASM="./asm"
export COREWAR="./corewar"
export TMP=$(mktemp)
export REF=$(mktemp)
export RES=$(mktemp)
export BOOLEAN="Y"

VERSION=0
printf "${YELLOW}What Operating System are you using?${NC}\n${GREEN}1 • MacOS${NC}\n${ORANGE}2 • Linux${NC}\n"
read -p "" VERSION

case $VERSION in
	"1")
		export ASM_REF="./corechecker/asm_mac"
		export COREWAR_REF="./corechecker/corewar_mac"
		;;
	"2")
		export ASM_REF="./corechecker/asm_linux"
		export COREWAR_REF="./corechecker/corewar_linux"
		;;
	*)
		printf "Please enter a valid number"
		BOOLEAN="N"
		;;
esac
while [ "$BOOLEAN" = "Y" ]
do
	clear
	TEST=0
	printf "${YELLOW}What do you want to test?\n${ORANGE}1 • ASM - Header validity\n2 • ASM - Bytecode validity\n3 • ASM - Error management${NC}\n"
	printf "${PINK}4 • VM - Proof of concept\n5 • VM - Instruction execution\n6 • VM - IDX mod\n7 • VM - Champion positionning\n"
	printf "8 • VM - Error management\n${NC}"
	read -p "" TEST
	case $TEST in
		"1")
			sh corechecker/corechecker_1_ASM_header.sh
			;;
		"2")
			sh corechecker/corechecker_2_ASM_bytecode.sh
			;;
		"3")
			sh corechecker/corechecker_3_ASM_errors.sh
			;;
		"4")
			sh corechecker/corechecker_4_VM_proof.sh
			;;
		"5")
			sh corechecker/corechecker_5_VM_instructions.sh
			;;
		"6")
			sh corechecker/corechecker_6_VM_IDXmod.sh
			;;
		"7")
			sh corechecker/corechecker_7_VM_position.sh
			;;
		"8")
			sh corechecker/corechecker_8_VM_errors.sh
			;;
		*)
			printf "${RED}Please enter a valid number${NC}\n"
			BOOLEAN="N"
			;;
	esac
	if [ "$BOOLEAN" = "Y" ]
	then
		printf "${YELLOW}Continue testing? (Y/N)${NC} "
		read -p "" BOOLEAN
	fi
done

rm $TMP
rm $RES
rm $REF