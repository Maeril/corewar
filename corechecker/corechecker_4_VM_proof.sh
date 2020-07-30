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

printf "${YELLOW}Showing that the VM works: Setting up multiple duels on both VMs${NC}\n"

printf "\n${YELLOW}• Parasite vs zork ${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corechecker/vm/Parasite.cor corechecker/vm/zork.cor
echo ""
$COREWAR_REF corechecker/vm/zork.cor corechecker/vm/Parasite.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corechecker/vm/Parasite.cor corechecker/vm/zork.cor
echo ""
$COREWAR corechecker/vm/zork.cor corechecker/vm/Parasite.cor
echo ""

printf "\n${YELLOW}• Parasite vs maxidef ${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corechecker/vm/Parasite.cor corechecker/vm/maxidef.cor
echo ""
$COREWAR_REF corechecker/vm/maxidef.cor corechecker/vm/Parasite.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corechecker/vm/Parasite.cor corechecker/vm/maxidef.cor
echo ""
$COREWAR corechecker/vm/maxidef.cor corechecker/vm/Parasite.cor
echo ""

printf "\n${YELLOW}• Parasite vs mortel ${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corechecker/vm/Parasite.cor corechecker/vm/mortel.cor
echo ""
$COREWAR_REF corechecker/vm/mortel.cor corechecker/vm/Parasite.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corechecker/vm/Parasite.cor corechecker/vm/mortel.cor
echo ""
$COREWAR corechecker/vm/mortel.cor corechecker/vm/Parasite.cor
echo ""

printf "\n${YELLOW}• Parasite vs slider2 ${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corechecker/vm/Parasite.cor corechecker/vm/slider2.cor
echo ""
$COREWAR_REF corechecker/vm/slider2.cor corechecker/vm/Parasite.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corechecker/vm/Parasite.cor corechecker/vm/slider2.cor
echo ""
$COREWAR corechecker/vm/slider2.cor corechecker/vm/Parasite.cor
echo ""