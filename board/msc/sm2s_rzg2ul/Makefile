#
# board/renesas/salvator-x/Makefile
#
# Copyright (C) 2015 Renesas Electronics Corporation
#
# SPDX-License-Identifier: GPL-2.0+
#

ifdef CONFIG_SPL_BUILD
obj-y	:= ../../renesas/rcar-common/gen3-spl.o
else
obj-y	:= sm2s-rzg2ul.o ../../renesas/rcar-common/common.o boardinfo.o bootsel.o
endif
