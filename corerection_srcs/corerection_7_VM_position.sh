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
	printf "${RED}Script must be executed from corerection.sh${NC}\n"
	exit 1
fi

printf "${YELLOW}Showcasing the starting position of champions${NC}\n"

printf "\n${YELLOW}• 2 champions:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF -d 1 Parasite.cor Parasite.cor | grep -v "^0x0... : 00"
printf "${PINK}Result :${NC}\n"
$COREWAR -d 1 Parasite.cor Parasite.cor | grep -v "^0x0...:	00"

printf "\n${YELLOW}• 4 champions:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF -d 1 Parasite.cor Parasite.cor Parasite.cor Parasite.cor | grep -v "^0x0... : 00"
printf "${PINK}Result :${NC}\n"
$COREWAR -d 1 Parasite.cor Parasite.cor Parasite.cor Parasite.cor | grep -v "^0x0...:	00"
