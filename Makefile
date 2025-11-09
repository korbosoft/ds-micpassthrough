# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2023-2024

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME		:= ds-micpassthrough
GAME_TITLE	?= ds-micpassthrough
GAME_SUBTITLE	?= DS(i) as a microphone!
GAME_AUTHOR	?= korbosoft
GAME_ICON	?= $(CURDIR)/icon.png

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile
