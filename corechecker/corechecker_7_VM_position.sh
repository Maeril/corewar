#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
PINK='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

clear

if [ "$COREWAR_REF" = "" ]
then
	printf "${RED}Script must be executed from corechecker.sh${NC}\n"
	exit 1
fi

printf "${YELLOW}Showcasing the starting position of champions${NC}\n"

EMPTY_REF=$($COREWAR_REF -d 1 corechecker/vm/Parasite.cor | sed -n 4,4p | cut -d ' ' -f3-)
EMPTY_RES=$($COREWAR -d 1 corechecker/vm/Parasite.cor | cat -e  | grep -v Cycle | sed 's/\^\[\[0m//g' | rev | cut -d ' ' -f2- | rev | sed -n 3,3p | cut -d ' ' -f2-)

printf "\n${YELLOW}• 2 champions:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF -d 1 corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor | tail -n +4 | grep -v "$EMPTY_REF"
printf "${PINK}Result :${NC}\n"
$COREWAR -d 1 corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor | cat -e  | grep -v Cycle | sed 's/\^\[\[0m//g' | rev | cut -d ' ' -f2- | rev | grep -v "$EMPTY_RES"

printf "\n${YELLOW}• 3 champions:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF -d 1 corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor | tail -n +5 | grep -v "$EMPTY_REF"
printf "${PINK}Result :${NC}\n"
$COREWAR -d 1 corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor | cat -e  | grep -v Cycle | sed 's/\^\[\[0m//g' | rev | cut -d ' ' -f2- | rev | grep -v "$EMPTY_RES"

printf "\n${YELLOW}• 4 champions:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF -d 1 corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor | tail -n +6 | grep -v "$EMPTY_REF"
printf "${PINK}Result :${NC}\n"
$COREWAR -d 1 corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor corechecker/vm/Parasite.cor | cat -e | grep -v Cycle | sed 's/\^\[\[0m//g' | rev | cut -d ' ' -f2- | rev | grep -v "$EMPTY_RES"
