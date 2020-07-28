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

printf "${YELLOW}Showing that the VM works: Setting up multiple duels on both VMs${NC}\n"

printf "\n${YELLOW}• Parasite vs zork ${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corerection_srcs/champs/Parasite.cor corerection_srcs/champs/zork.cor
echo ""
$COREWAR_REF corerection_srcs/champs/zork.cor corerection_srcs/champs/Parasite.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corerection_srcs/champs/Parasite.cor corerection_srcs/champs/zork.cor
echo ""
$COREWAR corerection_srcs/champs/zork.cor corerection_srcs/champs/Parasite.cor
echo ""

printf "\n${YELLOW}• Parasite vs maxidef ${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corerection_srcs/champs/Parasite.cor corerection_srcs/champs/maxidef.cor
echo ""
$COREWAR_REF corerection_srcs/champs/maxidef.cor corerection_srcs/champs/Parasite.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corerection_srcs/champs/Parasite.cor corerection_srcs/champs/maxidef.cor
echo ""
$COREWAR corerection_srcs/champs/maxidef.cor corerection_srcs/champs/Parasite.cor
echo ""

printf "\n${YELLOW}• Parasite vs mortel ${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corerection_srcs/champs/Parasite.cor corerection_srcs/champs/mortel.cor
echo ""
$COREWAR_REF corerection_srcs/champs/mortel.cor corerection_srcs/champs/Parasite.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corerection_srcs/champs/Parasite.cor corerection_srcs/champs/mortel.cor
echo ""
$COREWAR corerection_srcs/champs/mortel.cor corerection_srcs/champs/Parasite.cor
echo ""

printf "\n${YELLOW}• Parasite vs slider2 ${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$COREWAR_REF corerection_srcs/champs/Parasite.cor corerection_srcs/champs/slider2.cor
echo ""
$COREWAR_REF corerection_srcs/champs/slider2.cor corerection_srcs/champs/Parasite.cor
printf "${PINK}Result :${NC}\n"
$COREWAR corerection_srcs/champs/Parasite.cor corerection_srcs/champs/slider2.cor
echo ""
$COREWAR corerection_srcs/champs/slider2.cor corerection_srcs/champs/Parasite.cor
echo ""