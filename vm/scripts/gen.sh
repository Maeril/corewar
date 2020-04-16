#!/bin/sh
scripts/gen_makefile.sh
scripts/gen_prototypes.sh
(cd ../libft; scripts/gen.sh)