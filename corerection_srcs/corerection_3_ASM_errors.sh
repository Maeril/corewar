#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
PINK='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

if [ "$ASM_REF" = "" ]
then
	printf "${RED}Script must be executed from corerection.sh${NC}\n"
	exit 1
fi

printf "${YELLOW}Testing various maps that should not get assembled by the ASM${NC}\n\n"

printf "${YELLOW}• Missing name:${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/no-name.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/no-name.s

printf "${YELLOW}\n• Missing comment :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/no-comment.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/no-comment.s

printf "${YELLOW}\n• Wrong number of parameters :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/parameter-number.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/parameter-number.s

printf "${YELLOW}\n• Wrong parameter type :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/parameter-type.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/parameter-type.s

printf "${YELLOW}\n• Unknown instruction :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/unknown-instruction.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/unknown-instruction.s

printf "${YELLOW}\n• Reference to a non-existing label :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/unknown-label.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/unknown-label.s

printf "${YELLOW}\n• Label contains a wrong char :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/wrong-label-char.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/wrong-label-char.s

printf "${YELLOW}\n\nTesting various maps that can be considered as errors or can be handled by the asm${NC}\n"

printf "${YELLOW}\n• Wrong type of file :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/wrong-file-type
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/wrong-file-type

printf "${YELLOW}\n• Name too big :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/too-big-name.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/too-big-name.s

printf "${YELLOW}\n• Comment too big :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/too-big-comment.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/too-big-comment.s

printf "${YELLOW}\n• Empty name :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/empty-name.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/empty-name.s

printf "${YELLOW}\n• Empty comment :${NC}\n"
printf "${GREEN}Reference :${NC}\n"
$ASM_REF corerection_srcs/champs/errors/empty-comment.s
printf "${PINK}Result :${NC}\n"
$ASM corerection_srcs/champs/errors/empty-comment.s
