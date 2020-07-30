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

printf "${YELLOW}Testing various champion errors${NC}\n\n"

printf "${YELLOW}• Champion has an invalid header:${NC}\n"
printf "${YELLOW}The following header is invalid :${NC}\n"
hexdump -vC corechecker/vm/errors/wrong-header.cor | head -n 8
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corechecker/vm/errors/wrong-header.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corechecker/vm/errors/wrong-header.cor

printf "\n${YELLOW}• Champion has no code:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corechecker/vm/errors/no-code.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corechecker/vm/errors/no-code.cor

printf "\n${YELLOW}• Champion's code is too big:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corechecker/vm/errors/too-big-champion.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corechecker/vm/errors/too-big-champion.cor
